#include "qaudiodevice_wrap.h"

#include "./qaudioformat_wrap.h"

#include <QAudioDevice>

Napi::FunctionReference QAudioDeviceWrap::constructor;

Napi::Object QAudioDeviceWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QAudioDevice", {
        InstanceMethod("channelConfiguration", &QAudioDeviceWrap::channelConfiguration),
        InstanceMethod("description", &QAudioDeviceWrap::description),
        InstanceMethod("id", &QAudioDeviceWrap::id),
        InstanceMethod("isDefault", &QAudioDeviceWrap::isDefault),
        InstanceMethod("isFormatSupported", &QAudioDeviceWrap::isFormatSupported),
        InstanceMethod("isNull", &QAudioDeviceWrap::isNull),
        InstanceMethod("maximumChannelCount", &QAudioDeviceWrap::maximumChannelCount),
        InstanceMethod("maximumSampleRate", &QAudioDeviceWrap::maximumSampleRate),
        InstanceMethod("minimumChannelCount", &QAudioDeviceWrap::minimumChannelCount),
        InstanceMethod("minimumSampleRate", &QAudioDeviceWrap::minimumSampleRate),
        InstanceMethod("mode", &QAudioDeviceWrap::mode),
        InstanceMethod("preferredFormat", &QAudioDeviceWrap::preferredFormat),
        InstanceMethod("supportedSampleFormats", &QAudioDeviceWrap::supportedSampleFormats),
        InstanceMethod("swap", &QAudioDeviceWrap::swap),

        InstanceMethod("equals", &QAudioDeviceWrap::equals),
        
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QAudioDeviceWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QAudioDevice", func);
    return exports;
}

QAudioDeviceWrap::QAudioDeviceWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QAudioDeviceWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = std::make_unique<QAudioDevice>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        QAudioDevice* device = info[0].As<Napi::External<QAudioDevice>>().Data();
        this->instance = std::make_unique<QAudioDevice>(*device);
    } else {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QAudioDevice()").ThrowAsJavaScriptException();
        this->instance = nullptr;
    }
}

QAudioDeviceWrap::~QAudioDeviceWrap() {
    this->instance.reset();
}

QAudioDevice* QAudioDeviceWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QAudioDeviceWrap::channelConfiguration(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->channelConfiguration()));
}

Napi::Value QAudioDeviceWrap::description(const Napi::CallbackInfo& info) {
    return Napi::Value::From(info.Env(), (this->instance->description()).toStdString());
}

Napi::Value QAudioDeviceWrap::id(const Napi::CallbackInfo& info) {
    return Napi::Value::From(info.Env(), (this->instance->id()).toStdString());
}

Napi::Value QAudioDeviceWrap::isDefault(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isDefault());
}

Napi::Value QAudioDeviceWrap::isFormatSupported(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioDevice.setAudioBufferOutput()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object outputObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioFormatWrap* outputWrap = Napi::ObjectWrap<QAudioFormatWrap>::Unwrap(outputObj);
    QAudioFormat* output = outputWrap->getInternalInstance();
    return Napi::Boolean::New(info.Env(), this->instance->isFormatSupported(*output));
}

Napi::Value QAudioDeviceWrap::isNull(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isNull());
}

Napi::Value QAudioDeviceWrap::maximumChannelCount(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->maximumChannelCount());
}

Napi::Value QAudioDeviceWrap::maximumSampleRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->maximumSampleRate());
}

Napi::Value QAudioDeviceWrap::minimumChannelCount(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->minimumChannelCount());
}

Napi::Value QAudioDeviceWrap::minimumSampleRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->minimumSampleRate());
}

Napi::Value QAudioDeviceWrap::mode(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->mode()));
}

Napi::Value QAudioDeviceWrap::preferredFormat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return QAudioFormatWrap::constructor.New({
        Napi::External<QAudioFormat>::New(
            env, 
            new QAudioFormat(this->instance->preferredFormat())
        )
    });
}

Napi::Value QAudioDeviceWrap::supportedSampleFormats(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QAudioFormat::SampleFormat> formats = this->instance->supportedSampleFormats();
    int length = formats.length();
    Napi::Array retval = Napi::Array::New(env, length);
    for (int i = 0; i < length; i++) {
        QAudioFormat::SampleFormat format = formats[i];
        auto instance = Napi::Number::New(env,static_cast<int>(format));
        retval[i] = instance;
    }
    return retval;
}

Napi::Value QAudioDeviceWrap::swap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioDevice.swap()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object deviceObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioDeviceWrap* deviceWrap = Napi::ObjectWrap<QAudioDeviceWrap>::Unwrap(deviceObj);
    QAudioDevice* device = deviceWrap->getInternalInstance();
    this->instance->swap(*device);
    return env.Null();
}

// Wrapper around operator==()
Napi::Value QAudioDeviceWrap::equals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioDevice.equals()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object deviceObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioDeviceWrap* deviceWrap = Napi::ObjectWrap<QAudioDeviceWrap>::Unwrap(deviceObj);
    QAudioDevice* device = deviceWrap->getInternalInstance();
    return Napi::Boolean::New(env, (this->instance.get() == device));
}
