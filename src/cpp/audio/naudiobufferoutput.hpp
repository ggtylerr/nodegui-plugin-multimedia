#pragma once

#include <nodegui/core/Events/eventwidget.h>
#include <nodegui/core/Events/eventwidget_macro.h>

#include <QAudioBufferOutput>
#include "./qaudiobuffer_wrap.h"
#include "../helper.h"

class NAudioBufferOutput : public QAudioBufferOutput, public EventWidget {
    Q_OBJECT
    EVENTWIDGET_IMPLEMENTATIONS(QAudioBufferOutput)
    public:
        using QAudioBufferOutput::QAudioBufferOutput;

        void connectSignalsToEventEmitter() override {
            QOBJECT_SIGNALS

            QObject::connect(this, &QAudioBufferOutput::audioBufferReceived, [=](const QAudioBuffer &buffer) {
                Napi::Env env = this->emitOnNode.Env();
                Napi::HandleScope scope(env);
                auto instance = QAudioBufferWrap::constructor.New({
                    Napi::External<QAudioBuffer>::New(env, new QAudioBuffer(buffer))
                });
                this->emitOnNode.Call({ Napi::String::New(env, "audioBufferReceived"), instance });
            });
        }
};