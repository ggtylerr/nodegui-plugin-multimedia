#include "qaudioformat_wrap.h"

#include <QAudioFormat>

Napi::FunctionReference QAudioFormatWrap::constructor;

Napi::Object QAudioFormatWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QAudioFormat", {
        InstanceMethod("bytesForDuration", &QAudioFormatWrap::bytesForDuration),
        InstanceMethod("bytesForFrames", &QAudioFormatWrap::bytesForFrames),
        InstanceMethod("bytesPerFrame", &QAudioFormatWrap::bytesPerFrame),
        InstanceMethod("bytesPerSample", &QAudioFormatWrap::bytesPerSample),
        InstanceMethod("channelConfig", &QAudioFormatWrap::channelConfig),
        InstanceMethod("channelCount", &QAudioFormatWrap::channelCount),
        InstanceMethod("channelOffset", &QAudioFormatWrap::channelOffset),
        InstanceMethod("durationForBytes", &QAudioFormatWrap::durationForBytes),
        InstanceMethod("durationForFrames", &QAudioFormatWrap::durationForFrames),
        InstanceMethod("framesForBytes", &QAudioFormatWrap::framesForBytes),
        InstanceMethod("framesForDuration", &QAudioFormatWrap::framesForDuration),
        InstanceMethod("isValid", &QAudioFormatWrap::isValid),
        InstanceMethod("normalizedSampleValue", &QAudioFormatWrap::normalizedSampleValue),
        InstanceMethod("sampleFormat", &QAudioFormatWrap::sampleFormat),
        InstanceMethod("sampleRate", &QAudioFormatWrap::sampleRate),
        InstanceMethod("setChannelConfig", &QAudioFormatWrap::setChannelConfig),
        InstanceMethod("setChannelCount", &QAudioFormatWrap::setChannelCount),
        InstanceMethod("setSampleFormat", &QAudioFormatWrap::setSampleFormat),
        InstanceMethod("setSampleRate", &QAudioFormatWrap::setSampleRate),

        InstanceMethod("equals", &QAudioFormatWrap::equals),

        StaticMethod("defaultChannelConfigForChannelCount", &StaticQAudioFormatWrapMethods::defaultChannelConfigForChannelCount),

        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QAudioFormatWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QAudioFormat", func);
    return exports;
}

QAudioFormatWrap::QAudioFormatWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QAudioFormatWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = std::make_unique<QAudioFormat>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        QAudioFormat* format = info[0].As<Napi::External<QAudioFormat>>().Data();
        this->instance = std::make_unique<QAudioFormat>(*format);
    } else {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QAudioFormat()").ThrowAsJavaScriptException();
        this->instance.reset();
    }
}

QAudioFormatWrap::~QAudioFormatWrap() {
    this->instance.reset();
}

QAudioFormat* QAudioFormatWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QAudioFormatWrap::bytesForDuration(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.bytesForDuration()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    qint64 result = this->instance->bytesForDuration(info[0].As<Napi::Number>().Int64Value());
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QAudioFormatWrap::bytesForFrames(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.bytesForFrames()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    qint32 result = this->instance->bytesForFrames(info[0].As<Napi::Number>().Int32Value());
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QAudioFormatWrap::bytesPerFrame(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->bytesPerFrame());
}

Napi::Value QAudioFormatWrap::bytesPerSample(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->bytesPerSample());
}

Napi::Value QAudioFormatWrap::channelConfig(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->channelConfig()));
}

Napi::Value QAudioFormatWrap::channelCount(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->channelCount());
}

Napi::Value QAudioFormatWrap::channelOffset(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.channelOffset()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    auto out = static_cast<QAudioFormat::AudioChannelPosition>(info[0].As<Napi::Number>().Int32Value());
    return Napi::Number::New(env, this->instance->channelOffset(out));
}

Napi::Value QAudioFormatWrap::durationForBytes(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.durationForBytes()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    qint64 result = this->instance->durationForBytes(info[0].As<Napi::Number>().Int32Value());
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QAudioFormatWrap::durationForFrames(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.durationForFrames()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    qint64 result = this->instance->durationForFrames(info[0].As<Napi::Number>().Int32Value());
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QAudioFormatWrap::framesForBytes(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.framesForBytes()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    qint32 result = this->instance->framesForBytes(info[0].As<Napi::Number>().Int32Value());
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QAudioFormatWrap::framesForDuration(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.framesForDuration()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    qint32 result = this->instance->framesForDuration(info[0].As<Napi::Number>().Int64Value());
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QAudioFormatWrap::isValid(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isValid());
}

// DISCLAIMER: I AM NOT SMART ENOUGH TO IMPLEMENT THIS PROPERLY SO HOPEFULLY THIS WORKS LOL
// TODO: look into this
Napi::Value QAudioFormatWrap::normalizedSampleValue(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.normalizedSampleValue()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    float result = this->instance->normalizedSampleValue(info[0].As<Napi::Number>());
    return Napi::Number::New(env, static_cast<float>(result));
}

Napi::Value QAudioFormatWrap::sampleFormat(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->sampleFormat()));
}

Napi::Value QAudioFormatWrap::sampleRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->sampleRate());
}

Napi::Value QAudioFormatWrap::setChannelConfig(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.setChannelConfig()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setChannelConfig(static_cast<QAudioFormat::ChannelConfig>(info[0].As<Napi::Number>().Int32Value()));
    return env.Null();
}

Napi::Value QAudioFormatWrap::setChannelCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.setChannelCount()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    this->instance->setChannelCount(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QAudioFormatWrap::setSampleFormat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.setSampleFormat()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setSampleFormat(static_cast<QAudioFormat::SampleFormat>(info[0].As<Napi::Number>().Int32Value()));
    return env.Null();
}

Napi::Value QAudioFormatWrap::setSampleRate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.setSampleRate()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    this->instance->setSampleRate(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QAudioFormatWrap::equals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.equals()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object formatObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioFormatWrap* formatWrap = Napi::ObjectWrap<QAudioFormatWrap>::Unwrap(formatObj);
    QAudioFormat* format = formatWrap->getInternalInstance();
    return Napi::Boolean::New(env, (*this->instance == *format));
}

Napi::Value StaticQAudioFormatWrapMethods::defaultChannelConfigForChannelCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioFormat.defaultChannelConfigForChannelCount()").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    auto out = static_cast<QAudioFormat::ChannelConfig>(info[0].As<Napi::Number>().Int32Value());
    return Napi::Number::New(env, QAudioFormat::defaultChannelConfigForChannelCount(out));
}
