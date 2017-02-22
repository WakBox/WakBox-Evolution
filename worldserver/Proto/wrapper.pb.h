// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: wrapper.proto

#ifndef PROTOBUF_wrapper_2eproto__INCLUDED
#define PROTOBUF_wrapper_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace WakfuProto {
class Wrapper;
class WrapperDefaultTypeInternal;
extern WrapperDefaultTypeInternal _Wrapper_default_instance_;
}  // namespace WakfuProto

namespace WakfuProto {

namespace protobuf_wrapper_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_wrapper_2eproto

// ===================================================================

class Wrapper : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:WakfuProto.Wrapper) */ {
 public:
  Wrapper();
  virtual ~Wrapper();

  Wrapper(const Wrapper& from);

  inline Wrapper& operator=(const Wrapper& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Wrapper& default_instance();

  static inline const Wrapper* internal_default_instance() {
    return reinterpret_cast<const Wrapper*>(
               &_Wrapper_default_instance_);
  }

  void Swap(Wrapper* other);

  // implements Message ----------------------------------------------

  inline Wrapper* New() const PROTOBUF_FINAL { return New(NULL); }

  Wrapper* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Wrapper& from);
  void MergeFrom(const Wrapper& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Wrapper* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required bytes innerMessage = 2;
  bool has_innermessage() const;
  void clear_innermessage();
  static const int kInnerMessageFieldNumber = 2;
  const ::std::string& innermessage() const;
  void set_innermessage(const ::std::string& value);
  #if LANG_CXX11
  void set_innermessage(::std::string&& value);
  #endif
  void set_innermessage(const char* value);
  void set_innermessage(const void* value, size_t size);
  ::std::string* mutable_innermessage();
  ::std::string* release_innermessage();
  void set_allocated_innermessage(::std::string* innermessage);

  // required sint64 guid = 1;
  bool has_guid() const;
  void clear_guid();
  static const int kGuidFieldNumber = 1;
  ::google::protobuf::int64 guid() const;
  void set_guid(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:WakfuProto.Wrapper)
 private:
  void set_has_guid();
  void clear_has_guid();
  void set_has_innermessage();
  void clear_has_innermessage();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr innermessage_;
  ::google::protobuf::int64 guid_;
  friend struct  protobuf_wrapper_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Wrapper

// required sint64 guid = 1;
inline bool Wrapper::has_guid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Wrapper::set_has_guid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Wrapper::clear_has_guid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Wrapper::clear_guid() {
  guid_ = GOOGLE_LONGLONG(0);
  clear_has_guid();
}
inline ::google::protobuf::int64 Wrapper::guid() const {
  // @@protoc_insertion_point(field_get:WakfuProto.Wrapper.guid)
  return guid_;
}
inline void Wrapper::set_guid(::google::protobuf::int64 value) {
  set_has_guid();
  guid_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.Wrapper.guid)
}

// required bytes innerMessage = 2;
inline bool Wrapper::has_innermessage() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Wrapper::set_has_innermessage() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Wrapper::clear_has_innermessage() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Wrapper::clear_innermessage() {
  innermessage_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_innermessage();
}
inline const ::std::string& Wrapper::innermessage() const {
  // @@protoc_insertion_point(field_get:WakfuProto.Wrapper.innerMessage)
  return innermessage_.GetNoArena();
}
inline void Wrapper::set_innermessage(const ::std::string& value) {
  set_has_innermessage();
  innermessage_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:WakfuProto.Wrapper.innerMessage)
}
#if LANG_CXX11
inline void Wrapper::set_innermessage(::std::string&& value) {
  set_has_innermessage();
  innermessage_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:WakfuProto.Wrapper.innerMessage)
}
#endif
inline void Wrapper::set_innermessage(const char* value) {
  set_has_innermessage();
  innermessage_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:WakfuProto.Wrapper.innerMessage)
}
inline void Wrapper::set_innermessage(const void* value, size_t size) {
  set_has_innermessage();
  innermessage_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:WakfuProto.Wrapper.innerMessage)
}
inline ::std::string* Wrapper::mutable_innermessage() {
  set_has_innermessage();
  // @@protoc_insertion_point(field_mutable:WakfuProto.Wrapper.innerMessage)
  return innermessage_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Wrapper::release_innermessage() {
  // @@protoc_insertion_point(field_release:WakfuProto.Wrapper.innerMessage)
  clear_has_innermessage();
  return innermessage_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Wrapper::set_allocated_innermessage(::std::string* innermessage) {
  if (innermessage != NULL) {
    set_has_innermessage();
  } else {
    clear_has_innermessage();
  }
  innermessage_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), innermessage);
  // @@protoc_insertion_point(field_set_allocated:WakfuProto.Wrapper.innerMessage)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace WakfuProto

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_wrapper_2eproto__INCLUDED
