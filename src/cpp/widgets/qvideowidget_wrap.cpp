#include "qvideowidget_wrap.h"
#include "../helper.h"

#include "../video/qvideosink_wrap.h"

#include <QWidget>
#include <QVideoWidget>

#include <Extras/Utils/nutils.h>
#include <QtCore/QSize/qsize_wrap.h>

Napi::FunctionReference QVideoWidgetWrap::constructor;

Napi::Object QVideoWidgetWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QVideoWidget", {
        // Methods
        InstanceMethod("aspectRatioMode", &QVideoWidgetWrap::aspectRatioMode),
        InstanceMethod("isFullScreen", &QVideoWidgetWrap::isFullScreen),
        InstanceMethod("videoSink", &QVideoWidgetWrap::videoSink),
        InstanceMethod("sizeHint", &QVideoWidgetWrap::sizeHint),
        // Slots
        InstanceMethod("setAspectRatioMode", &QVideoWidgetWrap::setAspectRatioMode),
        InstanceMethod("setFullScreen", &QVideoWidgetWrap::setFullScreen),
        QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(QVideoWidgetWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QVideoWidget", func);
    QOBJECT_REGISTER_WRAPPER(QVideoWidget, QVideoWidgetWrap);
    return exports;
}

QVideoWidgetWrap::QVideoWidgetWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QVideoWidgetWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = new NVideoWidget();
    } else if (info.Length() == 1) {
        this->instance = new NVideoWidget(Helper::getQWidgetFromValue(info[0]));
        if (env.IsExceptionPending()) return;
    } else {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QVideoWidget()").ThrowAsJavaScriptException();
        return;
    }
    this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QVideoWidgetWrap::~QVideoWidgetWrap() {
    extrautils::safeDelete(this->instance);
}

NVideoWidget* QVideoWidgetWrap::getInternalInstance() {
    return this->instance;
}

Napi::Value QVideoWidgetWrap::aspectRatioMode(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(),
        static_cast<int>(this->instance->aspectRatioMode())
    );
}

Napi::Value QVideoWidgetWrap::isFullScreen(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isFullScreen());
}

Napi::Value QVideoWidgetWrap::videoSink(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QVideoSink* result = this->instance->videoSink();
    if (result) {
        return QVideoSinkWrap::constructor.New({
            Napi::External<QVideoSink>::New(env, result)
        });
    } else {
        return env.Null();
    }
}

Napi::Value QVideoWidgetWrap::sizeHint(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QSize result = this->instance->sizeHint();
    return QSizeWrap::constructor.New({
        Napi::External<QSize>::New(env, new QSize(result.width(), result.height()))
    });
}

Napi::Value QVideoWidgetWrap::setAspectRatioMode(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoWidget.setAspectRatioMode()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setAspectRatioMode(
        static_cast<Qt::AspectRatioMode>(
            info[0].As<Napi::Number>().Int32Value()
        )
    );
    return env.Null();
}

Napi::Value QVideoWidgetWrap::setFullScreen(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoWidget.setFullScreen()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setFullScreen(info[0].As<Napi::Boolean>());
    return env.Null();
}
