#include "qcameraformat_wrap.h"

#include <QCameraFormat>

#include "QtCore/QSize/qsize_wrap.h"

Napi::FunctionReference QCameraFormatWrap::constructor;

Napi::Object QCameraFormatWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(
      env, "QCameraFormat",
      {InstanceMethod("isNull", &QCameraFormatWrap::isNull),
       InstanceMethod("maxFrameRate", &QCameraFormatWrap::maxFrameRate),
       InstanceMethod("minFrameRate", &QCameraFormatWrap::minFrameRate),
       InstanceMethod("pixelFormat", &QCameraFormatWrap::pixelFormat),
       InstanceMethod("resolution", &QCameraFormatWrap::resolution),
       InstanceMethod("equals", &QCameraFormatWrap::equals),
       COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QCameraFormatWrap)});
  constructor = Napi::Persistent(func);
  exports.Set("QCameraFormat", func);
  return exports;
}

QCameraFormatWrap::QCameraFormatWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QCameraFormatWrap>(info) {
  Napi::Env env = info.Env();
  if (info.Length() == 0) {
    this->instance = std::make_unique<QCameraFormat>();
  } else if (info.Length() == 1 && info[0].IsExternal()) {
    this->instance.reset(info[0].As<Napi::External<QCameraFormat>>().Data());
  } else {
    Napi::TypeError::New(
        env, "Wrong number/type of arguments, refer to QCameraFormat()")
        .ThrowAsJavaScriptException();
    return;
  }
  this->rawData = this->instance.get();
}

QCameraFormat* QCameraFormatWrap::getInternalInstance() {
  return this->instance.get();
}

Napi::Value QCameraFormatWrap::isNull(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->instance->isNull());
}

Napi::Value QCameraFormatWrap::maxFrameRate(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->instance->maxFrameRate());
}

Napi::Value QCameraFormatWrap::minFrameRate(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->instance->minFrameRate());
}

Napi::Value QCameraFormatWrap::pixelFormat(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->instance->pixelFormat());
}

Napi::Value QCameraFormatWrap::resolution(const Napi::CallbackInfo& info) {
  return QSizeWrap::constructor.New({Napi::External<QSize>::New(
      info.Env(), new QSize(this->instance->resolution()))});
}

Napi::Value QCameraFormatWrap::equals(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() != 1 || !info[0].IsObject()) {
    Napi::TypeError::New(
        env, "Wrong number/type of arguments, refer to QCameraFormat.equals()")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::Object formatObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
  QCameraFormatWrap* formatWrap =
      Napi::ObjectWrap<QCameraFormatWrap>::Unwrap(formatObj);
  QCameraFormat* format = formatWrap->getInternalInstance();
  return Napi::Boolean::New(env, (this->instance.get() == format));
}
