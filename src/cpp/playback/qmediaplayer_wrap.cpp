#include "qmediaplayer_wrap.h"
#include "../helper.h"

#include "../audio/qaudiobufferoutput_wrap.h"
#include "../audio/qaudiooutput_wrap.h"
#include "../misc/qmediametadata_wrap.h"
#include "../misc/qmediatimerange_wrap.h"
#include "./qplaybackoptions_wrap.h"
#include "../video/qvideosink_wrap.h"

#include <QObject>
#include <QMediaPlayer>

#include <Extras/Utils/nutils.h>
#include <QtCore/QUrl/qurl_wrap.h>

Napi::FunctionReference QMediaPlayerWrap::constructor;

Napi::Object QMediaPlayerWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QMediaPlayer", {
        // Methods
        InstanceMethod("activeAudioTrack", &QMediaPlayerWrap::activeAudioTrack),
        InstanceMethod("activeSubtitleTrack", &QMediaPlayerWrap::activeSubtitleTrack),
        InstanceMethod("activeVideoTrack", &QMediaPlayerWrap::activeVideoTrack),
        InstanceMethod("audioBufferOutput", &QMediaPlayerWrap::audioBufferOutput),
        InstanceMethod("audioOutput", &QMediaPlayerWrap::audioOutput),
        InstanceMethod("audioTracks", &QMediaPlayerWrap::audioTracks),
        InstanceMethod("bufferProgress", &QMediaPlayerWrap::bufferProgress),
        InstanceMethod("bufferedTimeRange", &QMediaPlayerWrap::bufferedTimeRange),
        InstanceMethod("duration", &QMediaPlayerWrap::duration),
        InstanceMethod("error", &QMediaPlayerWrap::error),
        InstanceMethod("errorString", &QMediaPlayerWrap::errorString),
        InstanceMethod("hasAudio", &QMediaPlayerWrap::hasAudio),
        InstanceMethod("hasVideo", &QMediaPlayerWrap::hasVideo),
        InstanceMethod("isAvailable", &QMediaPlayerWrap::isAvailable),
        InstanceMethod("isPlaying", &QMediaPlayerWrap::isPlaying),
        InstanceMethod("isSeekable", &QMediaPlayerWrap::isSeekable),
        InstanceMethod("loops", &QMediaPlayerWrap::loops),
        InstanceMethod("mediaStatus", &QMediaPlayerWrap::mediaStatus),
        InstanceMethod("metaData", &QMediaPlayerWrap::metaData),
        InstanceMethod("pitchCompensation", &QMediaPlayerWrap::pitchCompensation),
        InstanceMethod("pitchCompensationAvailability", &QMediaPlayerWrap::pitchCompensationAvailability),
        InstanceMethod("playbackOptions", &QMediaPlayerWrap::playbackOptions),
        InstanceMethod("playbackRate", &QMediaPlayerWrap::playbackRate),
        InstanceMethod("playbackState", &QMediaPlayerWrap::playbackState),
        InstanceMethod("position", &QMediaPlayerWrap::position),
        InstanceMethod("setActiveAudioTrack", &QMediaPlayerWrap::setActiveAudioTrack),
        InstanceMethod("setActiveSubtitleTrack", &QMediaPlayerWrap::setActiveSubtitleTrack),
        InstanceMethod("setActiveVideoTrack", &QMediaPlayerWrap::setActiveVideoTrack),
        InstanceMethod("setAudioBufferOutput", &QMediaPlayerWrap::setAudioBufferOutput),
        InstanceMethod("setAudioOutput", &QMediaPlayerWrap::setAudioOutput),
        InstanceMethod("setLoops", &QMediaPlayerWrap::setLoops),
        InstanceMethod("setVideoOutput", &QMediaPlayerWrap::setVideoOutput),
        InstanceMethod("setVideoSink", &QMediaPlayerWrap::setVideoSink),
        InstanceMethod("source", &QMediaPlayerWrap::source),
        // InstanceMethod("sourceDevice", &QMediaPlayerWrap::sourceDevice),
        InstanceMethod("subtitleTracks", &QMediaPlayerWrap::subtitleTracks),
        InstanceMethod("videoOutput", &QMediaPlayerWrap::videoOutput),
        InstanceMethod("videoSink", &QMediaPlayerWrap::videoSink),
        InstanceMethod("videoTracks", &QMediaPlayerWrap::videoTracks),
        // Slots
        InstanceMethod("pause", &QMediaPlayerWrap::pause),
        InstanceMethod("play", &QMediaPlayerWrap::play),
        InstanceMethod("resetPlaybackOptions", &QMediaPlayerWrap::resetPlaybackOptions),
        InstanceMethod("setPitchCompensation", &QMediaPlayerWrap::setPitchCompensation),
        InstanceMethod("setPlaybackOptions", &QMediaPlayerWrap::setPlaybackOptions),
        InstanceMethod("setPlaybackRate", &QMediaPlayerWrap::setPlaybackRate),
        InstanceMethod("setPosition", &QMediaPlayerWrap::setPosition),
        InstanceMethod("setSource", &QMediaPlayerWrap::setSource),
        // InstanceMethod("setSourceDevice", &QMediaPlayerWrap::setSourceDevice),
        InstanceMethod("stop", &QMediaPlayerWrap::stop),
        QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaPlayerWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QMediaPlayer", func);
    return exports;
}

QMediaPlayerWrap::QMediaPlayerWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QMediaPlayerWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = new NMediaPlayer();
    } else if (info.Length() == 1) {
        this->instance = new NMediaPlayer(Helper::getQObjectFromValue(info[0]));
    } else {
        Napi::TypeError::New(env, "Wrong number of arguments, refer to QMediaPlayer()").ThrowAsJavaScriptException();
        return;
    }
    this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QMediaPlayerWrap::~QMediaPlayerWrap() {
    extrautils::safeDelete(this->instance);
}

NMediaPlayer* QMediaPlayerWrap::getInternalInstance() {
    return this->instance;
}

Napi::Value QMediaPlayerWrap::activeAudioTrack(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->activeAudioTrack());
}

Napi::Value QMediaPlayerWrap::activeSubtitleTrack(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->activeSubtitleTrack());
}

Napi::Value QMediaPlayerWrap::activeVideoTrack(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->activeVideoTrack());
}

Napi::Value QMediaPlayerWrap::audioBufferOutput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QAudioBufferOutput* result = this->instance->audioBufferOutput();
    if (result) {
        return QAudioBufferOutputWrap::constructor.New({
            Napi::External<QAudioBufferOutput>::New(env, result)
        });
    } else {
        return env.Null();
    }
}

Napi::Value QMediaPlayerWrap::audioOutput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QAudioOutput* result = this->instance->audioOutput();
    if (result) {
        return QAudioOutputWrap::constructor.New({
            Napi::External<QAudioOutput>::New(env, result)
        });
    } else {
        return env.Null();
    }
}

Napi::Value QMediaPlayerWrap::audioTracks(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QMediaMetaData> tracks = this->instance->audioTracks();
    int length = tracks.length();
    Napi::Array retval = Napi::Array::New(env, length);
    for (int i = 0; i < length; i++) {
        QMediaMetaData track = tracks[i];
        auto instance = QMediaMetaDataWrap::constructor.New({
            Napi::External<QMediaMetaData>::New(env, new QMediaMetaData(track))
        });
        retval[i] = instance;
    }
    return retval;
}

Napi::Value QMediaPlayerWrap::bufferProgress(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->bufferProgress());
}

Napi::Value QMediaPlayerWrap::bufferedTimeRange(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return QMediaTimeRangeWrap::constructor.New({
        Napi::External<QMediaTimeRange>::New(
            env, 
            new QMediaTimeRange(this->instance->bufferedTimeRange())
        )
    });
}

Napi::Value QMediaPlayerWrap::duration(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->duration());
}

Napi::Value QMediaPlayerWrap::error(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(), 
        static_cast<int>(this->instance->error())
    );
}

Napi::Value QMediaPlayerWrap::errorString(const Napi::CallbackInfo& info) {
    return Napi::String::New(info.Env(), this->instance->errorString().toStdString());
}

Napi::Value QMediaPlayerWrap::hasAudio(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->hasAudio());
}

Napi::Value QMediaPlayerWrap::hasVideo(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->hasVideo());
}

Napi::Value QMediaPlayerWrap::isAvailable(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isAvailable());
}

Napi::Value QMediaPlayerWrap::isPlaying(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isPlaying());
}

Napi::Value QMediaPlayerWrap::isSeekable(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isSeekable());
}

Napi::Value QMediaPlayerWrap::loops(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->loops());
}

Napi::Value QMediaPlayerWrap::mediaStatus(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(), 
        static_cast<int>(this->instance->mediaStatus())
    );
}

Napi::Value QMediaPlayerWrap::metaData(const Napi::CallbackInfo& info) {
    return QMediaMetaDataWrap::constructor.New({
        Napi::External<QMediaMetaData>::New(
            info.Env(), 
            new QMediaMetaData(this->instance->metaData())
        )
    });
}

Napi::Value QMediaPlayerWrap::pitchCompensation(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->pitchCompensation());
}

Napi::Value QMediaPlayerWrap::pitchCompensationAvailability(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(), 
        static_cast<int>(this->instance->pitchCompensationAvailability())
    );
}

Napi::Value QMediaPlayerWrap::playbackOptions(const Napi::CallbackInfo& info) {
    return QPlaybackOptionsWrap::constructor.New({
        Napi::External<QPlaybackOptions>::New(
            info.Env(), 
            new QPlaybackOptions(this->instance->playbackOptions())
        )
    });
}

Napi::Value QMediaPlayerWrap::playbackRate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->playbackRate());
}

Napi::Value QMediaPlayerWrap::playbackState(const Napi::CallbackInfo& info) {
    return Napi::Number::New(
        info.Env(), 
        static_cast<int>(this->instance->playbackState())
    );
}

Napi::Value QMediaPlayerWrap::position(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->instance->position());
}

Napi::Value QMediaPlayerWrap::setActiveAudioTrack(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setActiveAudioTrack()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setActiveAudioTrack(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setActiveSubtitleTrack(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setActiveSubtitleTrack()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setActiveSubtitleTrack(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setActiveVideoTrack(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setActiveVideoTrack()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setActiveVideoTrack(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setAudioBufferOutput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setAudioBufferOutput()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object outputObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioBufferOutputWrap* outputWrap = Napi::ObjectWrap<QAudioBufferOutputWrap>::Unwrap(outputObj);
    QAudioBufferOutput* output = outputWrap->getInternalInstance();
    this->instance->setAudioBufferOutput(output);
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setAudioOutput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setAudioOutput()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object outputObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QAudioOutputWrap* outputWrap = Napi::ObjectWrap<QAudioOutputWrap>::Unwrap(outputObj);
    QAudioOutput* output = outputWrap->getInternalInstance();
    this->instance->setAudioOutput(output);
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setLoops(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setLoops()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setLoops(info[0].As<Napi::Number>().Int32Value());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setVideoOutput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setVideoOutput()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setVideoOutput(Helper::getQObjectFromValue(info[0]));
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setVideoSink(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setVideoSink()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object sinkObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QVideoSinkWrap* sinkWrap = Napi::ObjectWrap<QVideoSinkWrap>::Unwrap(sinkObj);
    QVideoSink* sink = sinkWrap->getInternalInstance();
    this->instance->setVideoSink(sink);
    return env.Null();
}

Napi::Value QMediaPlayerWrap::source(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return QUrlWrap::constructor.New({
        Napi::External<QUrl>::New(env, new QUrl(this->instance->source().toString()))
    });
}

Napi::Value QMediaPlayerWrap::subtitleTracks(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QMediaMetaData> tracks = this->instance->subtitleTracks();
    int length = tracks.length();
    Napi::Array retval = Napi::Array::New(env, length);
    for (int i = 0; i < length; i++) {
        QMediaMetaData track = tracks[i];
        auto instance = QMediaMetaDataWrap::constructor.New({
            Napi::External<QMediaMetaData>::New(env, new QMediaMetaData(track))
        });
        retval[i] = instance;
    }
    return retval;
}

Napi::Value QMediaPlayerWrap::videoOutput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QObject* result = this->instance->videoOutput();
    if (result) {
        return WrapperCache::instance.getWrapper(env, result);
    } else {
        return env.Null();
    }
}

Napi::Value QMediaPlayerWrap::videoSink(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QVideoSink* result = this->instance->videoSink();
    if (result) {
        return QVideoSinkWrap::constructor.New({
            Napi::External<QVideoSink>::New(env, result)
        });
    } else {
        return env.Null();
    }
}

Napi::Value QMediaPlayerWrap::videoTracks(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QMediaMetaData> tracks = this->instance->videoTracks();
    int length = tracks.length();
    Napi::Array retval = Napi::Array::New(env, length);
    for (int i = 0; i < length; i++) {
        QMediaMetaData track = tracks[i];
        auto instance = QMediaMetaDataWrap::constructor.New({
            Napi::External<QMediaMetaData>::New(env, new QMediaMetaData(track))
        });
        retval[i] = instance;
    }
    return retval;
}

Napi::Value QMediaPlayerWrap::pause(const Napi::CallbackInfo& info) {
    this->instance->pause();
    return info.Env().Null();
}

Napi::Value QMediaPlayerWrap::play(const Napi::CallbackInfo& info) {
    this->instance->play();
    return info.Env().Null();
}

Napi::Value QMediaPlayerWrap::resetPlaybackOptions(const Napi::CallbackInfo& info) {
    this->instance->resetPlaybackOptions();
    return info.Env().Null();
}

Napi::Value QMediaPlayerWrap::setPitchCompensation(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsBoolean()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setPitchCompensation()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setPitchCompensation(info[0].As<Napi::Boolean>().Value());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setPlaybackOptions(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setPlaybackOptions()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object optionsObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QPlaybackOptionsWrap* optionsWrap = Napi::ObjectWrap<QPlaybackOptionsWrap>::Unwrap(optionsObj);
    QPlaybackOptions* options = optionsWrap->getInternalInstance();
    this->instance->setPlaybackOptions(*options);
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setPlaybackRate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setPlaybackRate()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setPlaybackRate(info[0].As<Napi::Number>().DoubleValue());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setPosition(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setPosition()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->setPosition(info[0].As<Napi::Number>().Int64Value());
    return env.Null();
}

Napi::Value QMediaPlayerWrap::setSource(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || (!info[0].IsString() && !info[0].IsObject())) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaPlayer.setSource()").ThrowAsJavaScriptException();
        return env.Null();
    }
    if (info[0].IsString()) {
        this->instance->setSource(
            QUrl(QString::fromStdString(info[0].As<Napi::String>().Utf8Value()))
        );
        return env.Null();
    }
    Napi::Object sourceObj = static_cast<Napi::Value>(info[0]).As<Napi::Object>();
    QUrlWrap* sourceWrap = Napi::ObjectWrap<QUrlWrap>::Unwrap(sourceObj);
    QUrl source = *sourceWrap->getInternalInstance();
    this->instance->setSource(source);
    return env.Null();
}


Napi::Value QMediaPlayerWrap::stop(const Napi::CallbackInfo& info) {
    this->instance->stop();
    return info.Env().Null();
}
