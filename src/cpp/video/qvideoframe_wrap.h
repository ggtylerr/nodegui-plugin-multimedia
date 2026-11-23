#pragma once
#include <napi.h>

#include <QVideoFrame>

#include "QtCore/QObject/qobject_macro.h"

class QVideoFrameWrap : public Napi::ObjectWrap<QVideoFrameWrap> {
 private:
  std::unique_ptr<QVideoFrame> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QVideoFrameWrap(const Napi::CallbackInfo& info);
  ~QVideoFrameWrap();
  QVideoFrame *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value bits(const Napi::CallbackInfo& info);
  Napi::Value bytesPerLine(const Napi::CallbackInfo& info);
  Napi::Value endTime(const Napi::CallbackInfo& info);
  Napi::Value handleType(const Napi::CallbackInfo& info);
  Napi::Value height(const Napi::CallbackInfo& info);
  Napi::Value isMapped(const Napi::CallbackInfo& info);
  Napi::Value isReadable(const Napi::CallbackInfo& info);
  Napi::Value isValid(const Napi::CallbackInfo& info);
  Napi::Value isWritable(const Napi::CallbackInfo& info);
  Napi::Value map(const Napi::CallbackInfo& info);
  Napi::Value mapMode(const Napi::CallbackInfo& info);
  Napi::Value mappedBytes(const Napi::CallbackInfo& info);
  Napi::Value mirrored(const Napi::CallbackInfo& info);
  Napi::Value paint(const Napi::CallbackInfo& info);
  Napi::Value pixelFormat(const Napi::CallbackInfo& info);
  Napi::Value planeCount(const Napi::CallbackInfo& info);
  Napi::Value rotation(const Napi::CallbackInfo& info);
  Napi::Value setEndTime(const Napi::CallbackInfo& info);
  Napi::Value setMirrored(const Napi::CallbackInfo& info);
  Napi::Value setRotation(const Napi::CallbackInfo& info);
  Napi::Value setStartTime(const Napi::CallbackInfo& info);
  Napi::Value setStreamFrameRate(const Napi::CallbackInfo& info);
  Napi::Value setSubtitleText(const Napi::CallbackInfo& info);
  Napi::Value size(const Napi::CallbackInfo& info);
  Napi::Value startTime(const Napi::CallbackInfo& info);
  Napi::Value streamFrameRate(const Napi::CallbackInfo& info);
  Napi::Value subtitleText(const Napi::CallbackInfo& info);
  Napi::Value surfaceFormat(const Napi::CallbackInfo& info);
  Napi::Value swap(const Napi::CallbackInfo& info);
  Napi::Value toImage(const Napi::CallbackInfo& info);
  Napi::Value unmap(const Napi::CallbackInfo& info);
  Napi::Value width(const Napi::CallbackInfo& info);
  // Operator Functions
  Napi::Value equals(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};