// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_HYPERIONREPLY_HYPERIONNET_H_
#define FLATBUFFERS_GENERATED_HYPERIONREPLY_HYPERIONNET_H_

#include "flatbuffers/flatbuffers.h"

namespace hyperionnet {

struct Reply;
struct ReplyBuilder;
struct ReplyT;

struct ReplyT : public flatbuffers::NativeTable {
  typedef Reply TableType;
  std::string error;
  int32_t video;
  int32_t registered;
  ReplyT()
      : video(-1),
        registered(-1) {
  }
};

struct Reply FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ReplyT NativeTableType;
  typedef ReplyBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ERROR = 4,
    VT_VIDEO = 6,
    VT_REGISTERED = 8
  };
  const flatbuffers::String *error() const {
    return GetPointer<const flatbuffers::String *>(VT_ERROR);
  }
  flatbuffers::String *mutable_error() {
    return GetPointer<flatbuffers::String *>(VT_ERROR);
  }
  int32_t video() const {
    return GetField<int32_t>(VT_VIDEO, -1);
  }
  bool mutate_video(int32_t _video) {
    return SetField<int32_t>(VT_VIDEO, _video, -1);
  }
  int32_t registered() const {
    return GetField<int32_t>(VT_REGISTERED, -1);
  }
  bool mutate_registered(int32_t _registered) {
    return SetField<int32_t>(VT_REGISTERED, _registered, -1);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ERROR) &&
           verifier.VerifyString(error()) &&
           VerifyField<int32_t>(verifier, VT_VIDEO) &&
           VerifyField<int32_t>(verifier, VT_REGISTERED) &&
           verifier.EndTable();
  }
  ReplyT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ReplyT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Reply> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ReplyT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ReplyBuilder {
  typedef Reply Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_error(flatbuffers::Offset<flatbuffers::String> error) {
    fbb_.AddOffset(Reply::VT_ERROR, error);
  }
  void add_video(int32_t video) {
    fbb_.AddElement<int32_t>(Reply::VT_VIDEO, video, -1);
  }
  void add_registered(int32_t registered) {
    fbb_.AddElement<int32_t>(Reply::VT_REGISTERED, registered, -1);
  }
  explicit ReplyBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Reply> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Reply>(end);
    return o;
  }
};

inline flatbuffers::Offset<Reply> CreateReply(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> error = 0,
    int32_t video = -1,
    int32_t registered = -1) {
  ReplyBuilder builder_(_fbb);
  builder_.add_registered(registered);
  builder_.add_video(video);
  builder_.add_error(error);
  return builder_.Finish();
}

inline flatbuffers::Offset<Reply> CreateReplyDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *error = nullptr,
    int32_t video = -1,
    int32_t registered = -1) {
  auto error__ = error ? _fbb.CreateString(error) : 0;
  return hyperionnet::CreateReply(
      _fbb,
      error__,
      video,
      registered);
}

flatbuffers::Offset<Reply> CreateReply(flatbuffers::FlatBufferBuilder &_fbb, const ReplyT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ReplyT *Reply::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  std::unique_ptr<hyperionnet::ReplyT> _o = std::unique_ptr<hyperionnet::ReplyT>(new ReplyT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Reply::UnPackTo(ReplyT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = error(); if (_e) _o->error = _e->str(); }
  { auto _e = video(); _o->video = _e; }
  { auto _e = registered(); _o->registered = _e; }
}

inline flatbuffers::Offset<Reply> Reply::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ReplyT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateReply(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Reply> CreateReply(flatbuffers::FlatBufferBuilder &_fbb, const ReplyT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ReplyT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _error = _o->error.empty() ? 0 : _fbb.CreateString(_o->error);
  auto _video = _o->video;
  auto _registered = _o->registered;
  return hyperionnet::CreateReply(
      _fbb,
      _error,
      _video,
      _registered);
}

inline const hyperionnet::Reply *GetReply(const void *buf) {
  return flatbuffers::GetRoot<hyperionnet::Reply>(buf);
}

inline const hyperionnet::Reply *GetSizePrefixedReply(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<hyperionnet::Reply>(buf);
}

inline Reply *GetMutableReply(void *buf) {
  return flatbuffers::GetMutableRoot<Reply>(buf);
}

inline bool VerifyReplyBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<hyperionnet::Reply>(nullptr);
}

inline bool VerifySizePrefixedReplyBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<hyperionnet::Reply>(nullptr);
}

inline void FinishReplyBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<hyperionnet::Reply> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedReplyBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<hyperionnet::Reply> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<hyperionnet::ReplyT> UnPackReply(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<hyperionnet::ReplyT>(GetReply(buf)->UnPack(res));
}

inline std::unique_ptr<hyperionnet::ReplyT> UnPackSizePrefixedReply(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<hyperionnet::ReplyT>(GetSizePrefixedReply(buf)->UnPack(res));
}

}  // namespace hyperionnet

#endif  // FLATBUFFERS_GENERATED_HYPERIONREPLY_HYPERIONNET_H_
