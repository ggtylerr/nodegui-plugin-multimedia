#pragma once
#include <nodegui/core/NodeWidget/nodewidget.h>
#include "QtWidgets/QWidget/qwidget_macro.h"

#include <QVideoWidget>

#include "../helper.h"

class NVideoWidget : public QVideoWidget, public NodeWidget {
    Q_OBJECT
    NODEWIDGET_IMPLEMENTATIONS(QVideoWidget)
public:
    using QVideoWidget::QVideoWidget;

    void connectSignalsToEventEmitter() override {
        QWIDGET_SIGNALS
        QObject::connect(this, &QVideoWidget::aspectRatioModeChanged, [=](Qt::AspectRatioMode mode) {
            Helper::handleSimpleSignalEnum(this->emitOnNode, "aspectRatioModeChanged", mode);
        });
        QObject::connect(this, &QVideoWidget::fullScreenChanged, [=](bool fullScreen) {
            Helper::handleSimpleSignalBool(this->emitOnNode, "fullScreenChanged", fullScreen);
        });
    }
};
