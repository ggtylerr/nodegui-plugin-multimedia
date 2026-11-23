#include "qvideosink_wrap.h"

#include <QObject>
#include <QVideoSink>

#include "QtCore/QSize/qsize_wrap.h"

Napi::FunctionReference QVideoSinkWrap::constructor;

Napi::Object QVideoSinkWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QVideoSink", {
        InstanceMethod("setSubtitleText", &QVideoSinkWrap::setSubtitleText),
        InstanceMethod("setVideoFrame", &QVideoSinkWrap::setVideoFrame),
        InstanceMethod("subtitleText", &QVideoSinkWrap::subtitleText),
        InstanceMethod("videoFrame", &QVideoSinkWrap::videoFrame),
        InstanceMethod("videoSize", &QVideoSinkWrap::videoSize),
        QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QVideoSinkWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QVideoSink", func);
    return exports;
}

QVideoSinkWrap::QVideoSinkWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QVideoSinkWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = new NVideoSink();
    } else if (info.Length() == 1 && info[0].IsObject()) {
        this->instance = new NVideoSink(Helper::getQObjectFromValue(info[0]));
    } else {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QVideoSink()").ThrowAsJavaScriptException();
        return;
    }
    this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QVideoSinkWrap::~QVideoSinkWrap() {
    extrautils::safeDelete(this->instance);
}

NVideoSink* QVideoSinkWrap::getInternalInstance() {
    return this->instance;
}

Napi::Value QVideoSinkWrap::setSubtitleText(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoSink.setSubtitleText()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setSubtitleText(
        QString::fromStdString(info[0].As<Napi::String>().Utf8Value())
    );
    return env.Null();
}

Napi::Value QVideoSinkWrap::setVideoFrame(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoSink.setVideoFrame()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object frameObj = info[0].As<Napi::Object>();
    QVideoFrameWrap* frameWrap = Napi::ObjectWrap<QVideoFrameWrap>::Unwrap(frameObj);
    QVideoFrame* frame = frameWrap->getInternalInstance();
    this->instance->setVideoFrame(*frame);
    return env.Null();
}

Napi::Value QVideoSinkWrap::subtitleText(const Napi::CallbackInfo& info) {
    return Napi::String::New(info.Env(), this->instance->subtitleText().toStdString());
}

Napi::Value QVideoSinkWrap::videoFrame(const Napi::CallbackInfo& info) {
    return QVideoFrameWrap::constructor.New({
        Napi::External<QVideoFrame>::New(
            info.Env(), new QVideoFrame(this->instance->videoFrame())
        )
    });
}

Napi::Value QVideoSinkWrap::videoSize(const Napi::CallbackInfo& info) {
    return QSizeWrap::constructor.New({
        Napi::External<QSize>::New(
            info.Env(), new QSize(this->instance->videoSize())
        )
    });
}
