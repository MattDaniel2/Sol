// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_lite_imports_nonlite.proto

#include "google/protobuf/unittest_lite_imports_nonlite.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<6> scc_info_TestAllTypes_google_2fprotobuf_2funittest_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_TestRequired_google_2fprotobuf_2funittest_2eproto;
namespace protobuf_unittest {
class TestLiteImportsNonliteDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<TestLiteImportsNonlite> _instance;
} _TestLiteImportsNonlite_default_instance_;
}  // namespace protobuf_unittest
static void InitDefaultsscc_info_TestLiteImportsNonlite_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::protobuf_unittest::_TestLiteImportsNonlite_default_instance_;
    new (ptr) ::protobuf_unittest::TestLiteImportsNonlite();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::protobuf_unittest::TestLiteImportsNonlite::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_TestLiteImportsNonlite_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 2, 0, InitDefaultsscc_info_TestLiteImportsNonlite_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto}, {
      &scc_info_TestAllTypes_google_2fprotobuf_2funittest_2eproto.base,
      &scc_info_TestRequired_google_2fprotobuf_2funittest_2eproto.base,}};

namespace protobuf_unittest {

// ===================================================================

void TestLiteImportsNonlite::InitAsDefaultInstance() {
  ::protobuf_unittest::_TestLiteImportsNonlite_default_instance_._instance.get_mutable()->message_ = const_cast< ::protobuf_unittest::TestAllTypes*>(
      ::protobuf_unittest::TestAllTypes::internal_default_instance());
  ::protobuf_unittest::_TestLiteImportsNonlite_default_instance_._instance.get_mutable()->message_with_required_ = const_cast< ::protobuf_unittest::TestRequired*>(
      ::protobuf_unittest::TestRequired::internal_default_instance());
}
class TestLiteImportsNonlite::_Internal {
 public:
  using HasBits = decltype(std::declval<TestLiteImportsNonlite>()._has_bits_);
  static const ::protobuf_unittest::TestAllTypes& message(const TestLiteImportsNonlite* msg);
  static void set_has_message(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static const ::protobuf_unittest::TestRequired& message_with_required(const TestLiteImportsNonlite* msg);
  static void set_has_message_with_required(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

const ::protobuf_unittest::TestAllTypes&
TestLiteImportsNonlite::_Internal::message(const TestLiteImportsNonlite* msg) {
  return *msg->message_;
}
const ::protobuf_unittest::TestRequired&
TestLiteImportsNonlite::_Internal::message_with_required(const TestLiteImportsNonlite* msg) {
  return *msg->message_with_required_;
}
void TestLiteImportsNonlite::clear_message() {
  if (message_ != nullptr) message_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
void TestLiteImportsNonlite::clear_message_with_required() {
  if (message_with_required_ != nullptr) message_with_required_->Clear();
  _has_bits_[0] &= ~0x00000002u;
}
TestLiteImportsNonlite::TestLiteImportsNonlite(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:protobuf_unittest.TestLiteImportsNonlite)
}
TestLiteImportsNonlite::TestLiteImportsNonlite(const TestLiteImportsNonlite& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  if (from._internal_has_message()) {
    message_ = new ::protobuf_unittest::TestAllTypes(*from.message_);
  } else {
    message_ = nullptr;
  }
  if (from._internal_has_message_with_required()) {
    message_with_required_ = new ::protobuf_unittest::TestRequired(*from.message_with_required_);
  } else {
    message_with_required_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest.TestLiteImportsNonlite)
}

void TestLiteImportsNonlite::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_TestLiteImportsNonlite_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto.base);
  ::memset(&message_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&message_with_required_) -
      reinterpret_cast<char*>(&message_)) + sizeof(message_with_required_));
}

TestLiteImportsNonlite::~TestLiteImportsNonlite() {
  // @@protoc_insertion_point(destructor:protobuf_unittest.TestLiteImportsNonlite)
  SharedDtor();
  _internal_metadata_.Delete<std::string>();
}

void TestLiteImportsNonlite::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  if (this != internal_default_instance()) delete message_;
  if (this != internal_default_instance()) delete message_with_required_;
}

void TestLiteImportsNonlite::ArenaDtor(void* object) {
  TestLiteImportsNonlite* _this = reinterpret_cast< TestLiteImportsNonlite* >(object);
  (void)_this;
}
void TestLiteImportsNonlite::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void TestLiteImportsNonlite::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const TestLiteImportsNonlite& TestLiteImportsNonlite::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_TestLiteImportsNonlite_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto.base);
  return *internal_default_instance();
}


void TestLiteImportsNonlite::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest.TestLiteImportsNonlite)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      GOOGLE_DCHECK(message_ != nullptr);
      message_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      GOOGLE_DCHECK(message_with_required_ != nullptr);
      message_with_required_->Clear();
    }
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<std::string>();
}

const char* TestLiteImportsNonlite::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional .protobuf_unittest.TestAllTypes message = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_message(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .protobuf_unittest.TestRequired message_with_required = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_message_with_required(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<std::string>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* TestLiteImportsNonlite::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protobuf_unittest.TestLiteImportsNonlite)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional .protobuf_unittest.TestAllTypes message = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::message(this), target, stream);
  }

  // optional .protobuf_unittest.TestRequired message_with_required = 2;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::message_with_required(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobuf_unittest.TestLiteImportsNonlite)
  return target;
}

size_t TestLiteImportsNonlite::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest.TestLiteImportsNonlite)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional .protobuf_unittest.TestAllTypes message = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *message_);
    }

    // optional .protobuf_unittest.TestRequired message_with_required = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *message_with_required_);
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size();
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void TestLiteImportsNonlite::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const TestLiteImportsNonlite*>(
      &from));
}

void TestLiteImportsNonlite::MergeFrom(const TestLiteImportsNonlite& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest.TestLiteImportsNonlite)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_message()->::protobuf_unittest::TestAllTypes::MergeFrom(from._internal_message());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_mutable_message_with_required()->::protobuf_unittest::TestRequired::MergeFrom(from._internal_message_with_required());
    }
  }
}

void TestLiteImportsNonlite::CopyFrom(const TestLiteImportsNonlite& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest.TestLiteImportsNonlite)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestLiteImportsNonlite::IsInitialized() const {
  if (_internal_has_message_with_required()) {
    if (!message_with_required_->IsInitialized()) return false;
  }
  return true;
}

void TestLiteImportsNonlite::InternalSwap(TestLiteImportsNonlite* other) {
  using std::swap;
  _internal_metadata_.Swap<std::string>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, message_with_required_)
      + sizeof(TestLiteImportsNonlite::message_with_required_)
      - PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, message_)>(
          reinterpret_cast<char*>(&message_),
          reinterpret_cast<char*>(&other->message_));
}

std::string TestLiteImportsNonlite::GetTypeName() const {
  return "protobuf_unittest.TestLiteImportsNonlite";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::protobuf_unittest::TestLiteImportsNonlite* Arena::CreateMaybeMessage< ::protobuf_unittest::TestLiteImportsNonlite >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protobuf_unittest::TestLiteImportsNonlite >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
