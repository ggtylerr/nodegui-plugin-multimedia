#pragma once

#include <nodegui/core/Events/eventwidget.h>
#include <nodegui/core/Events/eventwidget_macro.h>

#include <QMediaPlayer>

#include "../helper.h"

class NMediaPlayer : public QMediaPlayer, public EventWidget {
    Q_OBJECT
    EVENTWIDGET_IMPLEMENTATIONS(QMediaPlayer)
    public:
        using QMediaPlayer::QMediaPlayer;
        
        void connectSignalsToEventEmitter() override {
            QOBJECT_SIGNALS

            QObject::connect(this, &QMediaPlayer::activeTracksChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "activeTracksChanged");
            });
            QObject::connect(this, &QMediaPlayer::audioBufferOutputChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "audioBufferOutputChanged");
            });
            QObject::connect(this, &QMediaPlayer::audioOutputChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "audioOutputChanged");
            });
            QObject::connect(this, &QMediaPlayer::bufferProgressChanged, [=](float filled) {
                Helper::handleSimpleSignalNumber(this->emitOnNode, "bufferProgressChanged", filled);
            });
            QObject::connect(this, &QMediaPlayer::durationChanged, [=](qint64 duration) {
                Helper::handleSimpleSignalNumber(this->emitOnNode, "durationChanged", duration);
            });
            QObject::connect(this, &QMediaPlayer::errorChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "errorChanged");
            });
            QObject::connect(this, &QMediaPlayer::errorOccurred, [=](QMediaPlayer::Error error, const QString &errorString) {
                Helper::handleSimpleSignalString(this->emitOnNode, "errorOccurred", errorString);
            });
            QObject::connect(this, &QMediaPlayer::hasAudioChanged, [=](bool available) {
                Helper::handleSimpleSignalBool(this->emitOnNode, "hasAudioChanged", available);
            });
            QObject::connect(this, &QMediaPlayer::hasVideoChanged, [=](bool videoAvailable) {
                Helper::handleSimpleSignalBool(this->emitOnNode, "hasVideoChanged", videoAvailable);
            });
            QObject::connect(this, &QMediaPlayer::loopsChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "loopsChanged");
            });
            QObject::connect(this, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
                Helper::handleSimpleSignalEnum(this->emitOnNode, "mediaStatusChanged", status);
            });
            QObject::connect(this, &QMediaPlayer::metaDataChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "metaDataChanged");
            });
            QObject::connect(this, &QMediaPlayer::pitchCompensationChanged, [=](bool enabled) {
                Helper::handleSimpleSignalBool(this->emitOnNode, "pitchCompensationChanged", enabled);
            });
            QObject::connect(this, &QMediaPlayer::playbackOptionsChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "playbackOptionsChanged");
            });
            QObject::connect(this, &QMediaPlayer::playbackRateChanged, [=](qreal rate) {
                Helper::handleSimpleSignalNumber(this->emitOnNode, "playbackRateChanged", rate);
            });
            QObject::connect(this, &QMediaPlayer::playbackStateChanged, [=](QMediaPlayer::PlaybackState newState) {
                Helper::handleSimpleSignalEnum(this->emitOnNode, "playbackStateChanged", newState);
            });
            QObject::connect(this, &QMediaPlayer::playingChanged, [=](bool playing) {
                Helper::handleSimpleSignalBool(this->emitOnNode, "playingChanged", playing);
            });
            QObject::connect(this, &QMediaPlayer::positionChanged, [=](qint64 position) {
                Helper::handleSimpleSignalNumber(this->emitOnNode, "positionChanged", position);
            });
            QObject::connect(this, &QMediaPlayer::seekableChanged, [=](bool seekable) {
                Helper::handleSimpleSignalBool(this->emitOnNode, "seekableChanged", seekable);
            });
            QObject::connect(this, &QMediaPlayer::sourceChanged, [=](const QUrl &media) {
                Helper::handleSimpleSignalString(this->emitOnNode, "sourceChanged", media.toString());
            });
            QObject::connect(this, &QMediaPlayer::tracksChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "tracksChanged");
            });
            QObject::connect(this, &QMediaPlayer::videoOutputChanged, [=]() {
                Helper::handleSimpleSignal(this->emitOnNode, "videoOutputChanged");
            });
        }
};
