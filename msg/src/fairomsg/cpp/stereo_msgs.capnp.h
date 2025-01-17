// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: stereo_msgs.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>

#if CAPNP_VERSION != 9001
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif

#include "sensor_msgs.capnp.h"
#include "std_msgs.capnp.h"

CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(858a55eca55d6633);

}  // namespace schemas
}  // namespace capnp

namespace mrp {
namespace stereo {

struct DisparityImage {
  DisparityImage() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(858a55eca55d6633, 3, 3)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class DisparityImage::Reader {
public:
  typedef DisparityImage Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline bool hasHeader() const;
  inline  ::mrp::std::Header::Reader getHeader() const;

  inline bool hasImage() const;
  inline  ::mrp::sensor::Image::Reader getImage() const;

  inline float getF() const;

  inline float getT() const;

  inline bool hasValidWindow() const;
  inline  ::mrp::sensor::RegionOfInterest::Reader getValidWindow() const;

  inline float getMinDisparity() const;

  inline float getMaxDisparity() const;

  inline float getDeltaD() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class DisparityImage::Builder {
public:
  typedef DisparityImage Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline bool hasHeader();
  inline  ::mrp::std::Header::Builder getHeader();
  inline void setHeader( ::mrp::std::Header::Reader value);
  inline  ::mrp::std::Header::Builder initHeader();
  inline void adoptHeader(::capnp::Orphan< ::mrp::std::Header>&& value);
  inline ::capnp::Orphan< ::mrp::std::Header> disownHeader();

  inline bool hasImage();
  inline  ::mrp::sensor::Image::Builder getImage();
  inline void setImage( ::mrp::sensor::Image::Reader value);
  inline  ::mrp::sensor::Image::Builder initImage();
  inline void adoptImage(::capnp::Orphan< ::mrp::sensor::Image>&& value);
  inline ::capnp::Orphan< ::mrp::sensor::Image> disownImage();

  inline float getF();
  inline void setF(float value);

  inline float getT();
  inline void setT(float value);

  inline bool hasValidWindow();
  inline  ::mrp::sensor::RegionOfInterest::Builder getValidWindow();
  inline void setValidWindow( ::mrp::sensor::RegionOfInterest::Reader value);
  inline  ::mrp::sensor::RegionOfInterest::Builder initValidWindow();
  inline void adoptValidWindow(::capnp::Orphan< ::mrp::sensor::RegionOfInterest>&& value);
  inline ::capnp::Orphan< ::mrp::sensor::RegionOfInterest> disownValidWindow();

  inline float getMinDisparity();
  inline void setMinDisparity(float value);

  inline float getMaxDisparity();
  inline void setMaxDisparity(float value);

  inline float getDeltaD();
  inline void setDeltaD(float value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class DisparityImage::Pipeline {
public:
  typedef DisparityImage Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::mrp::std::Header::Pipeline getHeader();
  inline  ::mrp::sensor::Image::Pipeline getImage();
  inline  ::mrp::sensor::RegionOfInterest::Pipeline getValidWindow();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline bool DisparityImage::Reader::hasHeader() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool DisparityImage::Builder::hasHeader() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::mrp::std::Header::Reader DisparityImage::Reader::getHeader() const {
  return ::capnp::_::PointerHelpers< ::mrp::std::Header>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::mrp::std::Header::Builder DisparityImage::Builder::getHeader() {
  return ::capnp::_::PointerHelpers< ::mrp::std::Header>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::mrp::std::Header::Pipeline DisparityImage::Pipeline::getHeader() {
  return  ::mrp::std::Header::Pipeline(_typeless.getPointerField(0));
}
#endif  // !CAPNP_LITE
inline void DisparityImage::Builder::setHeader( ::mrp::std::Header::Reader value) {
  ::capnp::_::PointerHelpers< ::mrp::std::Header>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::mrp::std::Header::Builder DisparityImage::Builder::initHeader() {
  return ::capnp::_::PointerHelpers< ::mrp::std::Header>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void DisparityImage::Builder::adoptHeader(
    ::capnp::Orphan< ::mrp::std::Header>&& value) {
  ::capnp::_::PointerHelpers< ::mrp::std::Header>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::mrp::std::Header> DisparityImage::Builder::disownHeader() {
  return ::capnp::_::PointerHelpers< ::mrp::std::Header>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline bool DisparityImage::Reader::hasImage() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool DisparityImage::Builder::hasImage() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::mrp::sensor::Image::Reader DisparityImage::Reader::getImage() const {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::Image>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::mrp::sensor::Image::Builder DisparityImage::Builder::getImage() {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::Image>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::mrp::sensor::Image::Pipeline DisparityImage::Pipeline::getImage() {
  return  ::mrp::sensor::Image::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void DisparityImage::Builder::setImage( ::mrp::sensor::Image::Reader value) {
  ::capnp::_::PointerHelpers< ::mrp::sensor::Image>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::mrp::sensor::Image::Builder DisparityImage::Builder::initImage() {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::Image>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void DisparityImage::Builder::adoptImage(
    ::capnp::Orphan< ::mrp::sensor::Image>&& value) {
  ::capnp::_::PointerHelpers< ::mrp::sensor::Image>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::mrp::sensor::Image> DisparityImage::Builder::disownImage() {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::Image>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline float DisparityImage::Reader::getF() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline float DisparityImage::Builder::getF() {
  return _builder.getDataField<float>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void DisparityImage::Builder::setF(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline float DisparityImage::Reader::getT() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline float DisparityImage::Builder::getT() {
  return _builder.getDataField<float>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void DisparityImage::Builder::setT(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline bool DisparityImage::Reader::hasValidWindow() const {
  return !_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline bool DisparityImage::Builder::hasValidWindow() {
  return !_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline  ::mrp::sensor::RegionOfInterest::Reader DisparityImage::Reader::getValidWindow() const {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::RegionOfInterest>::get(_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline  ::mrp::sensor::RegionOfInterest::Builder DisparityImage::Builder::getValidWindow() {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::RegionOfInterest>::get(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::mrp::sensor::RegionOfInterest::Pipeline DisparityImage::Pipeline::getValidWindow() {
  return  ::mrp::sensor::RegionOfInterest::Pipeline(_typeless.getPointerField(2));
}
#endif  // !CAPNP_LITE
inline void DisparityImage::Builder::setValidWindow( ::mrp::sensor::RegionOfInterest::Reader value) {
  ::capnp::_::PointerHelpers< ::mrp::sensor::RegionOfInterest>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline  ::mrp::sensor::RegionOfInterest::Builder DisparityImage::Builder::initValidWindow() {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::RegionOfInterest>::init(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline void DisparityImage::Builder::adoptValidWindow(
    ::capnp::Orphan< ::mrp::sensor::RegionOfInterest>&& value) {
  ::capnp::_::PointerHelpers< ::mrp::sensor::RegionOfInterest>::adopt(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::mrp::sensor::RegionOfInterest> DisparityImage::Builder::disownValidWindow() {
  return ::capnp::_::PointerHelpers< ::mrp::sensor::RegionOfInterest>::disown(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}

inline float DisparityImage::Reader::getMinDisparity() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline float DisparityImage::Builder::getMinDisparity() {
  return _builder.getDataField<float>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void DisparityImage::Builder::setMinDisparity(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline float DisparityImage::Reader::getMaxDisparity() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline float DisparityImage::Builder::getMaxDisparity() {
  return _builder.getDataField<float>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void DisparityImage::Builder::setMaxDisparity(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline float DisparityImage::Reader::getDeltaD() const {
  return _reader.getDataField<float>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline float DisparityImage::Builder::getDeltaD() {
  return _builder.getDataField<float>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void DisparityImage::Builder::setDeltaD(float value) {
  _builder.setDataField<float>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

}  // namespace
}  // namespace

CAPNP_END_HEADER

