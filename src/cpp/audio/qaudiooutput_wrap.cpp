#include "qaudiooutput_wrap.h"

#include "qaudiodevice_wrap.h"

#include <QAudioOutput>

Napi::FunctionReference QAudioOutputWrap::constructor;

Napi::Object QAudioOutputWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QAudioOutput", {
        // Methods
        InstanceMethod("device", &QAudioOutputWrap::device),
        InstanceMethod("isMuted", &QAudioOutputWrap::isMuted),
        InstanceMethod("volume", &QAudioOutputWrap::volume),
        // Slots
        InstanceMethod("setDevice", &QAudioOutputWrap::setDevice),
        InstanceMethod("setMuted", &QAudioOutputWrap::setMuted),
        InstanceMethod("setVolume", &QAudioOutputWrap::setVolume),
        QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QAudioOutputWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QAudioOutput", func);
    return exports;
}

QAudioOutputWrap::QAudioOutputWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QAudioOutputWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = new NAudioOutput();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance = qobject_cast<NAudioOutput*>(info[0].As<Napi::External<QAudioOutput>>().Data());
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioOutput()").ThrowAsJavaScriptException();
        return;
    }
    this->rawData = this->instance.get();
}

NAudioOutput* QAudioOutputWrap::getInternalInstance() {
    return this->instance;
}

Napi::Value QAudioOutputWrap::device(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return QAudioDeviceWrap::constructor.New({
        Napi::External<QAudioDevice>::New(
            env, 
            new QAudioDevice(this->instance->device())
        )
    });
}

Napi::Value QAudioOutputWrap::isMuted(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isMuted());
}

Napi::Value QAudioOutputWrap::volume(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->volume()));
}

Napi::Value QAudioOutputWrap::setDevice(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioOutput.setDevice()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object deviceObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioDeviceWrap* deviceWrap = Napi::ObjectWrap<QAudioDeviceWrap>::Unwrap(deviceObj);
    QAudioDevice* device = deviceWrap->getInternalInstance();
    this->instance->setDevice(*device);
    return env.Null();
}

Napi::Value QAudioOutputWrap::setMuted(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioOutput.setMuted()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setMuted(info[0].As<Napi::Boolean>().Value());
    return env.Null();
}

Napi::Value QAudioOutputWrap::setVolume(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioOutput.setVolume()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setVolume(info[0].As<Napi::Number>().FloatValue());
    return env.Null();
}
