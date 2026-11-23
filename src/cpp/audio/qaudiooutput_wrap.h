#pragma once
#include <napi.h>
#include <stdlib.h>

#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"
#include "naudiooutput.hpp"

class QAudioOutputWrap : public Napi::ObjectWrap<QAudioOutputWrap> {
 private:
  QPointer<NAudioOutput> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QAudioOutputWrap(const Napi::CallbackInfo& info);
  NAudioOutput* getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value device(const Napi::CallbackInfo& info);
  Napi::Value isMuted(const Napi::CallbackInfo& info);
  Napi::Value volume(const Napi::CallbackInfo& info);

  // Wrapped Slots
  Napi::Value setDevice(const Napi::CallbackInfo& info);
  Napi::Value setMuted(const Napi::CallbackInfo& info);
  Napi::Value setVolume(const Napi::CallbackInfo& info);

  QOBJECT_WRAPPED_METHODS_DECLARATION
};