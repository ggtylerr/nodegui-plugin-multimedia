#include "qvideoframe_wrap.h"

#include "qabstractvideobuffer_wrap.h"
#include "qvideoframeformat_wrap.h"

#include "QtCore/QRectF/qrectf_wrap.h"
#include "QtCore/QSize/qsize_wrap.h"
#include "QtGui/QColor/qcolor_wrap.h"
#include "QtGui/QImage/qimage_wrap.h"

#include <QVideoFrame>

Napi::FunctionReference QVideoFrameWrap::constructor;

Napi::Object QVideoFrameWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QVideoFrame", {
        InstanceMethod("bits", &QVideoFrameWrap::bits),
        InstanceMethod("bytesPerLine", &QVideoFrameWrap::bytesPerLine),
        InstanceMethod("endTime", &QVideoFrameWrap::endTime),
        InstanceMethod("handleType", &QVideoFrameWrap::handleType),
        InstanceMethod("height", &QVideoFrameWrap::height),
        InstanceMethod("isMapped", &QVideoFrameWrap::isMapped),
        InstanceMethod("isReadable", &QVideoFrameWrap::isReadable),
        InstanceMethod("isValid", &QVideoFrameWrap::isValid),
        InstanceMethod("isWritable", &QVideoFrameWrap::isWritable),
        InstanceMethod("map", &QVideoFrameWrap::map),
        InstanceMethod("mapMode", &QVideoFrameWrap::mapMode),
        InstanceMethod("mappedBytes", &QVideoFrameWrap::mappedBytes),
        InstanceMethod("mirrored", &QVideoFrameWrap::mirrored),
        InstanceMethod("paint", &QVideoFrameWrap::paint),
        InstanceMethod("pixelFormat", &QVideoFrameWrap::pixelFormat),
        InstanceMethod("planeCount", &QVideoFrameWrap::planeCount),
        InstanceMethod("rotation", &QVideoFrameWrap::rotation),
        InstanceMethod("setEndTime", &QVideoFrameWrap::setEndTime),
        InstanceMethod("setMirrored", &QVideoFrameWrap::setMirrored),
        InstanceMethod("setRotation", &QVideoFrameWrap::setRotation),
        InstanceMethod("setStartTime", &QVideoFrameWrap::setStartTime),
        InstanceMethod("setStreamFrameRate", &QVideoFrameWrap::setStreamFrameRate),
        InstanceMethod("setSubtitleText", &QVideoFrameWrap::setSubtitleText),
        InstanceMethod("size", &QVideoFrameWrap::size),
        InstanceMethod("startTime", &QVideoFrameWrap::startTime),
        InstanceMethod("streamFrameRate", &QVideoFrameWrap::streamFrameRate),
        InstanceMethod("subtitleText", &QVideoFrameWrap::subtitleText),
        InstanceMethod("surfaceFormat", &QVideoFrameWrap::surfaceFormat),
        InstanceMethod("swap", &QVideoFrameWrap::swap),
        InstanceMethod("toImage", &QVideoFrameWrap::toImage),
        InstanceMethod("unmap", &QVideoFrameWrap::unmap),
        InstanceMethod("width", &QVideoFrameWrap::width),

        InstanceMethod("equals", &QVideoFrameWrap::equals),

        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QVideoFrameWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QVideoFrame", func);
    return exports;
}

QVideoFrameWrap::QVideoFrameWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QVideoFrameWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        // QVideoFrame()
        this->instance = std::make_unique<QVideoFrame>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        // QVideoFrame(&frame)
        QVideoFrame* frame = info[0].As<Napi::External<QVideoFrame>>().Data();
        this->instance = std::make_unique<QVideoFrame>(*frame);
    } else if (info.Length() == 1 && info[0].IsObject()) {
        Napi::Object obj = info[0].As<Napi::Object>();
        if (obj.InstanceOf(QImageWrap::constructor.Value())) {
            // QVideoFrame(&image)
            QImageWrap* image = Napi::ObjectWrap<QImageWrap>::Unwrap(obj);
            this->instance = std::make_unique<QVideoFrame>(*image->getInternalInstance());
        } else if (obj.InstanceOf(QVideoFrameFormatWrap::constructor.Value())) {
            // QVideoFrame(&format)
            QVideoFrameFormatWrap* format = Napi::ObjectWrap<QVideoFrameFormatWrap>::Unwrap(obj);
            this->instance = std::make_unique<QVideoFrame>(*format->getInternalInstance());
        } else if (obj.InstanceOf(QAbstractVideoBufferWrap::constructor.Value())) {
            // QVideoFrame(*buffer)
            QAbstractVideoBufferWrap* buffer = Napi::ObjectWrap<QAbstractVideoBufferWrap>::Unwrap(obj);
            this->instance = std::make_unique<QVideoFrame>(buffer->takeInstance());
        } else if (obj.InstanceOf(QVideoFrameWrap::constructor.Value())) {
            // QVideoFrame(&&other)
            QVideoFrameWrap* other = Napi::ObjectWrap<QVideoFrameWrap>::Unwrap(obj);
            this->instance = std::make_unique<QVideoFrame>(*other->getInternalInstance());
        } else {
            Napi::TypeError::New(env, "Wrong type of arguments, refer to QVideoFrame()").ThrowAsJavaScriptException();
            this->instance.reset();
        }
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame()").ThrowAsJavaScriptException();
        this->instance.reset();
    }
}

QVideoFrameWrap::~QVideoFrameWrap() {
    this->instance.reset();
}

QVideoFrame* QVideoFrameWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QVideoFrameWrap::bits(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.bits()").ThrowAsJavaScriptException();
        return env.Null();
    }
    // "This value is only valid while the frame data is mapped."
    // so we're gonna idiot proof and check if it's mapped first
    if (!this->instance->isMapped()) {
        Napi::TypeError::New(env, "Frame data is not mapped yet, cannot get bits.").ThrowAsJavaScriptException();
        return env.Null();
    }
    int plane = info[0].As<Napi::Number>().Int32Value();
    uchar* data = this->instance->bits(plane);
    int size = this->instance->mappedBytes(plane);
    return Napi::Buffer<uchar>::New(env, data, size);
}

Napi::Value QVideoFrameWrap::bytesPerLine(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.bits()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Number::New(env, this->instance->bytesPerLine(
        info[0].As<Napi::Number>().Int32Value()
    ));
}

Napi::Value QVideoFrameWrap::endTime(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->endTime());
}

Napi::Value QVideoFrameWrap::handleType(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->handleType()));
}

Napi::Value QVideoFrameWrap::height(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->height());
}

Napi::Value QVideoFrameWrap::isMapped(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isMapped());
}

Napi::Value QVideoFrameWrap::isReadable(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isReadable());
}

Napi::Value QVideoFrameWrap::isValid(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isValid());
}

Napi::Value QVideoFrameWrap::isWritable(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isWritable());
}

Napi::Value QVideoFrameWrap::map(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.map()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Boolean::New(env, this->instance->map(
        static_cast<QVideoFrame::MapMode>(
            info[0].As<Napi::Number>().Int32Value()
        )
    ));
}

Napi::Value QVideoFrameWrap::mapMode(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->mapMode()));
}

Napi::Value QVideoFrameWrap::mappedBytes(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.mappedBytes()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Boolean::New(env, this->instance->mappedBytes(
        info[0].As<Napi::Number>().Int32Value()
    ));
}

Napi::Value QVideoFrameWrap::mirrored(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->mirrored());
}

Napi::Value QVideoFrameWrap::paint(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 3 || !info[0].IsExternal() || !info[1].IsObject() || !info[2].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.paint()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QPainter* painter = info[0].As<Napi::External<QPainter>>().Data();
    QRectFWrap* rectWrap = Napi::ObjectWrap<QRectFWrap>::Unwrap(info[1].As<Napi::Object>());
    QRectF rect = *rectWrap->getInternalInstance();
    // shoutouts to Qt for not having proper documentation and requiring me to
    // get the whole PaintOptions struct from their source code
    // https://code.qt.io/cgit/qt/qtmultimedia.git/tree/src/multimedia/video/qvideoframe.h?h=6.12#n125
    // THANKS QT!!!!!!!!!!
    QVideoFrame::PaintOptions options;
    Napi::Object optionsObj = info[2].As<Napi::Object>();
    if (optionsObj.Has("backgroundColor")) {
        Napi::Value color = optionsObj.Get("backgroundColor");
        if (color.IsObject()) {
            QColorWrap* colorWrap = Napi::ObjectWrap<QColorWrap>::Unwrap(color.As<Napi::Object>());
            options.backgroundColor = *colorWrap->getInternalInstance();
        } else {
            Napi::TypeError::New(env, "backgroundColor in PaintOptions must be a QColor").ThrowAsJavaScriptException();
        }
    }
    if (optionsObj.Has("aspectRatioMode")) {
        Napi::Value mode = optionsObj.Get("aspectRatioMode");
        if (mode.IsNumber()) {
            options.aspectRatioMode = static_cast<Qt::AspectRatioMode>(
                mode.As<Napi::Number>().Int32Value()
            );
        } else {
            Napi::TypeError::New(env, "aspectRatioMode in PaintOptions must be a Qt.AspectRatioMode (enum)").ThrowAsJavaScriptException();
        }
    }
    if (optionsObj.Has("paintFlags")) {
        Napi::Value mode = optionsObj.Get("paintFlags");
        if (mode.IsNumber()) {
            options.paintFlags = static_cast<QVideoFrame::PaintOptions::PaintFlags>(
                mode.As<Napi::Number>().Int32Value()
            );
        } else {
            Napi::TypeError::New(env, "paintFlags in PaintOptions must be a PaintFlags (enum)").ThrowAsJavaScriptException();
        }
    }
    this->instance->paint(painter, rect, options);
    return env.Null();
}

Napi::Value QVideoFrameWrap::pixelFormat(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->pixelFormat()));
}

Napi::Value QVideoFrameWrap::planeCount(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->planeCount());
}

Napi::Value QVideoFrameWrap::rotation(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), static_cast<int>(this->instance->rotation()));
}

Napi::Value QVideoFrameWrap::setEndTime(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.setEndTime()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setEndTime(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QVideoFrameWrap::setMirrored(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.setMirrored()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setMirrored(info[0].As<Napi::Boolean>());
    return env.Null();
}

Napi::Value QVideoFrameWrap::setRotation(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.setRotation()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setRotation(
        static_cast<QtVideo::Rotation>(
            (info[0].As<Napi::Number>().Int32Value())
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameWrap::setStartTime(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.setStartTime()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setStartTime(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QVideoFrameWrap::setStreamFrameRate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.setStreamFrameRate()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setStreamFrameRate(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QVideoFrameWrap::setSubtitleText(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.setSubtitleText()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setSubtitleText(
        QString::fromStdString(
            info[0].As<Napi::String>().Utf8Value()
        )
    );
    return env.Null();
}

Napi::Value QVideoFrameWrap::size(const Napi::CallbackInfo& info) {
    return QSizeWrap::constructor.New({
        Napi::External<QSize>::New(
            info.Env(), new QSize(this->instance->size())
        )
    });
}

Napi::Value QVideoFrameWrap::startTime(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->startTime());
}

Napi::Value QVideoFrameWrap::streamFrameRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->streamFrameRate());
}

Napi::Value QVideoFrameWrap::subtitleText(const Napi::CallbackInfo& info) {
    return Napi::String::New(info.Env(), this->instance->subtitleText().toStdString());
}

Napi::Value QVideoFrameWrap::surfaceFormat(const Napi::CallbackInfo& info) {
    return QVideoFrameFormatWrap::constructor.New({
        Napi::External<QVideoFrameFormat>::New(
            info.Env(), new QVideoFrameFormat(this->instance->surfaceFormat())
        )
    });
}

Napi::Value QVideoFrameWrap::swap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.swap()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object frameObj = info[0].As<Napi::Object>();
    QVideoFrameWrap* frameWrap = Napi::ObjectWrap<QVideoFrameWrap>::Unwrap(frameObj);
    QVideoFrame* frame = frameWrap->getInternalInstance();
    this->instance->swap(*frame);
    return env.Null();
}

Napi::Value QVideoFrameWrap::toImage(const Napi::CallbackInfo& info) {
    return QImageWrap::constructor.New({
        Napi::External<QImage>::New(
            info.Env(), new QImage(this->instance->toImage())
        )
    });
}

Napi::Value QVideoFrameWrap::unmap(const Napi::CallbackInfo& info) {
    this->instance->unmap();
    return info.Env().Null();
}

Napi::Value QVideoFrameWrap::width(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->width());
}

Napi::Value QVideoFrameWrap::equals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QVideoFrame.equals()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object frameObj = info[0].As<Napi::Object>();
    QVideoFrameWrap* frameWrap = Napi::ObjectWrap<QVideoFrameWrap>::Unwrap(frameObj);
    QVideoFrame* frame = frameWrap->getInternalInstance();
    return Napi::Boolean::New(env, (*this->instance == *frame));
}
