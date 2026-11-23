#include "qabstractvideobuffer_wrap.h"
#include "qvideoframeformat_wrap.h"

#include <QAbstractVideoBuffer>

Napi::FunctionReference QAbstractVideoBufferWrap::constructor;

Napi::Object QAbstractVideoBufferWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QAbstractVideoBuffer", {
        InstanceMethod("format", &QAbstractVideoBufferWrap::format),
        InstanceMethod("map", &QAbstractVideoBufferWrap::map),
        InstanceMethod("unmap", &QAbstractVideoBufferWrap::unmap),
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QAbstractVideoBufferWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QAbstractVideoBuffer", func);
    return exports;
}

QAbstractVideoBufferWrap::QAbstractVideoBufferWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QAbstractVideoBufferWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance.reset(info[0].As<Napi::External<QAbstractVideoBuffer>>().Data());
        if (!this->instance) {
            Napi::TypeError::New(env, "Cannot wrap a null QAbstractVideoBuffer").ThrowAsJavaScriptException();
            return;
        }
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAbstractVideoBuffer()").ThrowAsJavaScriptException();
        return;
    }
}

QAbstractVideoBufferWrap::~QAbstractVideoBufferWrap() {
    this->instance.reset();
}

QAbstractVideoBuffer* QAbstractVideoBufferWrap::getInternalInstance() {
    return this->instance.get();
}

std::unique_ptr<QAbstractVideoBuffer> QAbstractVideoBufferWrap::takeInstance() {
    return std::move(this->instance);
}

Napi::Value QAbstractVideoBufferWrap::format(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (!this->instance) {
        Napi::Error::New(env, "QAbstractVideoBuffer is null").ThrowAsJavaScriptException();
        return env.Null();
    }
    return QVideoFrameFormatWrap::constructor.New({
        Napi::External<QVideoFrameFormat>::New(
            env, new QVideoFrameFormat(this->instance->format())
        )
    });
}

Napi::Value QAbstractVideoBufferWrap::map(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAbstractVideoBuffer.map()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return QAbstractVideoBufferWrap::mapDataToN(env, 
        this->instance->map(
            static_cast<QVideoFrame::MapMode>(
                info[0].As<Napi::Number>().Int32Value()
            )
        )
    );
}

Napi::Value QAbstractVideoBufferWrap::unmap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (!this->instance) {
        Napi::Error::New(env, "QAbstractVideoBuffer is null").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->unmap();
    return env.Null();
}

Napi::Object QAbstractVideoBufferWrap::mapDataToN(const Napi::Env& env, const QAbstractVideoBuffer::MapData& mapdata) {
    Napi::Object out = Napi::Object::New(env);
    Napi::Array bytesPerLine = Napi::Array::New(env, 4);
    Napi::Array dataSize = Napi::Array::New(env, 4);
    Napi::Array data = Napi::Array::New(env, 4);
    for (int i = 0; i < 4; i++) {
        bytesPerLine[i] = Napi::Number::New(env, mapdata.bytesPerLine[i]);
        dataSize[i] = Napi::Number::New(env, static_cast<double>(mapdata.dataSize[i]));
        if (mapdata.data[i] != nullptr && mapdata.dataSize[i] > 0) {
            data[i] = Napi::Buffer<uchar>::New(
                env, mapdata.data[i], static_cast<size_t>(mapdata.dataSize[i])
            );
        } else {
            data[i] = env.Null();
        }
    }
    out.Set("bytesPerLine", bytesPerLine);
    out.Set("dataSize", dataSize);
    out.Set("data", data);
    out.Set("planeCount", Napi::Number::New(env, mapdata.planeCount));
    return out;
}

QAbstractVideoBuffer::MapData QAbstractVideoBufferWrap::NToMapData(const Napi::Value& value) {
    Napi::Object in = value.As<Napi::Object>();
    QAbstractVideoBuffer::MapData out;

    Napi::Array bytesPerLine = in.Get("bytesPerLine").As<Napi::Array>();
    Napi::Array data = in.Get("data").As<Napi::Array>();
    Napi::Array dataSize = in.Get("dataSize").As<Napi::Array>();

    for (int i = 0; i < 4; i++) {
        out.bytesPerLine[i] = bytesPerLine.Get(i).As<Napi::Number>().Int32Value();
    }
    for (int i = 0; i < 4; i++) {
        out.data[i] = data.Get(i).As<Napi::Buffer<uchar>>().Data();
    }
    for (int i = 0; i < 4; i++) {
        out.dataSize[i] = dataSize.Get(i).As<Napi::Number>().Int32Value();
    }
    out.planeCount = std::clamp(in.Get("planeCount").As<Napi::Number>().Int32Value(), 0, 4);

    return out;
}