#pragma once
#include <napi.h>

#include <QCameraFormat>

#include "QtCore/QObject/qobject_macro.h"

class QCameraFormatWrap : public Napi::ObjectWrap<QCameraFormatWrap> {
   private:
    std::unique_ptr<QCameraFormat> instance;

   public:
    static Napi::Object init(Napi::Env env, Napi::Object exports);
    QCameraFormatWrap(const Napi::CallbackInfo& info);
    QCameraFormat* getInternalInstance();
    static Napi::FunctionReference constructor;
    // Wrapped Functions
    Napi::Value isNull(const Napi::CallbackInfo& info);
    Napi::Value maxFrameRate(const Napi::CallbackInfo& info);
    Napi::Value minFrameRate(const Napi::CallbackInfo& info);
    Napi::Value pixelFormat(const Napi::CallbackInfo& info);
    Napi::Value resolution(const Napi::CallbackInfo& info);
    Napi::Value equals(const Napi::CallbackInfo& info);

    COMPONENT_WRAPPED_METHODS_DECLARATION
};
