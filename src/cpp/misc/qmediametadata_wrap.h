#pragma once
#include <napi.h>

#include <QMediaMetaData>

#include "QtCore/QObject/qobject_macro.h"

class QMediaMetaDataWrap : public Napi::ObjectWrap<QMediaMetaDataWrap> {
 private:
  std::unique_ptr<QMediaMetaData> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaMetaDataWrap(const Napi::CallbackInfo& info);
  QMediaMetaData *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value asKeyValueRange(const Napi::CallbackInfo& info);
  Napi::Value clear(const Napi::CallbackInfo& info);
  Napi::Value insert(const Napi::CallbackInfo& info);
  Napi::Value isEmpty(const Napi::CallbackInfo& info);
  Napi::Value keys(const Napi::CallbackInfo& info);
  Napi::Value remove(const Napi::CallbackInfo& info);
  Napi::Value stringValue(const Napi::CallbackInfo& info);
  Napi::Value value(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};

namespace StaticQMediaMetaDataWrapMethods {
DLL_EXPORT Napi::Value metaDataKeyToString(const Napi::CallbackInfo& info);
} // namespace StaticQMediaMetaDataWrapMethods