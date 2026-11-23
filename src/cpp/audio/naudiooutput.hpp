#pragma once

#include <nodegui/core/Events/eventwidget.h>
#include <nodegui/core/Events/eventwidget_macro.h>

#include <QAudioOutput>

#include "../helper.h"

class NAudioOutput : public QAudioOutput, public EventWidget {
    Q_OBJECT
    EVENTWIDGET_IMPLEMENTATIONS(QAudioOutput)
    public:
        using QAudioOutput::QAudioOutput;

        void connectSignalsToEventEmitter() override {
            QOBJECT_SIGNALS

            QObject::connect(this, &QAudioOutput::deviceChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "deviceChanged");
            });
            QObject::connect(this, &QAudioOutput::mutedChanged, [=](bool muted) {
                Helper::handleSimpleSignalBool(this->emitOnNode, "volumeChanged", muted);
            });
            QObject::connect(this, &QAudioOutput::volumeChanged, [=](float volume) {
                Helper::handleSimpleSignalNumber(this->emitOnNode, "volumeChanged", volume);
            });
        }
};