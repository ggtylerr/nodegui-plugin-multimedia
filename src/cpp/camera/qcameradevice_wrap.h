#pragma once
#include <napi.h>

#include <QCameraDevice>

#include "QtCore/QObject/qobject_macro.h"

class QCameraDeviceWrap : public Napi::ObjectWrap<QCameraDeviceWrap> {
   private:
    std::unique_ptr<QCameraDevice> instance;

   public:
    static Napi::Object init(Napi::Env env, Napi::Object exports);
    QCameraDeviceWrap(const Napi::CallbackInfo& info);
    QCameraDevice* getInternalInstance();
    static Napi::FunctionReference constructor;
    // Wrapped Functions
    Napi::Value correctionAngle(const Napi::CallbackInfo& info);
    Napi::Value description(const Napi::CallbackInfo& info);
    Napi::Value id(const Napi::CallbackInfo& info);
    Napi::Value isDefault(const Napi::CallbackInfo& info);
    Napi::Value isNull(const Napi::CallbackInfo& info);
    Napi::Value photoResolutions(const Napi::CallbackInfo& info);
    Napi::Value position(const Napi::CallbackInfo& info);
    Napi::Value videoFormats(const Napi::CallbackInfo& info);
    Napi::Value equals(const Napi::CallbackInfo& info);

    COMPONENT_WRAPPED_METHODS_DECLARATION
};
