#include "qaudiobuffer_wrap.h"
#include "qaudioformat_wrap.h"

#include <cstdint>
#include <QAudioBuffer>

Napi::FunctionReference QAudioBufferWrap::constructor;

Napi::Object QAudioBufferWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QAudioBuffer", {
        // InstanceMethod("byteCount", &QAudioBufferWrap::byteCount),
        InstanceMethod("constData", &QAudioBufferWrap::constData),
        InstanceMethod("data", &QAudioBufferWrap::data),
        InstanceMethod("detach", &QAudioBufferWrap::detach),
        InstanceMethod("duration", &QAudioBufferWrap::duration),
        InstanceMethod("format", &QAudioBufferWrap::format),
        // InstanceMethod("frameCount", &QAudioBufferWrap::frameCount),
        InstanceMethod("isValid", &QAudioBufferWrap::isValid),
        // InstanceMethod("sampleCount", &QAudioBufferWrap::sampleCount),
        InstanceMethod("startTime", &QAudioBufferWrap::startTime),
        InstanceMethod("swap", &QAudioBufferWrap::swap),
        // InstanceMethod("operator=", &QAudioBufferWrap::operator=),
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QAudioBufferWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QAudioBuffer", func);
    return exports;
}

QAudioBufferWrap::QAudioBufferWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QAudioBufferWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        // QAudioBuffer()
        this->instance = new QAudioBuffer();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        // QAudioBuffer(&other)
        this->instance = info[0].As<Napi::External<QAudioBuffer>>().Data();
    } else if (info.Length() == 1 && info[0].IsObject()) {
        // QAudioBuffer(&&other)
        this->instance = new QAudioBuffer(
            (*Napi::ObjectWrap<QAudioBufferWrap>::Unwrap(
                info[0].As<Napi::Object>()
            )->getInternalInstance())
        );
    } else if ((info.Length() == 2 || info.Length() == 3) && info[0].IsBuffer() && info[1].IsObject()) {
        // QAudioBuffer(&data, &format, startTime)
        Napi::Buffer<const char> dataBuffer = info[0].As<Napi::Buffer<const char>>();
        QByteArray data = QByteArray(dataBuffer.Data(), dataBuffer.Length());
        QAudioFormatWrap* format = Napi::ObjectWrap<QAudioFormatWrap>::Unwrap(
            info[1].As<Napi::Object>()
        );
        qint64 startTime = (info.Length() == 3 && info[2].IsNumber()) 
            ? info[2].As<Napi::Number>().Int64Value() 
            : -1;
        this->instance = new QAudioBuffer(
            data, *format->getInternalInstance(), startTime
        );
    } else if ((info.Length() == 2 || info.Length() == 3) && info[0].IsNumber() && info[1].IsObject()) {
        // QAudioBuffer(numFrames, &format, startTime)
        int numFrames = info[0].As<Napi::Number>().Int32Value();
        QAudioFormatWrap* format = Napi::ObjectWrap<QAudioFormatWrap>::Unwrap(
            info[1].As<Napi::Object>()
        );
        qint64 startTime = (info.Length() == 3 && info[2].IsNumber()) 
            ? info[2].As<Napi::Number>().Int64Value() 
            : -1;
        this->instance = new QAudioBuffer(
            numFrames, *format->getInternalInstance(), startTime
        );
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QAudioBuffer()").ThrowAsJavaScriptException();
        this->instance = nullptr;
    }
}

QAudioBufferWrap::~QAudioBufferWrap() {
    delete this->instance;
}

QAudioBuffer* QAudioBufferWrap::getInternalInstance() {
    return this->instance;
}

Napi::Value QAudioBufferWrap::constData(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    qsizetype byteCount = this->instance->byteCount();

    if (!this->instance->isValid() || byteCount <= 0) {
        return Napi::Buffer<uint8_t>::New(env, 0);
    }

    const uint8_t* data = this->instance->constData<uint8_t>();
    return Napi::Buffer<uint8_t>::Copy(env, data, static_cast<size_t>(byteCount));
}

Napi::Value QAudioBufferWrap::data(const Napi::CallbackInfo& info) {
    return this->constData(info);
}

Napi::Value QAudioBufferWrap::detach(const Napi::CallbackInfo& info) {
    this->instance->detach();
    return info.Env().Undefined();
}

Napi::Value QAudioBufferWrap::duration(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->duration());
}

Napi::Value QAudioBufferWrap::format(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QAudioFormat result = this->instance->format();
    return QAudioFormatWrap::constructor.New({
        Napi::External<QAudioFormat>::New(env, new QAudioFormat(result))
    });
}

Napi::Value QAudioBufferWrap::isValid(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isValid());
}


Napi::Value QAudioBufferWrap::startTime(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->startTime());
}

Napi::Value QAudioBufferWrap::swap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QAudioBuffer.swap()").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    QAudioBufferWrap* otherWrap = Napi::ObjectWrap<QAudioBufferWrap>::Unwrap(info[0].As<Napi::Object>());
    this->instance->swap(*otherWrap->getInternalInstance());
    return env.Undefined();
}
