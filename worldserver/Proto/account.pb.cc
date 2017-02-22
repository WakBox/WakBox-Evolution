// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: account.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "account.pb.h"

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
class StatusDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<Status> {
} _Status_default_instance_;

namespace protobuf_account_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[2];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Status, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Status, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Status, status_),
  ~0u,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 5, sizeof(Status)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Status_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "account.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  const ::google::protobuf::Descriptor* Status_StatusEntry_descriptor = protobuf_account_2eproto::file_level_metadata[0].descriptor;
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Status_StatusEntry_descriptor,
        ::google::protobuf::internal::MapEntry<
            ::std::string,
            ::std::string,
            ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
            ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
            0>::CreateDefaultInstance(
                Status_StatusEntry_descriptor));
}

}  // namespace

void TableStruct::Shutdown() {
  _Status_default_instance_.Shutdown();
  delete file_level_metadata[1].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _Status_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\raccount.proto\022\nWakfuProto\"g\n\006Status\022.\n"
      "\006status\030\001 \003(\0132\036.WakfuProto.Status.Status"
      "Entry\032-\n\013StatusEntry\022\013\n\003key\030\001 \001(\t\022\r\n\005val"
      "ue\030\002 \001(\t:\0028\001"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 132);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "account.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_account_2eproto


// ===================================================================

#if PROTOBUF_INLINE_NOT_IN_HEADERS
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Status::kStatusFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Status::Status()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_account_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:WakfuProto.Status)
}
Status::Status(const Status& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  const ::google::protobuf::Descriptor*& Status_StatusEntry_descriptor = protobuf_account_2eproto::file_level_metadata[0].descriptor;
  status_.SetAssignDescriptorCallback(
      protobuf_account_2eproto::protobuf_AssignDescriptorsOnce);
  status_.SetEntryDescriptor(
      &Status_StatusEntry_descriptor);
  status_.MergeFrom(from.status_);
  // @@protoc_insertion_point(copy_constructor:WakfuProto.Status)
}

void Status::SharedCtor() {
  _cached_size_ = 0;
  const ::google::protobuf::Descriptor*& Status_StatusEntry_descriptor = protobuf_account_2eproto::file_level_metadata[0].descriptor;
  status_.SetAssignDescriptorCallback(
      protobuf_account_2eproto::protobuf_AssignDescriptorsOnce);
  status_.SetEntryDescriptor(
      &Status_StatusEntry_descriptor);
}

Status::~Status() {
  // @@protoc_insertion_point(destructor:WakfuProto.Status)
  SharedDtor();
}

void Status::SharedDtor() {
}

void Status::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Status::descriptor() {
  protobuf_account_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_account_2eproto::file_level_metadata[1].descriptor;
}

const Status& Status::default_instance() {
  protobuf_account_2eproto::InitDefaults();
  return *internal_default_instance();
}

Status* Status::New(::google::protobuf::Arena* arena) const {
  Status* n = new Status;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Status::Clear() {
// @@protoc_insertion_point(message_clear_start:WakfuProto.Status)
  status_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool Status::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WakfuProto.Status)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // map<string, string> status = 1;
      case 1: {
        if (tag == 10u) {
          DO_(input->IncrementRecursionDepth());
          Status_StatusEntry::Parser< ::google::protobuf::internal::MapField<
              ::std::string, ::std::string,
              ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
              ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
              0 >,
            ::google::protobuf::Map< ::std::string, ::std::string > > parser(&status_);
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
              input, &parser));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            parser.key().data(), parser.key().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "WakfuProto.Status.StatusEntry.key");
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            parser.value().data(), parser.value().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "WakfuProto.Status.StatusEntry.value");
        } else {
          goto handle_unusual;
        }
        input->UnsafeDecrementRecursionDepth();
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
  // @@protoc_insertion_point(parse_success:WakfuProto.Status)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WakfuProto.Status)
  return false;
#undef DO_
}

void Status::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WakfuProto.Status)
  // map<string, string> status = 1;
  if (!this->status().empty()) {
    typedef ::google::protobuf::Map< ::std::string, ::std::string >::const_pointer
        ConstPtr;
    typedef ConstPtr SortItem;
    typedef ::google::protobuf::internal::CompareByDerefFirst<SortItem> Less;
    struct Utf8Check {
      static void Check(ConstPtr p) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
          p->first.data(), p->first.length(),
          ::google::protobuf::internal::WireFormat::SERIALIZE,
          "WakfuProto.Status.StatusEntry.key");
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
          p->second.data(), p->second.length(),
          ::google::protobuf::internal::WireFormat::SERIALIZE,
          "WakfuProto.Status.StatusEntry.value");
      }
    };

    if (output->IsSerializationDeterministic() &&
        this->status().size() > 1) {
      ::google::protobuf::scoped_array<SortItem> items(
          new SortItem[this->status().size()]);
      typedef ::google::protobuf::Map< ::std::string, ::std::string >::size_type size_type;
      size_type n = 0;
      for (::google::protobuf::Map< ::std::string, ::std::string >::const_iterator
          it = this->status().begin();
          it != this->status().end(); ++it, ++n) {
        items[n] = SortItem(&*it);
      }
      ::std::sort(&items[0], &items[n], Less());
      ::google::protobuf::scoped_ptr<Status_StatusEntry> entry;
      for (size_type i = 0; i < n; i++) {
        entry.reset(status_.NewEntryWrapper(
            items[i]->first, items[i]->second));
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            1, *entry, output);
        Utf8Check::Check(items[i]);
      }
    } else {
      ::google::protobuf::scoped_ptr<Status_StatusEntry> entry;
      for (::google::protobuf::Map< ::std::string, ::std::string >::const_iterator
          it = this->status().begin();
          it != this->status().end(); ++it) {
        entry.reset(status_.NewEntryWrapper(
            it->first, it->second));
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            1, *entry, output);
        Utf8Check::Check(&*it);
      }
    }
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WakfuProto.Status)
}

::google::protobuf::uint8* Status::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:WakfuProto.Status)
  // map<string, string> status = 1;
  if (!this->status().empty()) {
    typedef ::google::protobuf::Map< ::std::string, ::std::string >::const_pointer
        ConstPtr;
    typedef ConstPtr SortItem;
    typedef ::google::protobuf::internal::CompareByDerefFirst<SortItem> Less;
    struct Utf8Check {
      static void Check(ConstPtr p) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
          p->first.data(), p->first.length(),
          ::google::protobuf::internal::WireFormat::SERIALIZE,
          "WakfuProto.Status.StatusEntry.key");
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
          p->second.data(), p->second.length(),
          ::google::protobuf::internal::WireFormat::SERIALIZE,
          "WakfuProto.Status.StatusEntry.value");
      }
    };

    if (deterministic &&
        this->status().size() > 1) {
      ::google::protobuf::scoped_array<SortItem> items(
          new SortItem[this->status().size()]);
      typedef ::google::protobuf::Map< ::std::string, ::std::string >::size_type size_type;
      size_type n = 0;
      for (::google::protobuf::Map< ::std::string, ::std::string >::const_iterator
          it = this->status().begin();
          it != this->status().end(); ++it, ++n) {
        items[n] = SortItem(&*it);
      }
      ::std::sort(&items[0], &items[n], Less());
      ::google::protobuf::scoped_ptr<Status_StatusEntry> entry;
      for (size_type i = 0; i < n; i++) {
        entry.reset(status_.NewEntryWrapper(
            items[i]->first, items[i]->second));
        target = ::google::protobuf::internal::WireFormatLite::
                   InternalWriteMessageNoVirtualToArray(
                       1, *entry, deterministic, target);
;
        Utf8Check::Check(items[i]);
      }
    } else {
      ::google::protobuf::scoped_ptr<Status_StatusEntry> entry;
      for (::google::protobuf::Map< ::std::string, ::std::string >::const_iterator
          it = this->status().begin();
          it != this->status().end(); ++it) {
        entry.reset(status_.NewEntryWrapper(
            it->first, it->second));
        target = ::google::protobuf::internal::WireFormatLite::
                   InternalWriteMessageNoVirtualToArray(
                       1, *entry, deterministic, target);
;
        Utf8Check::Check(&*it);
      }
    }
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WakfuProto.Status)
  return target;
}

size_t Status::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WakfuProto.Status)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // map<string, string> status = 1;
  total_size += 1 *
      ::google::protobuf::internal::FromIntSize(this->status_size());
  {
    ::google::protobuf::scoped_ptr<Status_StatusEntry> entry;
    for (::google::protobuf::Map< ::std::string, ::std::string >::const_iterator
        it = this->status().begin();
        it != this->status().end(); ++it) {
      entry.reset(status_.NewEntryWrapper(it->first, it->second));
      total_size += ::google::protobuf::internal::WireFormatLite::
          MessageSizeNoVirtual(*entry);
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Status::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:WakfuProto.Status)
  GOOGLE_DCHECK_NE(&from, this);
  const Status* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Status>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:WakfuProto.Status)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:WakfuProto.Status)
    MergeFrom(*source);
  }
}

void Status::MergeFrom(const Status& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:WakfuProto.Status)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  status_.MergeFrom(from.status_);
}

void Status::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:WakfuProto.Status)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Status::CopyFrom(const Status& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WakfuProto.Status)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Status::IsInitialized() const {
  return true;
}

void Status::Swap(Status* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Status::InternalSwap(Status* other) {
  status_.Swap(&other->status_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Status::GetMetadata() const {
  protobuf_account_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_account_2eproto::file_level_metadata[1];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Status

// map<string, string> status = 1;
int Status::status_size() const {
  return status_.size();
}
void Status::clear_status() {
  status_.Clear();
}
 const ::google::protobuf::Map< ::std::string, ::std::string >&
Status::status() const {
  // @@protoc_insertion_point(field_map:WakfuProto.Status.status)
  return status_.GetMap();
}
 ::google::protobuf::Map< ::std::string, ::std::string >*
Status::mutable_status() {
  // @@protoc_insertion_point(field_mutable_map:WakfuProto.Status.status)
  return status_.MutableMap();
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace WakfuProto

// @@protoc_insertion_point(global_scope)