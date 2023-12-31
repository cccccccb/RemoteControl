// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: relay_peer.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_relay_5fpeer_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_relay_5fpeer_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_relay_5fpeer_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_relay_5fpeer_2eproto {
  static const uint32_t offsets[];
};
namespace proto {
class PeerToRelay;
struct PeerToRelayDefaultTypeInternal;
extern PeerToRelayDefaultTypeInternal _PeerToRelay_default_instance_;
class PeerToRelay_Secret;
struct PeerToRelay_SecretDefaultTypeInternal;
extern PeerToRelay_SecretDefaultTypeInternal _PeerToRelay_Secret_default_instance_;
}  // namespace proto
PROTOBUF_NAMESPACE_OPEN
template<> ::proto::PeerToRelay* Arena::CreateMaybeMessage<::proto::PeerToRelay>(Arena*);
template<> ::proto::PeerToRelay_Secret* Arena::CreateMaybeMessage<::proto::PeerToRelay_Secret>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto {

// ===================================================================

class PeerToRelay_Secret final :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:proto.PeerToRelay.Secret) */ {
 public:
  inline PeerToRelay_Secret() : PeerToRelay_Secret(nullptr) {}
  ~PeerToRelay_Secret() override;
  explicit PROTOBUF_CONSTEXPR PeerToRelay_Secret(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PeerToRelay_Secret(const PeerToRelay_Secret& from);
  PeerToRelay_Secret(PeerToRelay_Secret&& from) noexcept
    : PeerToRelay_Secret() {
    *this = ::std::move(from);
  }

  inline PeerToRelay_Secret& operator=(const PeerToRelay_Secret& from) {
    CopyFrom(from);
    return *this;
  }
  inline PeerToRelay_Secret& operator=(PeerToRelay_Secret&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const PeerToRelay_Secret& default_instance() {
    return *internal_default_instance();
  }
  static inline const PeerToRelay_Secret* internal_default_instance() {
    return reinterpret_cast<const PeerToRelay_Secret*>(
               &_PeerToRelay_Secret_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PeerToRelay_Secret& a, PeerToRelay_Secret& b) {
    a.Swap(&b);
  }
  inline void Swap(PeerToRelay_Secret* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PeerToRelay_Secret* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PeerToRelay_Secret* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PeerToRelay_Secret>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)  final;
  void CopyFrom(const PeerToRelay_Secret& from);
  void MergeFrom(const PeerToRelay_Secret& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(PeerToRelay_Secret* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto.PeerToRelay.Secret";
  }
  protected:
  explicit PeerToRelay_Secret(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRandomDataFieldNumber = 1,
    kClientAddressFieldNumber = 2,
    kClientUserNameFieldNumber = 3,
    kHostAddressFieldNumber = 4,
    kHostIdFieldNumber = 5,
  };
  // bytes random_data = 1;
  void clear_random_data();
  const std::string& random_data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_random_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_random_data();
  PROTOBUF_NODISCARD std::string* release_random_data();
  void set_allocated_random_data(std::string* random_data);
  private:
  const std::string& _internal_random_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_random_data(const std::string& value);
  std::string* _internal_mutable_random_data();
  public:

  // string client_address = 2;
  void clear_client_address();
  const std::string& client_address() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_client_address(ArgT0&& arg0, ArgT... args);
  std::string* mutable_client_address();
  PROTOBUF_NODISCARD std::string* release_client_address();
  void set_allocated_client_address(std::string* client_address);
  private:
  const std::string& _internal_client_address() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_client_address(const std::string& value);
  std::string* _internal_mutable_client_address();
  public:

  // string client_user_name = 3;
  void clear_client_user_name();
  const std::string& client_user_name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_client_user_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_client_user_name();
  PROTOBUF_NODISCARD std::string* release_client_user_name();
  void set_allocated_client_user_name(std::string* client_user_name);
  private:
  const std::string& _internal_client_user_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_client_user_name(const std::string& value);
  std::string* _internal_mutable_client_user_name();
  public:

  // string host_address = 4;
  void clear_host_address();
  const std::string& host_address() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_host_address(ArgT0&& arg0, ArgT... args);
  std::string* mutable_host_address();
  PROTOBUF_NODISCARD std::string* release_host_address();
  void set_allocated_host_address(std::string* host_address);
  private:
  const std::string& _internal_host_address() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_host_address(const std::string& value);
  std::string* _internal_mutable_host_address();
  public:

  // fixed64 host_id = 5;
  void clear_host_id();
  uint64_t host_id() const;
  void set_host_id(uint64_t value);
  private:
  uint64_t _internal_host_id() const;
  void _internal_set_host_id(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:proto.PeerToRelay.Secret)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr random_data_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr client_address_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr client_user_name_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr host_address_;
    uint64_t host_id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_relay_5fpeer_2eproto;
};
// -------------------------------------------------------------------

class PeerToRelay final :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:proto.PeerToRelay) */ {
 public:
  inline PeerToRelay() : PeerToRelay(nullptr) {}
  ~PeerToRelay() override;
  explicit PROTOBUF_CONSTEXPR PeerToRelay(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PeerToRelay(const PeerToRelay& from);
  PeerToRelay(PeerToRelay&& from) noexcept
    : PeerToRelay() {
    *this = ::std::move(from);
  }

  inline PeerToRelay& operator=(const PeerToRelay& from) {
    CopyFrom(from);
    return *this;
  }
  inline PeerToRelay& operator=(PeerToRelay&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const PeerToRelay& default_instance() {
    return *internal_default_instance();
  }
  static inline const PeerToRelay* internal_default_instance() {
    return reinterpret_cast<const PeerToRelay*>(
               &_PeerToRelay_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(PeerToRelay& a, PeerToRelay& b) {
    a.Swap(&b);
  }
  inline void Swap(PeerToRelay* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PeerToRelay* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PeerToRelay* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PeerToRelay>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)  final;
  void CopyFrom(const PeerToRelay& from);
  void MergeFrom(const PeerToRelay& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(PeerToRelay* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto.PeerToRelay";
  }
  protected:
  explicit PeerToRelay(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  typedef PeerToRelay_Secret Secret;

  // accessors -------------------------------------------------------

  enum : int {
    kPublicKeyFieldNumber = 2,
    kDataFieldNumber = 3,
    kKeyIdFieldNumber = 1,
  };
  // bytes public_key = 2;
  void clear_public_key();
  const std::string& public_key() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_public_key(ArgT0&& arg0, ArgT... args);
  std::string* mutable_public_key();
  PROTOBUF_NODISCARD std::string* release_public_key();
  void set_allocated_public_key(std::string* public_key);
  private:
  const std::string& _internal_public_key() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_public_key(const std::string& value);
  std::string* _internal_mutable_public_key();
  public:

  // bytes data = 3;
  void clear_data();
  const std::string& data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_data();
  PROTOBUF_NODISCARD std::string* release_data();
  void set_allocated_data(std::string* data);
  private:
  const std::string& _internal_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_data(const std::string& value);
  std::string* _internal_mutable_data();
  public:

  // uint32 key_id = 1;
  void clear_key_id();
  uint32_t key_id() const;
  void set_key_id(uint32_t value);
  private:
  uint32_t _internal_key_id() const;
  void _internal_set_key_id(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:proto.PeerToRelay)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr public_key_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr data_;
    uint32_t key_id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_relay_5fpeer_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PeerToRelay_Secret

// bytes random_data = 1;
inline void PeerToRelay_Secret::clear_random_data() {
  _impl_.random_data_.ClearToEmpty();
}
inline const std::string& PeerToRelay_Secret::random_data() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.Secret.random_data)
  return _internal_random_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PeerToRelay_Secret::set_random_data(ArgT0&& arg0, ArgT... args) {
 
 _impl_.random_data_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.Secret.random_data)
}
inline std::string* PeerToRelay_Secret::mutable_random_data() {
  std::string* _s = _internal_mutable_random_data();
  // @@protoc_insertion_point(field_mutable:proto.PeerToRelay.Secret.random_data)
  return _s;
}
inline const std::string& PeerToRelay_Secret::_internal_random_data() const {
  return _impl_.random_data_.Get();
}
inline void PeerToRelay_Secret::_internal_set_random_data(const std::string& value) {
  
  _impl_.random_data_.Set(value, GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::_internal_mutable_random_data() {
  
  return _impl_.random_data_.Mutable(GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::release_random_data() {
  // @@protoc_insertion_point(field_release:proto.PeerToRelay.Secret.random_data)
  return _impl_.random_data_.Release();
}
inline void PeerToRelay_Secret::set_allocated_random_data(std::string* random_data) {
  if (random_data != nullptr) {
    
  } else {
    
  }
  _impl_.random_data_.SetAllocated(random_data, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.random_data_.IsDefault()) {
    _impl_.random_data_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto.PeerToRelay.Secret.random_data)
}

// string client_address = 2;
inline void PeerToRelay_Secret::clear_client_address() {
  _impl_.client_address_.ClearToEmpty();
}
inline const std::string& PeerToRelay_Secret::client_address() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.Secret.client_address)
  return _internal_client_address();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PeerToRelay_Secret::set_client_address(ArgT0&& arg0, ArgT... args) {
 
 _impl_.client_address_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.Secret.client_address)
}
inline std::string* PeerToRelay_Secret::mutable_client_address() {
  std::string* _s = _internal_mutable_client_address();
  // @@protoc_insertion_point(field_mutable:proto.PeerToRelay.Secret.client_address)
  return _s;
}
inline const std::string& PeerToRelay_Secret::_internal_client_address() const {
  return _impl_.client_address_.Get();
}
inline void PeerToRelay_Secret::_internal_set_client_address(const std::string& value) {
  
  _impl_.client_address_.Set(value, GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::_internal_mutable_client_address() {
  
  return _impl_.client_address_.Mutable(GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::release_client_address() {
  // @@protoc_insertion_point(field_release:proto.PeerToRelay.Secret.client_address)
  return _impl_.client_address_.Release();
}
inline void PeerToRelay_Secret::set_allocated_client_address(std::string* client_address) {
  if (client_address != nullptr) {
    
  } else {
    
  }
  _impl_.client_address_.SetAllocated(client_address, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.client_address_.IsDefault()) {
    _impl_.client_address_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto.PeerToRelay.Secret.client_address)
}

// string client_user_name = 3;
inline void PeerToRelay_Secret::clear_client_user_name() {
  _impl_.client_user_name_.ClearToEmpty();
}
inline const std::string& PeerToRelay_Secret::client_user_name() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.Secret.client_user_name)
  return _internal_client_user_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PeerToRelay_Secret::set_client_user_name(ArgT0&& arg0, ArgT... args) {
 
 _impl_.client_user_name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.Secret.client_user_name)
}
inline std::string* PeerToRelay_Secret::mutable_client_user_name() {
  std::string* _s = _internal_mutable_client_user_name();
  // @@protoc_insertion_point(field_mutable:proto.PeerToRelay.Secret.client_user_name)
  return _s;
}
inline const std::string& PeerToRelay_Secret::_internal_client_user_name() const {
  return _impl_.client_user_name_.Get();
}
inline void PeerToRelay_Secret::_internal_set_client_user_name(const std::string& value) {
  
  _impl_.client_user_name_.Set(value, GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::_internal_mutable_client_user_name() {
  
  return _impl_.client_user_name_.Mutable(GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::release_client_user_name() {
  // @@protoc_insertion_point(field_release:proto.PeerToRelay.Secret.client_user_name)
  return _impl_.client_user_name_.Release();
}
inline void PeerToRelay_Secret::set_allocated_client_user_name(std::string* client_user_name) {
  if (client_user_name != nullptr) {
    
  } else {
    
  }
  _impl_.client_user_name_.SetAllocated(client_user_name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.client_user_name_.IsDefault()) {
    _impl_.client_user_name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto.PeerToRelay.Secret.client_user_name)
}

// string host_address = 4;
inline void PeerToRelay_Secret::clear_host_address() {
  _impl_.host_address_.ClearToEmpty();
}
inline const std::string& PeerToRelay_Secret::host_address() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.Secret.host_address)
  return _internal_host_address();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PeerToRelay_Secret::set_host_address(ArgT0&& arg0, ArgT... args) {
 
 _impl_.host_address_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.Secret.host_address)
}
inline std::string* PeerToRelay_Secret::mutable_host_address() {
  std::string* _s = _internal_mutable_host_address();
  // @@protoc_insertion_point(field_mutable:proto.PeerToRelay.Secret.host_address)
  return _s;
}
inline const std::string& PeerToRelay_Secret::_internal_host_address() const {
  return _impl_.host_address_.Get();
}
inline void PeerToRelay_Secret::_internal_set_host_address(const std::string& value) {
  
  _impl_.host_address_.Set(value, GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::_internal_mutable_host_address() {
  
  return _impl_.host_address_.Mutable(GetArenaForAllocation());
}
inline std::string* PeerToRelay_Secret::release_host_address() {
  // @@protoc_insertion_point(field_release:proto.PeerToRelay.Secret.host_address)
  return _impl_.host_address_.Release();
}
inline void PeerToRelay_Secret::set_allocated_host_address(std::string* host_address) {
  if (host_address != nullptr) {
    
  } else {
    
  }
  _impl_.host_address_.SetAllocated(host_address, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.host_address_.IsDefault()) {
    _impl_.host_address_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto.PeerToRelay.Secret.host_address)
}

// fixed64 host_id = 5;
inline void PeerToRelay_Secret::clear_host_id() {
  _impl_.host_id_ = uint64_t{0u};
}
inline uint64_t PeerToRelay_Secret::_internal_host_id() const {
  return _impl_.host_id_;
}
inline uint64_t PeerToRelay_Secret::host_id() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.Secret.host_id)
  return _internal_host_id();
}
inline void PeerToRelay_Secret::_internal_set_host_id(uint64_t value) {
  
  _impl_.host_id_ = value;
}
inline void PeerToRelay_Secret::set_host_id(uint64_t value) {
  _internal_set_host_id(value);
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.Secret.host_id)
}

// -------------------------------------------------------------------

// PeerToRelay

// uint32 key_id = 1;
inline void PeerToRelay::clear_key_id() {
  _impl_.key_id_ = 0u;
}
inline uint32_t PeerToRelay::_internal_key_id() const {
  return _impl_.key_id_;
}
inline uint32_t PeerToRelay::key_id() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.key_id)
  return _internal_key_id();
}
inline void PeerToRelay::_internal_set_key_id(uint32_t value) {
  
  _impl_.key_id_ = value;
}
inline void PeerToRelay::set_key_id(uint32_t value) {
  _internal_set_key_id(value);
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.key_id)
}

// bytes public_key = 2;
inline void PeerToRelay::clear_public_key() {
  _impl_.public_key_.ClearToEmpty();
}
inline const std::string& PeerToRelay::public_key() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.public_key)
  return _internal_public_key();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PeerToRelay::set_public_key(ArgT0&& arg0, ArgT... args) {
 
 _impl_.public_key_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.public_key)
}
inline std::string* PeerToRelay::mutable_public_key() {
  std::string* _s = _internal_mutable_public_key();
  // @@protoc_insertion_point(field_mutable:proto.PeerToRelay.public_key)
  return _s;
}
inline const std::string& PeerToRelay::_internal_public_key() const {
  return _impl_.public_key_.Get();
}
inline void PeerToRelay::_internal_set_public_key(const std::string& value) {
  
  _impl_.public_key_.Set(value, GetArenaForAllocation());
}
inline std::string* PeerToRelay::_internal_mutable_public_key() {
  
  return _impl_.public_key_.Mutable(GetArenaForAllocation());
}
inline std::string* PeerToRelay::release_public_key() {
  // @@protoc_insertion_point(field_release:proto.PeerToRelay.public_key)
  return _impl_.public_key_.Release();
}
inline void PeerToRelay::set_allocated_public_key(std::string* public_key) {
  if (public_key != nullptr) {
    
  } else {
    
  }
  _impl_.public_key_.SetAllocated(public_key, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.public_key_.IsDefault()) {
    _impl_.public_key_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto.PeerToRelay.public_key)
}

// bytes data = 3;
inline void PeerToRelay::clear_data() {
  _impl_.data_.ClearToEmpty();
}
inline const std::string& PeerToRelay::data() const {
  // @@protoc_insertion_point(field_get:proto.PeerToRelay.data)
  return _internal_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PeerToRelay::set_data(ArgT0&& arg0, ArgT... args) {
 
 _impl_.data_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto.PeerToRelay.data)
}
inline std::string* PeerToRelay::mutable_data() {
  std::string* _s = _internal_mutable_data();
  // @@protoc_insertion_point(field_mutable:proto.PeerToRelay.data)
  return _s;
}
inline const std::string& PeerToRelay::_internal_data() const {
  return _impl_.data_.Get();
}
inline void PeerToRelay::_internal_set_data(const std::string& value) {
  
  _impl_.data_.Set(value, GetArenaForAllocation());
}
inline std::string* PeerToRelay::_internal_mutable_data() {
  
  return _impl_.data_.Mutable(GetArenaForAllocation());
}
inline std::string* PeerToRelay::release_data() {
  // @@protoc_insertion_point(field_release:proto.PeerToRelay.data)
  return _impl_.data_.Release();
}
inline void PeerToRelay::set_allocated_data(std::string* data) {
  if (data != nullptr) {
    
  } else {
    
  }
  _impl_.data_.SetAllocated(data, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.data_.IsDefault()) {
    _impl_.data_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto.PeerToRelay.data)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_relay_5fpeer_2eproto
