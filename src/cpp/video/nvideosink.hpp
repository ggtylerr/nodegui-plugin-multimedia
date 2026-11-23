#pragma once

#include <nodegui/core/Events/eventwidget.h>
#include <nodegui/core/Events/eventwidget_macro.h>

#include <QVideoSink>
#include <QVideoFrame>

#include "qvideoframe_wrap.h"
#include "../helper.h"

class NVideoSink : public QVideoSink, public EventWidget {
    Q_OBJECT
    EVENTWIDGET_IMPLEMENTATIONS(QVideoSink)
    public:
        using QVideoSink::QVideoSink;

        void connectSignalsToEventEmitter() override {
            QOBJECT_SIGNALS

            QObject::connect(this, &QVideoSink::subtitleTextChanged, [=](const QString &subtitleText) {
                Helper::handleSimpleSignalString(this->emitOnNode, "subtitleTextChanged", subtitleText);
            });

            QObject::connect(this, &QVideoSink::videoFrameChanged, [=](const QVideoFrame &frame) {
                const Napi::Env env = emitOnNode.Env();
                Napi::HandleScope scope(env);
                emitOnNode.Call({ 
                    Napi::String::New(env, "videoFrameChanged"),
                    QVideoFrameWrap::constructor.New({
                        Napi::External<QVideoFrame>::New(env, new QVideoFrame(frame))
                    })
                });
            });

            QObject::connect(this, &QVideoSink::videoSizeChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "videoSizeChanged");
            });
        }
};