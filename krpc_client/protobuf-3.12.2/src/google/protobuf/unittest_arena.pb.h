// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_arena.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5farena_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5farena_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "google/protobuf/unittest_no_arena_import.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5farena_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5farena_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5farena_2eproto;
namespace proto2_arena_unittest {
class ArenaMessage;
class ArenaMessageDefaultTypeInternal;
extern ArenaMessageDefaultTypeInternal _ArenaMessage_default_instance_;
class NestedMessage;
class NestedMessageDefaultTypeInternal;
extern NestedMessageDefaultTypeInternal _NestedMessage_default_instance_;
}  // namespace proto2_arena_unittest
PROTOBUF_NAMESPACE_OPEN
template<> ::proto2_arena_unittest::ArenaMessage* Arena::CreateMaybeMessage<::proto2_arena_unittest::ArenaMessage>(Arena*);
template<> ::proto2_arena_unittest::NestedMessage* Arena::CreateMaybeMessage<::proto2_arena_unittest::NestedMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto2_arena_unittest {

// ===================================================================

class NestedMessage PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto2_arena_unittest.NestedMessage) */ {
 public:
  inline NestedMessage() : NestedMessage(nullptr) {};
  virtual ~NestedMessage();

  NestedMessage(const NestedMessage& from);
  NestedMessage(NestedMessage&& from) noexcept
    : NestedMessage() {
    *this = ::std::move(from);
  }

  inline NestedMessage& operator=(const NestedMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline NestedMessage& operator=(NestedMessage&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const NestedMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NestedMessage* internal_default_instance() {
    return reinterpret_cast<const NestedMessage*>(
               &_NestedMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(NestedMessage& a, NestedMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(NestedMessage* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(NestedMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline NestedMessage* New() const final {
    return CreateMaybeMessage<NestedMessage>(nullptr);
  }

  NestedMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<NestedMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const NestedMessage& from);
  void MergeFrom(const NestedMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NestedMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto2_arena_unittest.NestedMessage";
  }
  protected:
  explicit NestedMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_google_2fprotobuf_2funittest_5farena_2eproto);
    return ::descriptor_table_google_2fprotobuf_2funittest_5farena_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDFieldNumber = 1,
  };
  // optional int32 d = 1;
  bool has_d() const;
  private:
  bool _internal_has_d() const;
  public:
  void clear_d();
  ::PROTOBUF_NAMESPACE_ID::int32 d() const;
  void set_d(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_d() const;
  void _internal_set_d(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.NestedMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 d_;
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5farena_2eproto;
};
// -------------------------------------------------------------------

class ArenaMessage PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto2_arena_unittest.ArenaMessage) */ {
 public:
  inline ArenaMessage() : ArenaMessage(nullptr) {};
  virtual ~ArenaMessage();

  ArenaMessage(const ArenaMessage& from);
  ArenaMessage(ArenaMessage&& from) noexcept
    : ArenaMessage() {
    *this = ::std::move(from);
  }

  inline ArenaMessage& operator=(const ArenaMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline ArenaMessage& operator=(ArenaMessage&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ArenaMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ArenaMessage* internal_default_instance() {
    return reinterpret_cast<const ArenaMessage*>(
               &_ArenaMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(ArenaMessage& a, ArenaMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(ArenaMessage* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ArenaMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ArenaMessage* New() const final {
    return CreateMaybeMessage<ArenaMessage>(nullptr);
  }

  ArenaMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ArenaMessage>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ArenaMessage& from);
  void MergeFrom(const ArenaMessage& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ArenaMessage* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto2_arena_unittest.ArenaMessage";
  }
  protected:
  explicit ArenaMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_google_2fprotobuf_2funittest_5farena_2eproto);
    return ::descriptor_table_google_2fprotobuf_2funittest_5farena_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRepeatedNestedMessageFieldNumber = 1,
    kRepeatedImportNoArenaMessageFieldNumber = 2,
  };
  // repeated .proto2_arena_unittest.NestedMessage repeated_nested_message = 1;
  int repeated_nested_message_size() const;
  private:
  int _internal_repeated_nested_message_size() const;
  public:
  void clear_repeated_nested_message();
  ::proto2_arena_unittest::NestedMessage* mutable_repeated_nested_message(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >*
      mutable_repeated_nested_message();
  private:
  const ::proto2_arena_unittest::NestedMessage& _internal_repeated_nested_message(int index) const;
  ::proto2_arena_unittest::NestedMessage* _internal_add_repeated_nested_message();
  public:
  const ::proto2_arena_unittest::NestedMessage& repeated_nested_message(int index) const;
  ::proto2_arena_unittest::NestedMessage* add_repeated_nested_message();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >&
      repeated_nested_message() const;

  // repeated .proto2_arena_unittest.ImportNoArenaNestedMessage repeated_import_no_arena_message = 2;
  int repeated_import_no_arena_message_size() const;
  private:
  int _internal_repeated_import_no_arena_message_size() const;
  public:
  void clear_repeated_import_no_arena_message();
  ::proto2_arena_unittest::ImportNoArenaNestedMessage* mutable_repeated_import_no_arena_message(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >*
      mutable_repeated_import_no_arena_message();
  private:
  const ::proto2_arena_unittest::ImportNoArenaNestedMessage& _internal_repeated_import_no_arena_message(int index) const;
  ::proto2_arena_unittest::ImportNoArenaNestedMessage* _internal_add_repeated_import_no_arena_message();
  public:
  const ::proto2_arena_unittest::ImportNoArenaNestedMessage& repeated_import_no_arena_message(int index) const;
  ::proto2_arena_unittest::ImportNoArenaNestedMessage* add_repeated_import_no_arena_message();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >&
      repeated_import_no_arena_message() const;

  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.ArenaMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage > repeated_nested_message_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage > repeated_import_no_arena_message_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5farena_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NestedMessage

// optional int32 d = 1;
inline bool NestedMessage::_internal_has_d() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool NestedMessage::has_d() const {
  return _internal_has_d();
}
inline void NestedMessage::clear_d() {
  d_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NestedMessage::_internal_d() const {
  return d_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NestedMessage::d() const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.NestedMessage.d)
  return _internal_d();
}
inline void NestedMessage::_internal_set_d(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  d_ = value;
}
inline void NestedMessage::set_d(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_d(value);
  // @@protoc_insertion_point(field_set:proto2_arena_unittest.NestedMessage.d)
}

// -------------------------------------------------------------------

// ArenaMessage

// repeated .proto2_arena_unittest.NestedMessage repeated_nested_message = 1;
inline int ArenaMessage::_internal_repeated_nested_message_size() const {
  return repeated_nested_message_.size();
}
inline int ArenaMessage::repeated_nested_message_size() const {
  return _internal_repeated_nested_message_size();
}
inline void ArenaMessage::clear_repeated_nested_message() {
  repeated_nested_message_.Clear();
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::mutable_repeated_nested_message(int index) {
  // @@protoc_insertion_point(field_mutable:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return repeated_nested_message_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >*
ArenaMessage::mutable_repeated_nested_message() {
  // @@protoc_insertion_point(field_mutable_list:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return &repeated_nested_message_;
}
inline const ::proto2_arena_unittest::NestedMessage& ArenaMessage::_internal_repeated_nested_message(int index) const {
  return repeated_nested_message_.Get(index);
}
inline const ::proto2_arena_unittest::NestedMessage& ArenaMessage::repeated_nested_message(int index) const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return _internal_repeated_nested_message(index);
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::_internal_add_repeated_nested_message() {
  return repeated_nested_message_.Add();
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::add_repeated_nested_message() {
  // @@protoc_insertion_point(field_add:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return _internal_add_repeated_nested_message();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >&
ArenaMessage::repeated_nested_message() const {
  // @@protoc_insertion_point(field_list:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return repeated_nested_message_;
}

// repeated .proto2_arena_unittest.ImportNoArenaNestedMessage repeated_import_no_arena_message = 2;
inline int ArenaMessage::_internal_repeated_import_no_arena_message_size() const {
  return repeated_import_no_arena_message_.size();
}
inline int ArenaMessage::repeated_import_no_arena_message_size() const {
  return _internal_repeated_import_no_arena_message_size();
}
inline ::proto2_arena_unittest::ImportNoArenaNestedMessage* ArenaMessage::mutable_repeated_import_no_arena_message(int index) {
  // @@protoc_insertion_point(field_mutable:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return repeated_import_no_arena_message_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >*
ArenaMessage::mutable_repeated_import_no_arena_message() {
  // @@protoc_insertion_point(field_mutable_list:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return &repeated_import_no_arena_message_;
}
inline const ::proto2_arena_unittest::ImportNoArenaNestedMessage& ArenaMessage::_internal_repeated_import_no_arena_message(int index) const {
  return repeated_import_no_arena_message_.Get(index);
}
inline const ::proto2_arena_unittest::ImportNoArenaNestedMessage& ArenaMessage::repeated_import_no_arena_message(int index) const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return _internal_repeated_import_no_arena_message(index);
}
inline ::proto2_arena_unittest::ImportNoArenaNestedMessage* ArenaMessage::_internal_add_repeated_import_no_arena_message() {
  return repeated_import_no_arena_message_.Add();
}
inline ::proto2_arena_unittest::ImportNoArenaNestedMessage* ArenaMessage::add_repeated_import_no_arena_message() {
  // @@protoc_insertion_point(field_add:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return _internal_add_repeated_import_no_arena_message();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >&
ArenaMessage::repeated_import_no_arena_message() const {
  // @@protoc_insertion_point(field_list:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return repeated_import_no_arena_message_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto2_arena_unittest

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5farena_2eproto
