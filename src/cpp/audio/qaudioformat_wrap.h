#pragma once
#include <napi.h>

#include <QAudioFormat>

#include "QtCore/QObject/qobject_macro.h"

class QAudioFormatWrap : public Napi::ObjectWrap<QAudioFormatWrap> {
 private:
  std::unique_ptr<QAudioFormat> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QAudioFormatWrap(const Napi::CallbackInfo& info);
  ~QAudioFormatWrap();
  QAudioFormat *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value bytesForDuration(const Napi::CallbackInfo& info);
  Napi::Value bytesForFrames(const Napi::CallbackInfo& info);
  Napi::Value bytesPerFrame(const Napi::CallbackInfo& info);
  Napi::Value bytesPerSample(const Napi::CallbackInfo& info);
  Napi::Value channelConfig(const Napi::CallbackInfo& info);
  Napi::Value channelCount(const Napi::CallbackInfo& info);
  Napi::Value channelOffset(const Napi::CallbackInfo& info);
  Napi::Value durationForBytes(const Napi::CallbackInfo& info);
  Napi::Value durationForFrames(const Napi::CallbackInfo& info);
  Napi::Value framesForBytes(const Napi::CallbackInfo& info);
  Napi::Value framesForDuration(const Napi::CallbackInfo& info);
  Napi::Value isValid(const Napi::CallbackInfo& info);
  Napi::Value normalizedSampleValue(const Napi::CallbackInfo& info);
  Napi::Value sampleFormat(const Napi::CallbackInfo& info);
  Napi::Value sampleRate(const Napi::CallbackInfo& info);
  Napi::Value setChannelConfig(const Napi::CallbackInfo& info);
  Napi::Value setChannelCount(const Napi::CallbackInfo& info);
  Napi::Value setSampleFormat(const Napi::CallbackInfo& info);
  Napi::Value setSampleRate(const Napi::CallbackInfo& info);
  // Operator Functions
  Napi::Value equals(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};

namespace StaticQAudioFormatWrapMethods {
DLL_EXPORT Napi::Value defaultChannelConfigForChannelCount(const Napi::CallbackInfo& info);
} // namespace StaticQAudioFormatWrapMethods