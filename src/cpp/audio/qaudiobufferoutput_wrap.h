#pragma once
#include <napi.h>

#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"
#include "naudiobufferoutput.hpp"

class QAudioBufferOutputWrap : public Napi::ObjectWrap<QAudioBufferOutputWrap> {
 private:
  QPointer<NAudioBufferOutput> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QAudioBufferOutputWrap(const Napi::CallbackInfo& info);
  ~QAudioBufferOutputWrap();
  NAudioBufferOutput *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value format(const Napi::CallbackInfo& info);

  QOBJECT_WRAPPED_METHODS_DECLARATION
};