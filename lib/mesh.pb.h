// Generated by the protocol buffer compiler.  DO NOT EDIT!

#ifndef PROTOBUF_mesh_2eproto__INCLUDED
#define PROTOBUF_mesh_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2000003
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2000003 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>

namespace mesh {

// Internal implementation detail -- do not call these.
void  protobuf_BuildDesc_mesh_2eproto();
void protobuf_BuildDesc_mesh_2eproto_AssignGlobalDescriptors(
    ::google::protobuf::FileDescriptor* file);

class Mesh;
class Mesh_Layer;

// ===================================================================

class Mesh_Layer : public ::google::protobuf::Message {
 public:
  Mesh_Layer();
  virtual ~Mesh_Layer();
  
  Mesh_Layer(const Mesh_Layer& from);
  
  inline Mesh_Layer& operator=(const Mesh_Layer& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Mesh_Layer& default_instance();
  void Swap(Mesh_Layer* other);
  
  // implements Message ----------------------------------------------
  
  Mesh_Layer* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline ::std::string* mutable_name();
  
  // required int32 columns = 2;
  inline bool has_columns() const;
  inline void clear_columns();
  inline ::google::protobuf::int32 columns() const;
  inline void set_columns(::google::protobuf::int32 value);
  
  // required int32 rows = 3;
  inline bool has_rows() const;
  inline void clear_rows();
  inline ::google::protobuf::int32 rows() const;
  inline void set_rows(::google::protobuf::int32 value);
  
  // repeated float data = 4;
  inline int data_size() const;
  inline void clear_data();
  inline const ::google::protobuf::RepeatedField< float >& data() const;
  inline ::google::protobuf::RepeatedField< float >* mutable_data();
  inline float data(int index) const;
  inline void set_data(int index, float value);
  inline void add_data(float value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* name_;
  static const ::std::string _default_name_;
  ::google::protobuf::int32 columns_;
  ::google::protobuf::int32 rows_;
  ::google::protobuf::RepeatedField< float > data_;
  friend void protobuf_BuildDesc_mesh_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Mesh_Layer* default_instance_;
};
// -------------------------------------------------------------------

class Mesh : public ::google::protobuf::Message {
 public:
  Mesh();
  virtual ~Mesh();
  
  Mesh(const Mesh& from);
  
  inline Mesh& operator=(const Mesh& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Mesh& default_instance();
  void Swap(Mesh* other);
  
  // implements Message ----------------------------------------------
  
  Mesh* New() const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SetCachedSize(int size) const { _cached_size_ = size; }
  public:
  
  const ::google::protobuf::Descriptor* GetDescriptor() const;
  const ::google::protobuf::Reflection* GetReflection() const;
  
  // nested types ----------------------------------------------------
  
  typedef Mesh_Layer Layer;
  
  // accessors -------------------------------------------------------
  
  // repeated .mesh.Mesh.Layer layers = 1;
  inline int layers_size() const;
  inline void clear_layers();
  inline const ::google::protobuf::RepeatedPtrField< ::mesh::Mesh_Layer >& layers() const;
  inline ::google::protobuf::RepeatedPtrField< ::mesh::Mesh_Layer >* mutable_layers();
  inline const ::mesh::Mesh_Layer& layers(int index) const;
  inline ::mesh::Mesh_Layer* mutable_layers(int index);
  inline ::mesh::Mesh_Layer* add_layers();
  
  // repeated uint32 indices = 2;
  inline int indices_size() const;
  inline void clear_indices();
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >& indices() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >* mutable_indices();
  inline ::google::protobuf::uint32 indices(int index) const;
  inline void set_indices(int index, ::google::protobuf::uint32 value);
  inline void add_indices(::google::protobuf::uint32 value);
  
  // required int32 primitive_type = 3;
  inline bool has_primitive_type() const;
  inline void clear_primitive_type();
  inline ::google::protobuf::int32 primitive_type() const;
  inline void set_primitive_type(::google::protobuf::int32 value);
  
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::google::protobuf::RepeatedPtrField< ::mesh::Mesh_Layer > layers_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > indices_;
  ::google::protobuf::int32 primitive_type_;
  friend void protobuf_BuildDesc_mesh_2eproto_AssignGlobalDescriptors(
      const ::google::protobuf::FileDescriptor* file);
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Mesh* default_instance_;
};
// ===================================================================


// ===================================================================


// ===================================================================

// Mesh_Layer

// required string name = 1;
inline bool Mesh_Layer::has_name() const {
  return _has_bit(0);
}
inline void Mesh_Layer::clear_name() {
  if (name_ != &_default_name_) {
    name_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Mesh_Layer::name() const {
  return *name_;
}
inline void Mesh_Layer::set_name(const ::std::string& value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Mesh_Layer::set_name(const char* value) {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline ::std::string* Mesh_Layer::mutable_name() {
  _set_bit(0);
  if (name_ == &_default_name_) {
    name_ = new ::std::string;
  }
  return name_;
}

// required int32 columns = 2;
inline bool Mesh_Layer::has_columns() const {
  return _has_bit(1);
}
inline void Mesh_Layer::clear_columns() {
  columns_ = 0;
  _clear_bit(1);
}
inline ::google::protobuf::int32 Mesh_Layer::columns() const {
  return columns_;
}
inline void Mesh_Layer::set_columns(::google::protobuf::int32 value) {
  _set_bit(1);
  columns_ = value;
}

// required int32 rows = 3;
inline bool Mesh_Layer::has_rows() const {
  return _has_bit(2);
}
inline void Mesh_Layer::clear_rows() {
  rows_ = 0;
  _clear_bit(2);
}
inline ::google::protobuf::int32 Mesh_Layer::rows() const {
  return rows_;
}
inline void Mesh_Layer::set_rows(::google::protobuf::int32 value) {
  _set_bit(2);
  rows_ = value;
}

// repeated float data = 4;
inline int Mesh_Layer::data_size() const {
  return data_.size();
}
inline void Mesh_Layer::clear_data() {
  data_.Clear();
}
inline const ::google::protobuf::RepeatedField< float >&
Mesh_Layer::data() const {
  return data_;
}
inline ::google::protobuf::RepeatedField< float >*
Mesh_Layer::mutable_data() {
  return &data_;
}
inline float Mesh_Layer::data(int index) const {
  return data_.Get(index);
}
inline void Mesh_Layer::set_data(int index, float value) {
  data_.Set(index, value);
}
inline void Mesh_Layer::add_data(float value) {
  data_.Add(value);
}

// -------------------------------------------------------------------

// Mesh

// repeated .mesh.Mesh.Layer layers = 1;
inline int Mesh::layers_size() const {
  return layers_.size();
}
inline void Mesh::clear_layers() {
  layers_.Clear();
}
inline const ::google::protobuf::RepeatedPtrField< ::mesh::Mesh_Layer >&
Mesh::layers() const {
  return layers_;
}
inline ::google::protobuf::RepeatedPtrField< ::mesh::Mesh_Layer >*
Mesh::mutable_layers() {
  return &layers_;
}
inline const ::mesh::Mesh_Layer& Mesh::layers(int index) const {
  return layers_.Get(index);
}
inline ::mesh::Mesh_Layer* Mesh::mutable_layers(int index) {
  return layers_.Mutable(index);
}
inline ::mesh::Mesh_Layer* Mesh::add_layers() {
  return layers_.Add();
}

// repeated uint32 indices = 2;
inline int Mesh::indices_size() const {
  return indices_.size();
}
inline void Mesh::clear_indices() {
  indices_.Clear();
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Mesh::indices() const {
  return indices_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Mesh::mutable_indices() {
  return &indices_;
}
inline ::google::protobuf::uint32 Mesh::indices(int index) const {
  return indices_.Get(index);
}
inline void Mesh::set_indices(int index, ::google::protobuf::uint32 value) {
  indices_.Set(index, value);
}
inline void Mesh::add_indices(::google::protobuf::uint32 value) {
  indices_.Add(value);
}

// required int32 primitive_type = 3;
inline bool Mesh::has_primitive_type() const {
  return _has_bit(2);
}
inline void Mesh::clear_primitive_type() {
  primitive_type_ = 0;
  _clear_bit(2);
}
inline ::google::protobuf::int32 Mesh::primitive_type() const {
  return primitive_type_;
}
inline void Mesh::set_primitive_type(::google::protobuf::int32 value) {
  _set_bit(2);
  primitive_type_ = value;
}


}  // namespace mesh
#endif  // PROTOBUF_mesh_2eproto__INCLUDED