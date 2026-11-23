#pragma once
#include <napi.h>
#include <stdlib.h>

#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"
#include "nvideosink.hpp"

class QVideoSinkWrap : public Napi::ObjectWrap<QVideoSinkWrap> {
 private:
  QPointer<NVideoSink> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QVideoSinkWrap(const Napi::CallbackInfo& info);
  ~QVideoSinkWrap();
  NVideoSink *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  // NodeGui doesn't support QRhi
//   Napi::Value rhi(const Napi::CallbackInfo& info);
  Napi::Value setSubtitleText(const Napi::CallbackInfo& info);
  Napi::Value setVideoFrame(const Napi::CallbackInfo& info);
  Napi::Value subtitleText(const Napi::CallbackInfo& info);
  Napi::Value videoFrame(const Napi::CallbackInfo& info);
  Napi::Value videoSize(const Napi::CallbackInfo& info);

  QOBJECT_WRAPPED_METHODS_DECLARATION
};