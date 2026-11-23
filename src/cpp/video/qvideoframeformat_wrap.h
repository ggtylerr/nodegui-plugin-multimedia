#pragma once
#include <napi.h>

#include <QVideoFrameFormat>

#include "QtCore/QObject/qobject_macro.h"
class QVideoFrameFormatWrap : public Napi::ObjectWrap<QVideoFrameFormatWrap> {
 private:
  std::unique_ptr<QVideoFrameFormat> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QVideoFrameFormatWrap(const Napi::CallbackInfo& info);
  ~QVideoFrameFormatWrap();
  QVideoFrameFormat *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value colorRange(const Napi::CallbackInfo& info);
  Napi::Value colorSpace(const Napi::CallbackInfo& info);
  Napi::Value colorTransfer(const Napi::CallbackInfo& info);
  Napi::Value frameHeight(const Napi::CallbackInfo& info);
  Napi::Value frameRate(const Napi::CallbackInfo& info);
  Napi::Value frameSize(const Napi::CallbackInfo& info);
  Napi::Value frameWidth(const Napi::CallbackInfo& info);
  Napi::Value isMirrored(const Napi::CallbackInfo& info);
  Napi::Value isValid(const Napi::CallbackInfo& info);
  Napi::Value pixelFormat(const Napi::CallbackInfo& info);
  Napi::Value planeCount(const Napi::CallbackInfo& info);
  Napi::Value rotation(const Napi::CallbackInfo& info);
  Napi::Value scanLineDirection(const Napi::CallbackInfo& info);
  Napi::Value setColorRange(const Napi::CallbackInfo& info);
  Napi::Value setColorSpace(const Napi::CallbackInfo& info);
  Napi::Value setColorTransfer(const Napi::CallbackInfo& info);
  Napi::Value setFrameRate(const Napi::CallbackInfo& info);
  Napi::Value setFrameSize(const Napi::CallbackInfo& info);
  Napi::Value setMaxLuminance(const Napi::CallbackInfo& info);
  Napi::Value setMirrored(const Napi::CallbackInfo& info);
  Napi::Value setRotation(const Napi::CallbackInfo& info);
  Napi::Value setScanLineDirection(const Napi::CallbackInfo& info);
  Napi::Value setStreamFrameRate(const Napi::CallbackInfo& info);
  Napi::Value setViewport(const Napi::CallbackInfo& info);
  Napi::Value streamFrameRate(const Napi::CallbackInfo& info);
  Napi::Value swap(const Napi::CallbackInfo& info);
  Napi::Value viewport(const Napi::CallbackInfo& info);
  // Operator Functions
  Napi::Value equals(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};

namespace StaticQVideoFrameFormatWrapMethods {
DLL_EXPORT Napi::Value imageFormatFromPixelFormat(const Napi::CallbackInfo& info);
DLL_EXPORT Napi::Value pixelFormatFromImageFormat(const Napi::CallbackInfo& info);
DLL_EXPORT Napi::Value pixelFormatToString(const Napi::CallbackInfo& info);
} // namespace StaticQVideoFrameFormatMethods