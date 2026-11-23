#pragma once
#include <napi.h>

#include <QAbstractVideoBuffer>

#include "QtCore/QObject/qobject_macro.h"

class QAbstractVideoBufferWrap : public Napi::ObjectWrap<QAbstractVideoBufferWrap> {
 private:
  std::unique_ptr<QAbstractVideoBuffer> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QAbstractVideoBufferWrap(const Napi::CallbackInfo& info);
  ~QAbstractVideoBufferWrap();
  QAbstractVideoBuffer *getInternalInstance();
  std::unique_ptr<QAbstractVideoBuffer> takeInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value format(const Napi::CallbackInfo& info);
  Napi::Value map(const Napi::CallbackInfo& info);
  Napi::Value unmap(const Napi::CallbackInfo& info);
  // Struct Conversion Functions
  static Napi::Object mapDataToN(const Napi::Env& env, const QAbstractVideoBuffer::MapData& mapdata);
  static QAbstractVideoBuffer::MapData NToMapData(const Napi::Value& value);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};