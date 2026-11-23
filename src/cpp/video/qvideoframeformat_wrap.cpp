#include "qvideoframeformat_wrap.h"

#include <QVideoFrameFormat>

#include "QtCore/QRect/qrect_wrap.h"
#include "QtCore/QSize/qsize_wrap.h"

Napi::FunctionReference QVideoFrameFormatWrap::constructor;

Napi::Object QVideoFrameFormatWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QVideoFrameFormat", {
        InstanceMethod("colorRange", &QVideoFrameFormatWrap::colorRange),
        InstanceMethod("colorSpace", &QVideoFrameFormatWrap::colorSpace),
        InstanceMethod("colorTransfer", &QVideoFrameFormatWrap::colorTransfer),
        InstanceMethod("frameHeight", &QVideoFrameFormatWrap::frameHeight),
        InstanceMethod("frameRate", &QVideoFrameFormatWrap::frameRate),
        InstanceMethod("frameSize", &QVideoFrameFormatWrap::frameSize),
        InstanceMethod("frameWidth", &QVideoFrameFormatWrap::frameWidth),
        InstanceMethod("isMirrored", &QVideoFrameFormatWrap::isMirrored),
        InstanceMethod("isValid", &QVideoFrameFormatWrap::isValid),
        InstanceMethod("pixelFormat", &QVideoFrameFormatWrap::pixelFormat),
        InstanceMethod("planeCount", &QVideoFrameFormatWrap::planeCount),
        InstanceMethod("rotation", &QVideoFrameFormatWrap::rotation),
        InstanceMethod("scanLineDirection", &QVideoFrameFormatWrap::scanLineDirection),
        InstanceMethod("setColorRange", &QVideoFrameFormatWrap::setColorRange),
        InstanceMethod("setColorSpace", &QVideoFrameFormatWrap::setColorSpace),
        InstanceMethod("setColorTransfer", &QVideoFrameFormatWrap::setColorTransfer),
        InstanceMethod("setFrameRate", &QVideoFrameFormatWrap::setFrameRate),
        InstanceMethod("setFrameSize", &QVideoFrameFormatWrap::setFrameSize),
        InstanceMethod("setMaxLuminance", &QVideoFrameFormatWrap::setMaxLuminance),
        InstanceMethod("setMirrored", &QVideoFrameFormatWrap::setMirrored),
        InstanceMethod("setRotation", &QVideoFrameFormatWrap::setRotation),
        InstanceMethod("setScanLineDirection", &QVideoFrameFormatWrap::setScanLineDirection),
        InstanceMethod("setStreamFrameRate", &QVideoFrameFormatWrap::setStreamFrameRate),
        InstanceMethod("setViewport", &QVideoFrameFormatWrap::setViewport),
        InstanceMethod("streamFrameRate", &QVideoFrameFormatWrap::streamFrameRate),
        InstanceMethod("swap", &QVideoFrameFormatWrap::swap),
        InstanceMethod("viewport", &QVideoFrameFormatWrap::viewport),

        InstanceMethod("equals", &QVideoFrameFormatWrap::equals),

        StaticMethod("imageFormatFromPixelFormat", &StaticQVideoFrameFormatWrapMethods::imageFormatFromPixelFormat),
        StaticMethod("pixelFormatFromImageFormat", &StaticQVideoFrameFormatWrapMethods::pixelFormatFromImageFormat),
        StaticMethod("pixelFormatToString", &StaticQVideoFrameFormatWrapMethods::pixelFormatToString),
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QVideoFrameFormatWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QVideoFrameFormat", func);
    return exports;
}

QVideoFrameFormatWrap::QVideoFrameFormatWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QVideoFrameFormatWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        // QVideoFrameFormat()
        this->instance = std::make_unique<QVideoFrameFormat>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        // QVideoFrameFormat(&other)
        QVideoFrameFormat* format = info[0].As<Napi::External<QVideoFrameFormat>>().Data();
        this->instance = std::make_unique<QVideoFrameFormat>(*format);
    } else if (info.Length() == 1 && info[0].IsObject()) {
        // QVideoFrameFormat(&&other)
        QVideoFrameFormatWrap* format = Napi::ObjectWrap<QVideoFrameFormatWrap>::Unwrap(info[0].As<Napi::Object>());
        this->instance = std::make_unique<QVideoFrameFormat>(*format->getInternalInstance());
    } else if (info.Length() == 2 && info[0].IsObject() && info[1].IsNumber()) {
        // QVideoFrameFormat(&size, pixelFormat)
        QSizeWrap* size = Napi::ObjectWrap<QSizeWrap>::Unwrap(info[0].As<Napi::Object>());
        QVideoFrameFormat::PixelFormat format = static_cast<QVideoFrameFormat::PixelFormat>(info[1].As<Napi::Number>().Int32Value());
        this->instance = std::make_unique<QVideoFrameFormat>(
            *size->getInternalInstance(),
            format
        );
    }
}

QVideoFrameFormatWrap::~QVideoFrameFormatWrap() {
    this->instance.reset();
}

QVideoFrameFormat* QVideoFrameFormatWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QVideoFrameFormatWrap::colorRange(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->colorRange()));
}

Napi::Value QVideoFrameFormatWrap::colorSpace(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->colorSpace()));
}

Napi::Value QVideoFrameFormatWrap::colorTransfer(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->colorTransfer()));
}

Napi::Value QVideoFrameFormatWrap::frameHeight(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->frameHeight());
}

Napi::Value QVideoFrameFormatWrap::frameRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->frameRate());
}

Napi::Value QVideoFrameFormatWrap::frameSize(const Napi::CallbackInfo& info) {
    return QSizeWrap::constructor.New({
        Napi::External<QSize>::New(
            info.Env(), new QSize(this->instance->frameSize())
        )
    });
}

Napi::Value QVideoFrameFormatWrap::frameWidth(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->frameWidth());
}

Napi::Value QVideoFrameFormatWrap::isMirrored(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isMirrored());
}

Napi::Value QVideoFrameFormatWrap::isValid(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isValid());
}

Napi::Value QVideoFrameFormatWrap::pixelFormat(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->pixelFormat()));
}

Napi::Value QVideoFrameFormatWrap::planeCount(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->planeCount());
}

Napi::Value QVideoFrameFormatWrap::rotation(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->rotation()));
}

Napi::Value QVideoFrameFormatWrap::scanLineDirection(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->scanLineDirection()));
}

Napi::Value QVideoFrameFormatWrap::setColorRange(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setColorRange()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setColorRange(
        static_cast<QVideoFrameFormat::ColorRange>(
            (info[0].As<Napi::Number>().Int32Value())
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setColorSpace(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setColorSpace()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setColorSpace(
        static_cast<QVideoFrameFormat::ColorSpace>(
            (info[0].As<Napi::Number>().Int32Value())
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setColorTransfer(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setColorTransfer()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setColorTransfer(
        static_cast<QVideoFrameFormat::ColorTransfer>(
            (info[0].As<Napi::Number>().Int32Value())
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setFrameRate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setFrameRate()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setFrameRate((info[0].As<Napi::Number>().Int32Value()));
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setFrameSize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && info[0].IsObject()) {
        Napi::Object sizeObj = info[0].As<Napi::Object>();
        QSizeWrap* sizeWrap = Napi::ObjectWrap<QSizeWrap>::Unwrap(sizeObj);
        QSize* size = sizeWrap->getInternalInstance();
        this->instance->setFrameSize(*size);
    } else if (info.Length() == 2 && info[0].IsNumber() && info[1].IsNumber()) {
        this->instance->setFrameSize(
            static_cast<int>(info[0].As<Napi::Number>().Int32Value()),
            static_cast<int>(info[1].As<Napi::Number>().Int32Value())
        );
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setFrameSize()").ThrowAsJavaScriptException();
    }
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setMaxLuminance(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setMaxLuminance()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setMaxLuminance((info[0].As<Napi::Number>().FloatValue()));
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setMirrored(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setMirrored()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setMirrored(info[0].As<Napi::Boolean>());
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setRotation(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setRotation()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setRotation(
        static_cast<QtVideo::Rotation>(
            (info[0].As<Napi::Number>().Int32Value())
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setScanLineDirection(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setScanLineDirection()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setScanLineDirection(
        static_cast<QVideoFrameFormat::Direction>(
            (info[0].As<Napi::Number>().Int32Value())
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setStreamFrameRate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setStreamFrameRate()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setStreamFrameRate((info[0].As<Napi::Number>().Int32Value()));
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::setViewport(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.setViewport()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object rectObj = info[0].As<Napi::Object>();
    QRectWrap* rectWrap = Napi::ObjectWrap<QRectWrap>::Unwrap(rectObj);
    QRect* rect = rectWrap->getInternalInstance();
    this->instance->setViewport(*rect);
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::streamFrameRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->streamFrameRate());
}

Napi::Value QVideoFrameFormatWrap::swap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.swap()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object formatObj = info[0].As<Napi::Object>();
    QVideoFrameFormatWrap* formatWrap = Napi::ObjectWrap<QVideoFrameFormatWrap>::Unwrap(formatObj);
    QVideoFrameFormat* format = formatWrap->getInternalInstance();
    this->instance->swap(*format);
    return env.Null();
}

Napi::Value QVideoFrameFormatWrap::viewport(const Napi::CallbackInfo& info) {
    return QRectWrap::constructor.New({
        Napi::External<QRect>::New(
            info.Env(), new QRect(this->instance->viewport())
        )
    });
}

Napi::Value QVideoFrameFormatWrap::equals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.equals()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object formatObj = info[0].As<Napi::Object>();
    QVideoFrameFormatWrap* formatWrap = Napi::ObjectWrap<QVideoFrameFormatWrap>::Unwrap(formatObj);
    QVideoFrameFormat* format = formatWrap->getInternalInstance();
    return Napi::Boolean::New(env, (*this->instance == *format));
}

Napi::Value StaticQVideoFrameFormatWrapMethods::imageFormatFromPixelFormat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.imageFormatFromPixelFormat()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QVideoFrameFormat::PixelFormat pix = static_cast<QVideoFrameFormat::PixelFormat>(
        info[0].As<Napi::Number>().Int32Value()
    );
    return Napi::Number::New(env, QVideoFrameFormat::imageFormatFromPixelFormat(pix));
}

Napi::Value StaticQVideoFrameFormatWrapMethods::pixelFormatFromImageFormat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.pixelFormatFromImageFormat()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QImage::Format img = static_cast<QImage::Format>(
        info[0].As<Napi::Number>().Int32Value()
    );
    return Napi::Number::New(env, QVideoFrameFormat::pixelFormatFromImageFormat(img));
}

Napi::Value StaticQVideoFrameFormatWrapMethods::pixelFormatToString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrameFormat.pixelFormatToString()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Value::From(env, (
        QVideoFrameFormat::pixelFormatToString(
            static_cast<QVideoFrameFormat::PixelFormat>(
                info[0].As<Napi::Number>().Int32Value()
            )
        ).toStdString()
    ));
}
