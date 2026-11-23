#pragma once
#include <napi.h>

#include <QAudioDevice>

#include "QtCore/QObject/qobject_macro.h"

class QAudioDeviceWrap : public Napi::ObjectWrap<QAudioDeviceWrap> {
 private:
  std::unique_ptr<QAudioDevice> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QAudioDeviceWrap(const Napi::CallbackInfo& info);
  ~QAudioDeviceWrap();
  QAudioDevice *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value channelConfiguration(const Napi::CallbackInfo& info);
  Napi::Value description(const Napi::CallbackInfo& info);
  Napi::Value id(const Napi::CallbackInfo& info);
  Napi::Value isDefault(const Napi::CallbackInfo& info);
  Napi::Value isFormatSupported(const Napi::CallbackInfo& info);
  Napi::Value isNull(const Napi::CallbackInfo& info);
  Napi::Value maximumChannelCount(const Napi::CallbackInfo& info);
  Napi::Value maximumSampleRate(const Napi::CallbackInfo& info);
  Napi::Value minimumChannelCount(const Napi::CallbackInfo& info);
  Napi::Value minimumSampleRate(const Napi::CallbackInfo& info);
  Napi::Value mode(const Napi::CallbackInfo& info);
  Napi::Value preferredFormat(const Napi::CallbackInfo& info);
  Napi::Value supportedSampleFormats(const Napi::CallbackInfo& info);
  Napi::Value swap(const Napi::CallbackInfo& info);
  // Operator Functions
  // Note: There's != as well as == but you can just use ! so...
  Napi::Value equals(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};