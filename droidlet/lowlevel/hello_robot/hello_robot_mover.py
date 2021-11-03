"""
Copyright (c) Facebook, Inc. and its affiliates.
"""
import os
import sys
import math
import copy
import time
import logging
from collections.abc import Iterable
from prettytable import PrettyTable
import Pyro4
import numpy as np

if "/opt/ros/kinetic/lib/python2.7/dist-packages" in sys.path:
    sys.path.remove("/opt/ros/kinetic/lib/python2.7/dist-packages")

import cv2
from droidlet.shared_data_structs import ErrorWithResponse
from agents.argument_parser import ArgumentParser
from droidlet.shared_data_structs import RGBDepth

from ..robot_mover import MoverInterface
from ..robot_mover_utils import (
    get_camera_angles,
    angle_diff,
    MAX_PAN_RAD,
    CAMERA_HEIGHT,
    ARM_HEIGHT,
    transform_pose,
    base_canonical_coords_to_pyrobot_coords,
    xyz_pyrobot_to_canonical_coords,
)
from tenacity import retry, stop_after_attempt, wait_fixed

Pyro4.config.SERIALIZER = "pickle"
Pyro4.config.SERIALIZERS_ACCEPTED.add("pickle")
Pyro4.config.PICKLE_PROTOCOL_VERSION=2

def safe_call(f, *args, **kwargs):
    try:
        return f(*args, **kwargs)
    except Pyro4.errors.ConnectionClosedError as e:
        msg = "{} - {}".format(f._RemoteMethod__name, e)
        raise ErrorWithResponse(msg)
    except Exception as e:
        print("Pyro traceback:")
        print("".join(Pyro4.util.getPyroTraceback()))
        raise e

class HelloRobotMover(MoverInterface):
    """Implements methods that call the physical interfaces of the Robot.

    Arguments:
        ip (string): IP of the Robot.
    """

    def __init__(self, ip=None):
        self.bot = Pyro4.Proxy("PYRONAME:remotehellorobot@" + ip)
        self.cam = Pyro4.Proxy("PYRONAME:remotehellorealsense@" + ip)
        self.curr_look_dir = np.array([0, 0, 1])  # initial look dir is along the z-axis

        intrinsic_mat = np.asarray(safe_call(self.cam.get_intrinsics))
        intrinsic_mat_inv = np.linalg.inv(intrinsic_mat)
        img_resolution = safe_call(self.cam.get_img_resolution)
        img_pixs = np.mgrid[0 : img_resolution[1] : 1, 0 : img_resolution[0] : 1]
        img_pixs = img_pixs.reshape(2, -1)
        img_pixs[[0, 1], :] = img_pixs[[1, 0], :]
        uv_one = np.concatenate((img_pixs, np.ones((1, img_pixs.shape[1]))))
        self.uv_one_in_cam = np.dot(intrinsic_mat_inv, uv_one)

    # TODO/FIXME!  instead of just True/False, return diagnostic messages
    # so e.g. if a grip attempt fails, the task is finished, but the status is a failure
    def bot_step(self):
        try:
            f = self.bot.command_finished()
        except:
            # do better here?
            f = True
        return f

    def get_pan(self):
        """get yaw in radians."""
        return self.bot.get_pan()

    def get_tilt(self):
        """get pitch in radians."""
        return self.bot.get_tilt()

    def reset_camera(self):
        """reset the camera to 0 pan and tilt."""
        return self.bot.reset()

    def move_relative(self, xyt_positions, use_dslam=False):
        """Command to execute a relative move.

        Args:
            xyt_positions: a list of relative (x,y,yaw) positions for the bot to execute.
            x,y,yaw are in the pyrobot's coordinates.
        """
        if not isinstance(next(iter(xyt_positions)), Iterable):
            # single xyt position given
            xyt_positions = [xyt_positions]
        for xyt in xyt_positions:
            safe_call(self.bot.go_to_relative, xyt, close_loop=True, use_dslam=use_dslam)

    def move_absolute(self, xyt_positions, use_map=False, use_dslam=False):
        """Command to execute a move to an absolute position.

        It receives positions in canonical world coordinates and converts them to pyrobot's coordinates
        before calling the bot APIs.

        Args:
            xyt_positions: a list of (x_c,y_c,yaw) positions for the bot to move to.
            (x_c,y_c,yaw) are in the canonical world coordinates.
        """
        if not isinstance(next(iter(xyt_positions)), Iterable):
            # single xyt position given
            xyt_positions = [xyt_positions]
        for xyt in xyt_positions:
            logging.info("Move absolute in canonical coordinates {}".format(xyt))
            self.bot.go_to_absolute(
                base_canonical_coords_to_pyrobot_coords(xyt),
                close_loop=True,
                use_map=use_map,
                use_dslam=use_dslam,
            )
        return "finished"

    def look_at(self, obj_pos, yaw_deg, pitch_deg):
        """Executes "look at" by setting the pan, tilt of the camera or turning the base if required.

        Uses both the base state and object coordinates in canonical world coordinates to calculate
        expected yaw and pitch.

        Args:
            obj_pos (list): object coordinates as saved in memory.
            yaw_deg (float): yaw in degrees
            pitch_deg (float): pitch in degrees

        Returns:
            string "finished"
        """
        pan_rad, tilt_rad = 0.0, 0.0
        old_pan = self.get_pan()
        old_tilt = self.get_tilt()
        pos = self.get_base_pos_in_canonical_coords()
        logging.info(f"Current Locobot state (x, z, yaw): {pos}")
        if yaw_deg:
            pan_rad = old_pan - float(yaw_deg) * np.pi / 180
        if pitch_deg:
            tilt_rad = old_tilt - float(pitch_deg) * np.pi / 180
        if obj_pos is not None:
            logging.info(f"looking at x,y,z: {obj_pos}")
            pan_rad, tilt_rad = get_camera_angles([pos[0], CAMERA_HEIGHT, pos[1]], obj_pos)
            logging.info(f"Returned new pan and tilt angles (radians): ({pan_rad}, {tilt_rad})")

        # FIXME!!! more async; move head and body at the same time
        head_res = angle_diff(pos[2], pan_rad)
        if np.abs(head_res) > MAX_PAN_RAD:
            dyaw = np.sign(head_res) * (np.abs(head_res) - MAX_PAN_RAD)
            self.turn(dyaw)
            pan_rad = np.sign(head_res) * MAX_PAN_RAD
        else:
            pan_rad = head_res
        logging.info(f"Camera new pan and tilt angles (radians): ({pan_rad}, {tilt_rad})")
        self.bot.set_pan_tilt(pan_rad, np.clip(tilt_rad, tilt_rad, 0.9))

        return "finished"

    def get_base_pos_in_canonical_coords(self):
        """get the current robot position in the canonical coordinate system
       
        the standard coordinate systems:
          Camera looks at (0, 0, 1),
          its right direction is (1, 0, 0) and
          its up-direction is (0, 1, 0)

         return:
         (x, z, yaw) of the robot base in standard coordinates
        """
        x_global, y_global, yaw = safe_call(self.bot.get_base_state)
        x_standard = -y_global
        z_standard = x_global
        return np.array([x_standard, z_standard, yaw])
        
    def get_rgb_depth(self):
        """Fetches rgb, depth and pointcloud in pyrobot world coordinates.

        Returns:
            an RGBDepth object
        """
        rgb, depth, rot, trans = self.cam.get_pcd_data()
        rgb = np.asarray(rgb).astype(np.uint8)
        rgb = cv2.cvtColor(rgb, cv2.COLOR_BGR2RGB)
        depth = np.asarray(depth)
        rot = np.asarray(rot)
        trans = np.asarray(trans)
        depth = depth.astype(np.float32)
        d = copy.deepcopy(depth)
        print(f'shapes depth {depth.shape}, rgb {rgb.shape}')
        depth /= 1000.0
        depth = depth.reshape(-1)
        print(f'shapes depth {depth.shape}, rot {rot.shape}')
        pts_in_cam = np.multiply(self.uv_one_in_cam, depth)
        pts_in_cam = np.concatenate((pts_in_cam, np.ones((1, pts_in_cam.shape[1]))), axis=0)
        pts = pts_in_cam[:3, :].T
        pts = np.dot(pts, rot.T)
        pts = pts + trans.reshape(-1)
        pts = transform_pose(pts, self.bot.get_base_state())
        logging.info("Fetched all camera sensor input.")
        return RGBDepth(rgb, d, pts)

    def turn(self, yaw):
        """turns the bot by the yaw specified.

        Args:
            yaw: the yaw to execute in degree.
        """
        turn_rad = yaw * math.pi / 180
        self.bot.rotate_by(turn_rad)

    def get_obstacles_in_canonical_coords(self):
        cordinates_in_robot_frame = self.bot.get_map()
        cordinates_in_standard_frame = [
            xyz_pyrobot_to_canonical_coords(list(c) + [0.0]) for c in cordinates_in_robot_frame
        ]
        cordinates_in_standard_frame = [(c[0], c[2]) for c in cordinates_in_standard_frame]
        return cordinates_in_standard_frame

    def explore(self):
        return self.bot.explore()

if __name__ == "__main__":
    base_path = os.path.dirname(__file__)
    parser = ArgumentParser("HelloRobot", base_path)
    opts = parser.parse()
    mover = BotMover(ip=opts.ip)
    if opts.check_controller:
        mover.check()
