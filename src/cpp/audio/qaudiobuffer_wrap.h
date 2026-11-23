#pragma once
#include <napi.h>
#include <stdlib.h>

#include <QAudioBuffer>

class QAudioBufferWrap : public Napi::ObjectWrap<QAudioBufferWrap> {
 private:
  QAudioBuffer* instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QAudioBufferWrap(const Napi::CallbackInfo& info);
  ~QAudioBufferWrap();
  QAudioBuffer *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  // Napi::Value byteCount(const Napi::CallbackInfo& info);
  Napi::Value constData(const Napi::CallbackInfo& info);
  Napi::Value data(const Napi::CallbackInfo& info);
  Napi::Value detach(const Napi::CallbackInfo& info);
  Napi::Value duration(const Napi::CallbackInfo& info);
  Napi::Value format(const Napi::CallbackInfo& info);
  // Napi::Value frameCount(const Napi::CallbackInfo& info);
  Napi::Value isValid(const Napi::CallbackInfo& info);
  // Napi::Value sampleCount(const Napi::CallbackInfo& info);
  Napi::Value startTime(const Napi::CallbackInfo& info);
  Napi::Value swap(const Napi::CallbackInfo& info);
  // Napi::Value operator=(const Napi::CallbackInfo& info);
};
