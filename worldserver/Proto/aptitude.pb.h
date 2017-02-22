// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: aptitude.proto

#ifndef PROTOBUF_aptitude_2eproto__INCLUDED
#define PROTOBUF_aptitude_2eproto__INCLUDED

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
class CategoryPoints;
class CategoryPointsDefaultTypeInternal;
extern CategoryPointsDefaultTypeInternal _CategoryPoints_default_instance_;
class LevelsByBonus;
class LevelsByBonusDefaultTypeInternal;
extern LevelsByBonusDefaultTypeInternal _LevelsByBonus_default_instance_;
class Sheet;
class SheetDefaultTypeInternal;
extern SheetDefaultTypeInternal _Sheet_default_instance_;
class SheetSet;
class SheetSetDefaultTypeInternal;
extern SheetSetDefaultTypeInternal _SheetSet_default_instance_;
}  // namespace WakfuProto

namespace WakfuProto {

namespace protobuf_aptitude_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_aptitude_2eproto

// ===================================================================

class SheetSet : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:WakfuProto.SheetSet) */ {
 public:
  SheetSet();
  virtual ~SheetSet();

  SheetSet(const SheetSet& from);

  inline SheetSet& operator=(const SheetSet& from) {
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
  static const SheetSet& default_instance();

  static inline const SheetSet* internal_default_instance() {
    return reinterpret_cast<const SheetSet*>(
               &_SheetSet_default_instance_);
  }

  void Swap(SheetSet* other);

  // implements Message ----------------------------------------------

  inline SheetSet* New() const PROTOBUF_FINAL { return New(NULL); }

  SheetSet* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const SheetSet& from);
  void MergeFrom(const SheetSet& from);
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
  void InternalSwap(SheetSet* other);
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

  // repeated .WakfuProto.Sheet sheets = 2;
  int sheets_size() const;
  void clear_sheets();
  static const int kSheetsFieldNumber = 2;
  const ::WakfuProto::Sheet& sheets(int index) const;
  ::WakfuProto::Sheet* mutable_sheets(int index);
  ::WakfuProto::Sheet* add_sheets();
  ::google::protobuf::RepeatedPtrField< ::WakfuProto::Sheet >*
      mutable_sheets();
  const ::google::protobuf::RepeatedPtrField< ::WakfuProto::Sheet >&
      sheets() const;

  // @@protoc_insertion_point(class_scope:WakfuProto.SheetSet)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::WakfuProto::Sheet > sheets_;
  friend struct  protobuf_aptitude_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Sheet : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:WakfuProto.Sheet) */ {
 public:
  Sheet();
  virtual ~Sheet();

  Sheet(const Sheet& from);

  inline Sheet& operator=(const Sheet& from) {
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
  static const Sheet& default_instance();

  static inline const Sheet* internal_default_instance() {
    return reinterpret_cast<const Sheet*>(
               &_Sheet_default_instance_);
  }

  void Swap(Sheet* other);

  // implements Message ----------------------------------------------

  inline Sheet* New() const PROTOBUF_FINAL { return New(NULL); }

  Sheet* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Sheet& from);
  void MergeFrom(const Sheet& from);
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
  void InternalSwap(Sheet* other);
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

  // repeated .WakfuProto.LevelsByBonus bonus = 4;
  int bonus_size() const;
  void clear_bonus();
  static const int kBonusFieldNumber = 4;
  const ::WakfuProto::LevelsByBonus& bonus(int index) const;
  ::WakfuProto::LevelsByBonus* mutable_bonus(int index);
  ::WakfuProto::LevelsByBonus* add_bonus();
  ::google::protobuf::RepeatedPtrField< ::WakfuProto::LevelsByBonus >*
      mutable_bonus();
  const ::google::protobuf::RepeatedPtrField< ::WakfuProto::LevelsByBonus >&
      bonus() const;

  // repeated .WakfuProto.CategoryPoints categoryPoints = 5;
  int categorypoints_size() const;
  void clear_categorypoints();
  static const int kCategoryPointsFieldNumber = 5;
  const ::WakfuProto::CategoryPoints& categorypoints(int index) const;
  ::WakfuProto::CategoryPoints* mutable_categorypoints(int index);
  ::WakfuProto::CategoryPoints* add_categorypoints();
  ::google::protobuf::RepeatedPtrField< ::WakfuProto::CategoryPoints >*
      mutable_categorypoints();
  const ::google::protobuf::RepeatedPtrField< ::WakfuProto::CategoryPoints >&
      categorypoints() const;

  // required string name = 2;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required int32 index = 1;
  bool has_index() const;
  void clear_index();
  static const int kIndexFieldNumber = 1;
  ::google::protobuf::int32 index() const;
  void set_index(::google::protobuf::int32 value);

  // required int32 level = 3;
  bool has_level() const;
  void clear_level();
  static const int kLevelFieldNumber = 3;
  ::google::protobuf::int32 level() const;
  void set_level(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:WakfuProto.Sheet)
 private:
  void set_has_index();
  void clear_has_index();
  void set_has_name();
  void clear_has_name();
  void set_has_level();
  void clear_has_level();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::WakfuProto::LevelsByBonus > bonus_;
  ::google::protobuf::RepeatedPtrField< ::WakfuProto::CategoryPoints > categorypoints_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int32 index_;
  ::google::protobuf::int32 level_;
  friend struct  protobuf_aptitude_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class LevelsByBonus : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:WakfuProto.LevelsByBonus) */ {
 public:
  LevelsByBonus();
  virtual ~LevelsByBonus();

  LevelsByBonus(const LevelsByBonus& from);

  inline LevelsByBonus& operator=(const LevelsByBonus& from) {
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
  static const LevelsByBonus& default_instance();

  static inline const LevelsByBonus* internal_default_instance() {
    return reinterpret_cast<const LevelsByBonus*>(
               &_LevelsByBonus_default_instance_);
  }

  void Swap(LevelsByBonus* other);

  // implements Message ----------------------------------------------

  inline LevelsByBonus* New() const PROTOBUF_FINAL { return New(NULL); }

  LevelsByBonus* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const LevelsByBonus& from);
  void MergeFrom(const LevelsByBonus& from);
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
  void InternalSwap(LevelsByBonus* other);
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

  // required int32 bonusId = 1;
  bool has_bonusid() const;
  void clear_bonusid();
  static const int kBonusIdFieldNumber = 1;
  ::google::protobuf::int32 bonusid() const;
  void set_bonusid(::google::protobuf::int32 value);

  // required int32 level = 2;
  bool has_level() const;
  void clear_level();
  static const int kLevelFieldNumber = 2;
  ::google::protobuf::int32 level() const;
  void set_level(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:WakfuProto.LevelsByBonus)
 private:
  void set_has_bonusid();
  void clear_has_bonusid();
  void set_has_level();
  void clear_has_level();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::int32 bonusid_;
  ::google::protobuf::int32 level_;
  friend struct  protobuf_aptitude_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class CategoryPoints : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:WakfuProto.CategoryPoints) */ {
 public:
  CategoryPoints();
  virtual ~CategoryPoints();

  CategoryPoints(const CategoryPoints& from);

  inline CategoryPoints& operator=(const CategoryPoints& from) {
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
  static const CategoryPoints& default_instance();

  static inline const CategoryPoints* internal_default_instance() {
    return reinterpret_cast<const CategoryPoints*>(
               &_CategoryPoints_default_instance_);
  }

  void Swap(CategoryPoints* other);

  // implements Message ----------------------------------------------

  inline CategoryPoints* New() const PROTOBUF_FINAL { return New(NULL); }

  CategoryPoints* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CategoryPoints& from);
  void MergeFrom(const CategoryPoints& from);
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
  void InternalSwap(CategoryPoints* other);
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

  // required int32 categoryId = 1;
  bool has_categoryid() const;
  void clear_categoryid();
  static const int kCategoryIdFieldNumber = 1;
  ::google::protobuf::int32 categoryid() const;
  void set_categoryid(::google::protobuf::int32 value);

  // required int32 points = 2;
  bool has_points() const;
  void clear_points();
  static const int kPointsFieldNumber = 2;
  ::google::protobuf::int32 points() const;
  void set_points(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:WakfuProto.CategoryPoints)
 private:
  void set_has_categoryid();
  void clear_has_categoryid();
  void set_has_points();
  void clear_has_points();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::int32 categoryid_;
  ::google::protobuf::int32 points_;
  friend struct  protobuf_aptitude_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// SheetSet

// repeated .WakfuProto.Sheet sheets = 2;
inline int SheetSet::sheets_size() const {
  return sheets_.size();
}
inline void SheetSet::clear_sheets() {
  sheets_.Clear();
}
inline const ::WakfuProto::Sheet& SheetSet::sheets(int index) const {
  // @@protoc_insertion_point(field_get:WakfuProto.SheetSet.sheets)
  return sheets_.Get(index);
}
inline ::WakfuProto::Sheet* SheetSet::mutable_sheets(int index) {
  // @@protoc_insertion_point(field_mutable:WakfuProto.SheetSet.sheets)
  return sheets_.Mutable(index);
}
inline ::WakfuProto::Sheet* SheetSet::add_sheets() {
  // @@protoc_insertion_point(field_add:WakfuProto.SheetSet.sheets)
  return sheets_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::WakfuProto::Sheet >*
SheetSet::mutable_sheets() {
  // @@protoc_insertion_point(field_mutable_list:WakfuProto.SheetSet.sheets)
  return &sheets_;
}
inline const ::google::protobuf::RepeatedPtrField< ::WakfuProto::Sheet >&
SheetSet::sheets() const {
  // @@protoc_insertion_point(field_list:WakfuProto.SheetSet.sheets)
  return sheets_;
}

// -------------------------------------------------------------------

// Sheet

// required int32 index = 1;
inline bool Sheet::has_index() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Sheet::set_has_index() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Sheet::clear_has_index() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Sheet::clear_index() {
  index_ = 0;
  clear_has_index();
}
inline ::google::protobuf::int32 Sheet::index() const {
  // @@protoc_insertion_point(field_get:WakfuProto.Sheet.index)
  return index_;
}
inline void Sheet::set_index(::google::protobuf::int32 value) {
  set_has_index();
  index_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.Sheet.index)
}

// required string name = 2;
inline bool Sheet::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Sheet::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Sheet::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Sheet::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& Sheet::name() const {
  // @@protoc_insertion_point(field_get:WakfuProto.Sheet.name)
  return name_.GetNoArena();
}
inline void Sheet::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:WakfuProto.Sheet.name)
}
#if LANG_CXX11
inline void Sheet::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:WakfuProto.Sheet.name)
}
#endif
inline void Sheet::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:WakfuProto.Sheet.name)
}
inline void Sheet::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:WakfuProto.Sheet.name)
}
inline ::std::string* Sheet::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:WakfuProto.Sheet.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Sheet::release_name() {
  // @@protoc_insertion_point(field_release:WakfuProto.Sheet.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Sheet::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:WakfuProto.Sheet.name)
}

// required int32 level = 3;
inline bool Sheet::has_level() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Sheet::set_has_level() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Sheet::clear_has_level() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Sheet::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 Sheet::level() const {
  // @@protoc_insertion_point(field_get:WakfuProto.Sheet.level)
  return level_;
}
inline void Sheet::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.Sheet.level)
}

// repeated .WakfuProto.LevelsByBonus bonus = 4;
inline int Sheet::bonus_size() const {
  return bonus_.size();
}
inline void Sheet::clear_bonus() {
  bonus_.Clear();
}
inline const ::WakfuProto::LevelsByBonus& Sheet::bonus(int index) const {
  // @@protoc_insertion_point(field_get:WakfuProto.Sheet.bonus)
  return bonus_.Get(index);
}
inline ::WakfuProto::LevelsByBonus* Sheet::mutable_bonus(int index) {
  // @@protoc_insertion_point(field_mutable:WakfuProto.Sheet.bonus)
  return bonus_.Mutable(index);
}
inline ::WakfuProto::LevelsByBonus* Sheet::add_bonus() {
  // @@protoc_insertion_point(field_add:WakfuProto.Sheet.bonus)
  return bonus_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::WakfuProto::LevelsByBonus >*
Sheet::mutable_bonus() {
  // @@protoc_insertion_point(field_mutable_list:WakfuProto.Sheet.bonus)
  return &bonus_;
}
inline const ::google::protobuf::RepeatedPtrField< ::WakfuProto::LevelsByBonus >&
Sheet::bonus() const {
  // @@protoc_insertion_point(field_list:WakfuProto.Sheet.bonus)
  return bonus_;
}

// repeated .WakfuProto.CategoryPoints categoryPoints = 5;
inline int Sheet::categorypoints_size() const {
  return categorypoints_.size();
}
inline void Sheet::clear_categorypoints() {
  categorypoints_.Clear();
}
inline const ::WakfuProto::CategoryPoints& Sheet::categorypoints(int index) const {
  // @@protoc_insertion_point(field_get:WakfuProto.Sheet.categoryPoints)
  return categorypoints_.Get(index);
}
inline ::WakfuProto::CategoryPoints* Sheet::mutable_categorypoints(int index) {
  // @@protoc_insertion_point(field_mutable:WakfuProto.Sheet.categoryPoints)
  return categorypoints_.Mutable(index);
}
inline ::WakfuProto::CategoryPoints* Sheet::add_categorypoints() {
  // @@protoc_insertion_point(field_add:WakfuProto.Sheet.categoryPoints)
  return categorypoints_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::WakfuProto::CategoryPoints >*
Sheet::mutable_categorypoints() {
  // @@protoc_insertion_point(field_mutable_list:WakfuProto.Sheet.categoryPoints)
  return &categorypoints_;
}
inline const ::google::protobuf::RepeatedPtrField< ::WakfuProto::CategoryPoints >&
Sheet::categorypoints() const {
  // @@protoc_insertion_point(field_list:WakfuProto.Sheet.categoryPoints)
  return categorypoints_;
}

// -------------------------------------------------------------------

// LevelsByBonus

// required int32 bonusId = 1;
inline bool LevelsByBonus::has_bonusid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LevelsByBonus::set_has_bonusid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LevelsByBonus::clear_has_bonusid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LevelsByBonus::clear_bonusid() {
  bonusid_ = 0;
  clear_has_bonusid();
}
inline ::google::protobuf::int32 LevelsByBonus::bonusid() const {
  // @@protoc_insertion_point(field_get:WakfuProto.LevelsByBonus.bonusId)
  return bonusid_;
}
inline void LevelsByBonus::set_bonusid(::google::protobuf::int32 value) {
  set_has_bonusid();
  bonusid_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.LevelsByBonus.bonusId)
}

// required int32 level = 2;
inline bool LevelsByBonus::has_level() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LevelsByBonus::set_has_level() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LevelsByBonus::clear_has_level() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LevelsByBonus::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 LevelsByBonus::level() const {
  // @@protoc_insertion_point(field_get:WakfuProto.LevelsByBonus.level)
  return level_;
}
inline void LevelsByBonus::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.LevelsByBonus.level)
}

// -------------------------------------------------------------------

// CategoryPoints

// required int32 categoryId = 1;
inline bool CategoryPoints::has_categoryid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CategoryPoints::set_has_categoryid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CategoryPoints::clear_has_categoryid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CategoryPoints::clear_categoryid() {
  categoryid_ = 0;
  clear_has_categoryid();
}
inline ::google::protobuf::int32 CategoryPoints::categoryid() const {
  // @@protoc_insertion_point(field_get:WakfuProto.CategoryPoints.categoryId)
  return categoryid_;
}
inline void CategoryPoints::set_categoryid(::google::protobuf::int32 value) {
  set_has_categoryid();
  categoryid_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.CategoryPoints.categoryId)
}

// required int32 points = 2;
inline bool CategoryPoints::has_points() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CategoryPoints::set_has_points() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CategoryPoints::clear_has_points() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CategoryPoints::clear_points() {
  points_ = 0;
  clear_has_points();
}
inline ::google::protobuf::int32 CategoryPoints::points() const {
  // @@protoc_insertion_point(field_get:WakfuProto.CategoryPoints.points)
  return points_;
}
inline void CategoryPoints::set_points(::google::protobuf::int32 value) {
  set_has_points();
  points_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.CategoryPoints.points)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace WakfuProto

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_aptitude_2eproto__INCLUDED
