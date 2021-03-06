// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: dimensionalBag.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "dimensionalBag.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace WakfuProto {
class ProtoDimensionalBagCraftFeeDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<ProtoDimensionalBagCraftFee> {
} _ProtoDimensionalBagCraftFee_default_instance_;
class ProtoDimensionalBagCategoryFeeDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<ProtoDimensionalBagCategoryFee> {
} _ProtoDimensionalBagCategoryFee_default_instance_;

namespace protobuf_dimensionalBag_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[2];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCraftFee, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCraftFee, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCraftFee, categoryfee_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCraftFee, isfreeforfriends_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCraftFee, isfreeforguild_),
  ~0u,
  0,
  1,
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCategoryFee, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCategoryFee, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCategoryFee, categoryindex_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCategoryFee, equipmentcraftfee_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProtoDimensionalBagCategoryFee, componentcraftfee_),
  0,
  1,
  2,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 7, sizeof(ProtoDimensionalBagCraftFee)},
  { 10, 17, sizeof(ProtoDimensionalBagCategoryFee)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_ProtoDimensionalBagCraftFee_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_ProtoDimensionalBagCategoryFee_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "dimensionalBag.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

}  // namespace

void TableStruct::Shutdown() {
  _ProtoDimensionalBagCraftFee_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
  _ProtoDimensionalBagCategoryFee_default_instance_.Shutdown();
  delete file_level_metadata[1].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _ProtoDimensionalBagCraftFee_default_instance_.DefaultConstruct();
  _ProtoDimensionalBagCategoryFee_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\024dimensionalBag.proto\022\nWakfuProto\"\220\001\n\033P"
      "rotoDimensionalBagCraftFee\022\?\n\013categoryFe"
      "e\030\001 \003(\0132*.WakfuProto.ProtoDimensionalBag"
      "CategoryFee\022\030\n\020isFreeForFriends\030\002 \002(\010\022\026\n"
      "\016isFreeForGuild\030\003 \002(\010\"m\n\036ProtoDimensiona"
      "lBagCategoryFee\022\025\n\rcategoryIndex\030\001 \002(\005\022\031"
      "\n\021equipmentCraftFee\030\002 \002(\005\022\031\n\021componentCr"
      "aftFee\030\003 \002(\005"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 292);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "dimensionalBag.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_dimensionalBag_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ProtoDimensionalBagCraftFee::kCategoryFeeFieldNumber;
const int ProtoDimensionalBagCraftFee::kIsFreeForFriendsFieldNumber;
const int ProtoDimensionalBagCraftFee::kIsFreeForGuildFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ProtoDimensionalBagCraftFee::ProtoDimensionalBagCraftFee()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_dimensionalBag_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:WakfuProto.ProtoDimensionalBagCraftFee)
}
ProtoDimensionalBagCraftFee::ProtoDimensionalBagCraftFee(const ProtoDimensionalBagCraftFee& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      categoryfee_(from.categoryfee_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&isfreeforfriends_, &from.isfreeforfriends_,
    reinterpret_cast<char*>(&isfreeforguild_) -
    reinterpret_cast<char*>(&isfreeforfriends_) + sizeof(isfreeforguild_));
  // @@protoc_insertion_point(copy_constructor:WakfuProto.ProtoDimensionalBagCraftFee)
}

void ProtoDimensionalBagCraftFee::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&isfreeforfriends_, 0, reinterpret_cast<char*>(&isfreeforguild_) -
    reinterpret_cast<char*>(&isfreeforfriends_) + sizeof(isfreeforguild_));
}

ProtoDimensionalBagCraftFee::~ProtoDimensionalBagCraftFee() {
  // @@protoc_insertion_point(destructor:WakfuProto.ProtoDimensionalBagCraftFee)
  SharedDtor();
}

void ProtoDimensionalBagCraftFee::SharedDtor() {
}

void ProtoDimensionalBagCraftFee::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ProtoDimensionalBagCraftFee::descriptor() {
  protobuf_dimensionalBag_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_dimensionalBag_2eproto::file_level_metadata[0].descriptor;
}

const ProtoDimensionalBagCraftFee& ProtoDimensionalBagCraftFee::default_instance() {
  protobuf_dimensionalBag_2eproto::InitDefaults();
  return *internal_default_instance();
}

ProtoDimensionalBagCraftFee* ProtoDimensionalBagCraftFee::New(::google::protobuf::Arena* arena) const {
  ProtoDimensionalBagCraftFee* n = new ProtoDimensionalBagCraftFee;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ProtoDimensionalBagCraftFee::Clear() {
// @@protoc_insertion_point(message_clear_start:WakfuProto.ProtoDimensionalBagCraftFee)
  categoryfee_.Clear();
  if (_has_bits_[0 / 32] & 3u) {
    ::memset(&isfreeforfriends_, 0, reinterpret_cast<char*>(&isfreeforguild_) -
      reinterpret_cast<char*>(&isfreeforfriends_) + sizeof(isfreeforguild_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool ProtoDimensionalBagCraftFee::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WakfuProto.ProtoDimensionalBagCraftFee)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .WakfuProto.ProtoDimensionalBagCategoryFee categoryFee = 1;
      case 1: {
        if (tag == 10u) {
          DO_(input->IncrementRecursionDepth());
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                input, add_categoryfee()));
        } else {
          goto handle_unusual;
        }
        input->UnsafeDecrementRecursionDepth();
        break;
      }

      // required bool isFreeForFriends = 2;
      case 2: {
        if (tag == 16u) {
          set_has_isfreeforfriends();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isfreeforfriends_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required bool isFreeForGuild = 3;
      case 3: {
        if (tag == 24u) {
          set_has_isfreeforguild();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isfreeforguild_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:WakfuProto.ProtoDimensionalBagCraftFee)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WakfuProto.ProtoDimensionalBagCraftFee)
  return false;
#undef DO_
}

void ProtoDimensionalBagCraftFee::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WakfuProto.ProtoDimensionalBagCraftFee)
  // repeated .WakfuProto.ProtoDimensionalBagCategoryFee categoryFee = 1;
  for (unsigned int i = 0, n = this->categoryfee_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->categoryfee(i), output);
  }

  // required bool isFreeForFriends = 2;
  if (has_isfreeforfriends()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->isfreeforfriends(), output);
  }

  // required bool isFreeForGuild = 3;
  if (has_isfreeforguild()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->isfreeforguild(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WakfuProto.ProtoDimensionalBagCraftFee)
}

::google::protobuf::uint8* ProtoDimensionalBagCraftFee::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:WakfuProto.ProtoDimensionalBagCraftFee)
  // repeated .WakfuProto.ProtoDimensionalBagCategoryFee categoryFee = 1;
  for (unsigned int i = 0, n = this->categoryfee_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, this->categoryfee(i), false, target);
  }

  // required bool isFreeForFriends = 2;
  if (has_isfreeforfriends()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->isfreeforfriends(), target);
  }

  // required bool isFreeForGuild = 3;
  if (has_isfreeforguild()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->isfreeforguild(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WakfuProto.ProtoDimensionalBagCraftFee)
  return target;
}

size_t ProtoDimensionalBagCraftFee::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:WakfuProto.ProtoDimensionalBagCraftFee)
  size_t total_size = 0;

  if (has_isfreeforfriends()) {
    // required bool isFreeForFriends = 2;
    total_size += 1 + 1;
  }

  if (has_isfreeforguild()) {
    // required bool isFreeForGuild = 3;
    total_size += 1 + 1;
  }

  return total_size;
}
size_t ProtoDimensionalBagCraftFee::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WakfuProto.ProtoDimensionalBagCraftFee)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required bool isFreeForFriends = 2;
    total_size += 1 + 1;

    // required bool isFreeForGuild = 3;
    total_size += 1 + 1;

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // repeated .WakfuProto.ProtoDimensionalBagCategoryFee categoryFee = 1;
  {
    unsigned int count = this->categoryfee_size();
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->categoryfee(i));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ProtoDimensionalBagCraftFee::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:WakfuProto.ProtoDimensionalBagCraftFee)
  GOOGLE_DCHECK_NE(&from, this);
  const ProtoDimensionalBagCraftFee* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ProtoDimensionalBagCraftFee>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:WakfuProto.ProtoDimensionalBagCraftFee)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:WakfuProto.ProtoDimensionalBagCraftFee)
    MergeFrom(*source);
  }
}

void ProtoDimensionalBagCraftFee::MergeFrom(const ProtoDimensionalBagCraftFee& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:WakfuProto.ProtoDimensionalBagCraftFee)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  categoryfee_.MergeFrom(from.categoryfee_);
  if (from._has_bits_[0 / 32] & 3u) {
    if (from.has_isfreeforfriends()) {
      set_isfreeforfriends(from.isfreeforfriends());
    }
    if (from.has_isfreeforguild()) {
      set_isfreeforguild(from.isfreeforguild());
    }
  }
}

void ProtoDimensionalBagCraftFee::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:WakfuProto.ProtoDimensionalBagCraftFee)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ProtoDimensionalBagCraftFee::CopyFrom(const ProtoDimensionalBagCraftFee& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WakfuProto.ProtoDimensionalBagCraftFee)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProtoDimensionalBagCraftFee::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->categoryfee())) return false;
  return true;
}

void ProtoDimensionalBagCraftFee::Swap(ProtoDimensionalBagCraftFee* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ProtoDimensionalBagCraftFee::InternalSwap(ProtoDimensionalBagCraftFee* other) {
  categoryfee_.UnsafeArenaSwap(&other->categoryfee_);
  std::swap(isfreeforfriends_, other->isfreeforfriends_);
  std::swap(isfreeforguild_, other->isfreeforguild_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ProtoDimensionalBagCraftFee::GetMetadata() const {
  protobuf_dimensionalBag_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_dimensionalBag_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ProtoDimensionalBagCraftFee

// repeated .WakfuProto.ProtoDimensionalBagCategoryFee categoryFee = 1;
int ProtoDimensionalBagCraftFee::categoryfee_size() const {
  return categoryfee_.size();
}
void ProtoDimensionalBagCraftFee::clear_categoryfee() {
  categoryfee_.Clear();
}
const ::WakfuProto::ProtoDimensionalBagCategoryFee& ProtoDimensionalBagCraftFee::categoryfee(int index) const {
  // @@protoc_insertion_point(field_get:WakfuProto.ProtoDimensionalBagCraftFee.categoryFee)
  return categoryfee_.Get(index);
}
::WakfuProto::ProtoDimensionalBagCategoryFee* ProtoDimensionalBagCraftFee::mutable_categoryfee(int index) {
  // @@protoc_insertion_point(field_mutable:WakfuProto.ProtoDimensionalBagCraftFee.categoryFee)
  return categoryfee_.Mutable(index);
}
::WakfuProto::ProtoDimensionalBagCategoryFee* ProtoDimensionalBagCraftFee::add_categoryfee() {
  // @@protoc_insertion_point(field_add:WakfuProto.ProtoDimensionalBagCraftFee.categoryFee)
  return categoryfee_.Add();
}
::google::protobuf::RepeatedPtrField< ::WakfuProto::ProtoDimensionalBagCategoryFee >*
ProtoDimensionalBagCraftFee::mutable_categoryfee() {
  // @@protoc_insertion_point(field_mutable_list:WakfuProto.ProtoDimensionalBagCraftFee.categoryFee)
  return &categoryfee_;
}
const ::google::protobuf::RepeatedPtrField< ::WakfuProto::ProtoDimensionalBagCategoryFee >&
ProtoDimensionalBagCraftFee::categoryfee() const {
  // @@protoc_insertion_point(field_list:WakfuProto.ProtoDimensionalBagCraftFee.categoryFee)
  return categoryfee_;
}

// required bool isFreeForFriends = 2;
bool ProtoDimensionalBagCraftFee::has_isfreeforfriends() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ProtoDimensionalBagCraftFee::set_has_isfreeforfriends() {
  _has_bits_[0] |= 0x00000001u;
}
void ProtoDimensionalBagCraftFee::clear_has_isfreeforfriends() {
  _has_bits_[0] &= ~0x00000001u;
}
void ProtoDimensionalBagCraftFee::clear_isfreeforfriends() {
  isfreeforfriends_ = false;
  clear_has_isfreeforfriends();
}
bool ProtoDimensionalBagCraftFee::isfreeforfriends() const {
  // @@protoc_insertion_point(field_get:WakfuProto.ProtoDimensionalBagCraftFee.isFreeForFriends)
  return isfreeforfriends_;
}
void ProtoDimensionalBagCraftFee::set_isfreeforfriends(bool value) {
  set_has_isfreeforfriends();
  isfreeforfriends_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.ProtoDimensionalBagCraftFee.isFreeForFriends)
}

// required bool isFreeForGuild = 3;
bool ProtoDimensionalBagCraftFee::has_isfreeforguild() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void ProtoDimensionalBagCraftFee::set_has_isfreeforguild() {
  _has_bits_[0] |= 0x00000002u;
}
void ProtoDimensionalBagCraftFee::clear_has_isfreeforguild() {
  _has_bits_[0] &= ~0x00000002u;
}
void ProtoDimensionalBagCraftFee::clear_isfreeforguild() {
  isfreeforguild_ = false;
  clear_has_isfreeforguild();
}
bool ProtoDimensionalBagCraftFee::isfreeforguild() const {
  // @@protoc_insertion_point(field_get:WakfuProto.ProtoDimensionalBagCraftFee.isFreeForGuild)
  return isfreeforguild_;
}
void ProtoDimensionalBagCraftFee::set_isfreeforguild(bool value) {
  set_has_isfreeforguild();
  isfreeforguild_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.ProtoDimensionalBagCraftFee.isFreeForGuild)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ProtoDimensionalBagCategoryFee::kCategoryIndexFieldNumber;
const int ProtoDimensionalBagCategoryFee::kEquipmentCraftFeeFieldNumber;
const int ProtoDimensionalBagCategoryFee::kComponentCraftFeeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ProtoDimensionalBagCategoryFee::ProtoDimensionalBagCategoryFee()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_dimensionalBag_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:WakfuProto.ProtoDimensionalBagCategoryFee)
}
ProtoDimensionalBagCategoryFee::ProtoDimensionalBagCategoryFee(const ProtoDimensionalBagCategoryFee& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&categoryindex_, &from.categoryindex_,
    reinterpret_cast<char*>(&componentcraftfee_) -
    reinterpret_cast<char*>(&categoryindex_) + sizeof(componentcraftfee_));
  // @@protoc_insertion_point(copy_constructor:WakfuProto.ProtoDimensionalBagCategoryFee)
}

void ProtoDimensionalBagCategoryFee::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&categoryindex_, 0, reinterpret_cast<char*>(&componentcraftfee_) -
    reinterpret_cast<char*>(&categoryindex_) + sizeof(componentcraftfee_));
}

ProtoDimensionalBagCategoryFee::~ProtoDimensionalBagCategoryFee() {
  // @@protoc_insertion_point(destructor:WakfuProto.ProtoDimensionalBagCategoryFee)
  SharedDtor();
}

void ProtoDimensionalBagCategoryFee::SharedDtor() {
}

void ProtoDimensionalBagCategoryFee::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ProtoDimensionalBagCategoryFee::descriptor() {
  protobuf_dimensionalBag_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_dimensionalBag_2eproto::file_level_metadata[1].descriptor;
}

const ProtoDimensionalBagCategoryFee& ProtoDimensionalBagCategoryFee::default_instance() {
  protobuf_dimensionalBag_2eproto::InitDefaults();
  return *internal_default_instance();
}

ProtoDimensionalBagCategoryFee* ProtoDimensionalBagCategoryFee::New(::google::protobuf::Arena* arena) const {
  ProtoDimensionalBagCategoryFee* n = new ProtoDimensionalBagCategoryFee;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ProtoDimensionalBagCategoryFee::Clear() {
// @@protoc_insertion_point(message_clear_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  if (_has_bits_[0 / 32] & 7u) {
    ::memset(&categoryindex_, 0, reinterpret_cast<char*>(&componentcraftfee_) -
      reinterpret_cast<char*>(&categoryindex_) + sizeof(componentcraftfee_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool ProtoDimensionalBagCategoryFee::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 categoryIndex = 1;
      case 1: {
        if (tag == 8u) {
          set_has_categoryindex();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &categoryindex_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 equipmentCraftFee = 2;
      case 2: {
        if (tag == 16u) {
          set_has_equipmentcraftfee();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &equipmentcraftfee_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 componentCraftFee = 3;
      case 3: {
        if (tag == 24u) {
          set_has_componentcraftfee();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &componentcraftfee_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:WakfuProto.ProtoDimensionalBagCategoryFee)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WakfuProto.ProtoDimensionalBagCategoryFee)
  return false;
#undef DO_
}

void ProtoDimensionalBagCategoryFee::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  // required int32 categoryIndex = 1;
  if (has_categoryindex()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->categoryindex(), output);
  }

  // required int32 equipmentCraftFee = 2;
  if (has_equipmentcraftfee()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->equipmentcraftfee(), output);
  }

  // required int32 componentCraftFee = 3;
  if (has_componentcraftfee()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->componentcraftfee(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WakfuProto.ProtoDimensionalBagCategoryFee)
}

::google::protobuf::uint8* ProtoDimensionalBagCategoryFee::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  // required int32 categoryIndex = 1;
  if (has_categoryindex()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->categoryindex(), target);
  }

  // required int32 equipmentCraftFee = 2;
  if (has_equipmentcraftfee()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->equipmentcraftfee(), target);
  }

  // required int32 componentCraftFee = 3;
  if (has_componentcraftfee()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->componentcraftfee(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WakfuProto.ProtoDimensionalBagCategoryFee)
  return target;
}

size_t ProtoDimensionalBagCategoryFee::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  size_t total_size = 0;

  if (has_categoryindex()) {
    // required int32 categoryIndex = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->categoryindex());
  }

  if (has_equipmentcraftfee()) {
    // required int32 equipmentCraftFee = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->equipmentcraftfee());
  }

  if (has_componentcraftfee()) {
    // required int32 componentCraftFee = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->componentcraftfee());
  }

  return total_size;
}
size_t ProtoDimensionalBagCategoryFee::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required int32 categoryIndex = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->categoryindex());

    // required int32 equipmentCraftFee = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->equipmentcraftfee());

    // required int32 componentCraftFee = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->componentcraftfee());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ProtoDimensionalBagCategoryFee::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  GOOGLE_DCHECK_NE(&from, this);
  const ProtoDimensionalBagCategoryFee* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ProtoDimensionalBagCategoryFee>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:WakfuProto.ProtoDimensionalBagCategoryFee)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:WakfuProto.ProtoDimensionalBagCategoryFee)
    MergeFrom(*source);
  }
}

void ProtoDimensionalBagCategoryFee::MergeFrom(const ProtoDimensionalBagCategoryFee& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 7u) {
    if (from.has_categoryindex()) {
      set_categoryindex(from.categoryindex());
    }
    if (from.has_equipmentcraftfee()) {
      set_equipmentcraftfee(from.equipmentcraftfee());
    }
    if (from.has_componentcraftfee()) {
      set_componentcraftfee(from.componentcraftfee());
    }
  }
}

void ProtoDimensionalBagCategoryFee::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ProtoDimensionalBagCategoryFee::CopyFrom(const ProtoDimensionalBagCategoryFee& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WakfuProto.ProtoDimensionalBagCategoryFee)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProtoDimensionalBagCategoryFee::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  return true;
}

void ProtoDimensionalBagCategoryFee::Swap(ProtoDimensionalBagCategoryFee* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ProtoDimensionalBagCategoryFee::InternalSwap(ProtoDimensionalBagCategoryFee* other) {
  std::swap(categoryindex_, other->categoryindex_);
  std::swap(equipmentcraftfee_, other->equipmentcraftfee_);
  std::swap(componentcraftfee_, other->componentcraftfee_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ProtoDimensionalBagCategoryFee::GetMetadata() const {
  protobuf_dimensionalBag_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_dimensionalBag_2eproto::file_level_metadata[1];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ProtoDimensionalBagCategoryFee

// required int32 categoryIndex = 1;
bool ProtoDimensionalBagCategoryFee::has_categoryindex() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ProtoDimensionalBagCategoryFee::set_has_categoryindex() {
  _has_bits_[0] |= 0x00000001u;
}
void ProtoDimensionalBagCategoryFee::clear_has_categoryindex() {
  _has_bits_[0] &= ~0x00000001u;
}
void ProtoDimensionalBagCategoryFee::clear_categoryindex() {
  categoryindex_ = 0;
  clear_has_categoryindex();
}
::google::protobuf::int32 ProtoDimensionalBagCategoryFee::categoryindex() const {
  // @@protoc_insertion_point(field_get:WakfuProto.ProtoDimensionalBagCategoryFee.categoryIndex)
  return categoryindex_;
}
void ProtoDimensionalBagCategoryFee::set_categoryindex(::google::protobuf::int32 value) {
  set_has_categoryindex();
  categoryindex_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.ProtoDimensionalBagCategoryFee.categoryIndex)
}

// required int32 equipmentCraftFee = 2;
bool ProtoDimensionalBagCategoryFee::has_equipmentcraftfee() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void ProtoDimensionalBagCategoryFee::set_has_equipmentcraftfee() {
  _has_bits_[0] |= 0x00000002u;
}
void ProtoDimensionalBagCategoryFee::clear_has_equipmentcraftfee() {
  _has_bits_[0] &= ~0x00000002u;
}
void ProtoDimensionalBagCategoryFee::clear_equipmentcraftfee() {
  equipmentcraftfee_ = 0;
  clear_has_equipmentcraftfee();
}
::google::protobuf::int32 ProtoDimensionalBagCategoryFee::equipmentcraftfee() const {
  // @@protoc_insertion_point(field_get:WakfuProto.ProtoDimensionalBagCategoryFee.equipmentCraftFee)
  return equipmentcraftfee_;
}
void ProtoDimensionalBagCategoryFee::set_equipmentcraftfee(::google::protobuf::int32 value) {
  set_has_equipmentcraftfee();
  equipmentcraftfee_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.ProtoDimensionalBagCategoryFee.equipmentCraftFee)
}

// required int32 componentCraftFee = 3;
bool ProtoDimensionalBagCategoryFee::has_componentcraftfee() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void ProtoDimensionalBagCategoryFee::set_has_componentcraftfee() {
  _has_bits_[0] |= 0x00000004u;
}
void ProtoDimensionalBagCategoryFee::clear_has_componentcraftfee() {
  _has_bits_[0] &= ~0x00000004u;
}
void ProtoDimensionalBagCategoryFee::clear_componentcraftfee() {
  componentcraftfee_ = 0;
  clear_has_componentcraftfee();
}
::google::protobuf::int32 ProtoDimensionalBagCategoryFee::componentcraftfee() const {
  // @@protoc_insertion_point(field_get:WakfuProto.ProtoDimensionalBagCategoryFee.componentCraftFee)
  return componentcraftfee_;
}
void ProtoDimensionalBagCategoryFee::set_componentcraftfee(::google::protobuf::int32 value) {
  set_has_componentcraftfee();
  componentcraftfee_ = value;
  // @@protoc_insertion_point(field_set:WakfuProto.ProtoDimensionalBagCategoryFee.componentCraftFee)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace WakfuProto

// @@protoc_insertion_point(global_scope)
