#include "qplaybackoptions_wrap.h"

#include <QPlaybackOptions>

Napi::FunctionReference QPlaybackOptionsWrap::constructor;

Napi::Object QPlaybackOptionsWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QPlaybackOptions", {
        InstanceMethod("networkTimeout", &QPlaybackOptionsWrap::networkTimeout),
        InstanceMethod("playbackIntent", &QPlaybackOptionsWrap::playbackIntent),
        // InstanceMethod("probeSize", &QPlaybackOptionsWrap::probeSize),
        InstanceMethod("resetNetworkTimeout", &QPlaybackOptionsWrap::resetNetworkTimeout),
        InstanceMethod("resetPlaybackIntent", &QPlaybackOptionsWrap::resetPlaybackIntent),
        InstanceMethod("resetProbeSize", &QPlaybackOptionsWrap::resetProbeSize),
        InstanceMethod("setNetworkTimeout", &QPlaybackOptionsWrap::setNetworkTimeout),
        InstanceMethod("setPlaybackIntent", &QPlaybackOptionsWrap::setPlaybackIntent),
        // InstanceMethod("setProbeSize", &QPlaybackOptionsWrap::setProbeSize),
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QPlaybackOptionsWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QPlaybackOptions", func);
    return exports;
}

QPlaybackOptionsWrap::QPlaybackOptionsWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QPlaybackOptionsWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = std::make_unique<QPlaybackOptions>();
    } else if (info.Length() == 1 && info[0].IsObject()) {
        Napi::Object obj = info[0].As<Napi::Object>();
        QPlaybackOptionsWrap* other = Napi::ObjectWrap<QPlaybackOptionsWrap>::Unwrap(obj);
        this->instance = std::make_unique<QPlaybackOptions>(*other->getInternalInstance());
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QPlaybackOptions()").ThrowAsJavaScriptException();
        this->instance.reset();
    }
}

QPlaybackOptions* QPlaybackOptionsWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QPlaybackOptionsWrap::networkTimeout(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<double>((*this->instance).networkTimeout().count()));
}

Napi::Value QPlaybackOptionsWrap::playbackIntent(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>((*this->instance).playbackIntent()));
}

Napi::Value QPlaybackOptionsWrap::resetNetworkTimeout(const Napi::CallbackInfo& info) {
    this->instance->resetNetworkTimeout();
    return info.Env().Null();
}

Napi::Value QPlaybackOptionsWrap::resetPlaybackIntent(const Napi::CallbackInfo& info) {
    this->instance->resetPlaybackIntent();
    return info.Env().Null();
}

Napi::Value QPlaybackOptionsWrap::resetProbeSize(const Napi::CallbackInfo& info) {
    this->instance->resetProbeSize();
    return info.Env().Null();
}

Napi::Value QPlaybackOptionsWrap::setNetworkTimeout(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QPlaybackOptions.setNetworkTimeout()").ThrowAsJavaScriptException();
        return env.Null();
    }
    double dub = info[0].As<Napi::Number>().DoubleValue();
    auto ms = std::chrono::milliseconds{static_cast<int64_t>(dub)};
    this->instance->setNetworkTimeout(ms);
    return env.Null();
}

Napi::Value QPlaybackOptionsWrap::setPlaybackIntent(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QPlaybackOptions.setPlaybackIntent()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setPlaybackIntent(
        static_cast<QPlaybackOptions::PlaybackIntent>(
            info[0].As<Napi::Number>().Int32Value()
        )
    );
    return env.Null();
}