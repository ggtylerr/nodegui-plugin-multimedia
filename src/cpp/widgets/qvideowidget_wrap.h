#pragma once
#include <napi.h>
#include <stdlib.h>

#include <QPointer>

#include "QtWidgets/QWidget/qwidget_macro.h"
#include "nvideowidget.hpp"

class QVideoWidgetWrap : public Napi::ObjectWrap<QVideoWidgetWrap> {
    QWIDGET_WRAPPED_METHODS_DECLARATION
private:
    QPointer<NVideoWidget> instance;
public:
    static Napi::Object init(Napi::Env env, Napi::Object exports);
    QVideoWidgetWrap(const Napi::CallbackInfo& info);
    ~QVideoWidgetWrap();
    NVideoWidget *getInternalInstance();
    static Napi::FunctionReference constructor;
    // Wrapped Functions
    Napi::Value aspectRatioMode(const Napi::CallbackInfo& info);
    Napi::Value isFullScreen(const Napi::CallbackInfo& info);
    Napi::Value videoSink(const Napi::CallbackInfo& info);
    Napi::Value sizeHint(const Napi::CallbackInfo& info);

    // Wrapped slots
    Napi::Value setAspectRatioMode(const Napi::CallbackInfo& info);
    Napi::Value setFullScreen(const Napi::CallbackInfo& info);
};
