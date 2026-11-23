#include "qaudiobufferoutput_wrap.h"
#include "../helper.h"

#include "./qaudioformat_wrap.h"

#include <QObject>
#include <QAudioBufferOutput>

Napi::FunctionReference QAudioBufferOutputWrap::constructor;

Napi::Object QAudioBufferOutputWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QAudioBufferOutput", {
        InstanceMethod("format", &QAudioBufferOutputWrap::format),
        QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QAudioBufferOutputWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QAudioBufferOutput", func);
    return exports;
}

QAudioBufferOutputWrap::QAudioBufferOutputWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QAudioBufferOutputWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = new NAudioBufferOutput();
    } else if (info.Length() == 1) {
        if (info[0].As<Napi::Object>().InstanceOf(QAudioFormatWrap::constructor.Value())) {
            QAudioFormatWrap* formatWrap = Napi::ObjectWrap<QAudioFormatWrap>::Unwrap(info[0].As<Napi::Object>());
            QAudioFormat* format = formatWrap->getInternalInstance();
            this->instance = new NAudioBufferOutput(*format);
        } else {
            this->instance = new NAudioBufferOutput(Helper::getQObjectFromValue(info[0]));
        }
    } else if (info.Length() ==  2) {
        QAudioFormatWrap* formatWrap = Napi::ObjectWrap<QAudioFormatWrap>::Unwrap(info[0].As<Napi::Object>());
        QAudioFormat* format = formatWrap->getInternalInstance();
        this->instance = new NAudioBufferOutput(*format, Helper::getQObjectFromValue(info[1]));
    } else {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QAudioBufferOutput()").ThrowAsJavaScriptException();
    }
    this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QAudioBufferOutputWrap::~QAudioBufferOutputWrap() {
    extrautils::safeDelete(this->instance);
}

NAudioBufferOutput* QAudioBufferOutputWrap::getInternalInstance() {
    return this->instance;
}

Napi::Value QAudioBufferOutputWrap::format(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QAudioFormat result = this->instance->format();
    return QAudioFormatWrap::constructor.New({
        Napi::External<QAudioFormat>::New(env, new QAudioFormat(result))
    });
}
