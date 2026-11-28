#include "qcameradevice_wrap.h"

#include <QCameraDevice>

#include "./qcameraformat_wrap.h"
#include "QtCore/QSize/qsize_wrap.h"

Napi::FunctionReference QCameraDeviceWrap::constructor;

Napi::Object QCameraDeviceWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QCameraDevice", {
        InstanceMethod("correctionAngle", &QCameraDeviceWrap::correctionAngle),
        InstanceMethod("description", &QCameraDeviceWrap::description),
        InstanceMethod("id", &QCameraDeviceWrap::id),
        InstanceMethod("isDefault", &QCameraDeviceWrap::isDefault),
        InstanceMethod("isNull", &QCameraDeviceWrap::isNull),
        InstanceMethod("photoResolutions", &QCameraDeviceWrap::photoResolutions),
        InstanceMethod("position", &QCameraDeviceWrap::position),
        InstanceMethod("videoFormats", &QCameraDeviceWrap::videoFormats),
        InstanceMethod("equals", &QCameraDeviceWrap::equals),
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QCameraDeviceWrap) });
    constructor = Napi::Persistent(func);
    exports.Set("QCameraDevice", func);
    return exports;
}

QCameraDeviceWrap::QCameraDeviceWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QCameraDeviceWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = std::make_unique<QCameraDevice>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance.reset(
            info[0].As<Napi::External<QCameraDevice>>().Data());
    } else {
        Napi::TypeError::New(
            env, "Wrong number/type of arguments, refer to QCameraDevice()")
            .ThrowAsJavaScriptException();
        return;
    }
    this->rawData = this->instance.get();
}

QCameraDevice* QCameraDeviceWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QCameraDeviceWrap::correctionAngle(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(), static_cast<int>(this->instance->correctionAngle()));
}

Napi::Value QCameraDeviceWrap::description(const Napi::CallbackInfo& info) {
    return Napi::String::New(
        info.Env(), this->instance->description().toStdString());
}

Napi::Value QCameraDeviceWrap::id(const Napi::CallbackInfo& info) {
    return Napi::String::New(
        info.Env(), QString(this->instance->id()).toStdString());
}

Napi::Value QCameraDeviceWrap::isDefault(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isDefault());
}

Napi::Value QCameraDeviceWrap::isNull(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isNull());
}

Napi::Value QCameraDeviceWrap::photoResolutions(
    const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QSize> sizes = this->instance->photoResolutions();
    int l = sizes.length();
    Napi::Array out = Napi::Array::New(env, l);
    for (int i = 0; i < l; i++) {
        out[i] = QSizeWrap::constructor.New(
            { Napi::External<QSize>::New(info.Env(), new QSize(sizes[i])) });
    }
    return out;
}

Napi::Value QCameraDeviceWrap::position(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(), static_cast<int>(this->instance->position()));
}

Napi::Value QCameraDeviceWrap::videoFormats(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QCameraFormat> formats = this->instance->videoFormats();
    int l = formats.length();
    Napi::Array out = Napi::Array::New(env, l);
    for (int i = 0; i < l; i++) {
        out[i] = QCameraFormatWrap::constructor.New(
            { Napi::External<QCameraFormat>::New(
                info.Env(), new QCameraFormat(formats[i])) });
    }
    return out;
}

Napi::Value QCameraDeviceWrap::equals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env,
            "Wrong number/type of arguments, refer to QCameraDevice.equals()")
            .ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object deviceObj =
        static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QCameraDeviceWrap* deviceWrap =
        Napi::ObjectWrap<QCameraDeviceWrap>::Unwrap(deviceObj);
    QCameraDevice* device = deviceWrap->getInternalInstance();
    return Napi::Boolean::New(env, (this->instance.get() == device));
}
