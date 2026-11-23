#pragma once
#include <napi.h>
#include <stdlib.h>

#include <QPointer>

#include "QtCore/QObject/qobject_macro.h"
#include "nmediaplayer.hpp"

class QMediaPlayerWrap : public Napi::ObjectWrap<QMediaPlayerWrap> {
 private:
  QPointer<NMediaPlayer> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaPlayerWrap(const Napi::CallbackInfo& info);
  ~QMediaPlayerWrap();
  NMediaPlayer *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value activeAudioTrack(const Napi::CallbackInfo& info);
  Napi::Value activeSubtitleTrack(const Napi::CallbackInfo& info);
  Napi::Value activeVideoTrack(const Napi::CallbackInfo& info);
  Napi::Value audioBufferOutput(const Napi::CallbackInfo& info);
  Napi::Value audioOutput(const Napi::CallbackInfo& info);
  Napi::Value audioTracks(const Napi::CallbackInfo& info);
  Napi::Value bufferProgress(const Napi::CallbackInfo& info);
  Napi::Value bufferedTimeRange(const Napi::CallbackInfo& info);
  Napi::Value duration(const Napi::CallbackInfo& info);
  Napi::Value error(const Napi::CallbackInfo& info);
  Napi::Value errorString(const Napi::CallbackInfo& info);
  Napi::Value hasAudio(const Napi::CallbackInfo& info);
  Napi::Value hasVideo(const Napi::CallbackInfo& info);
  Napi::Value isAvailable(const Napi::CallbackInfo& info);
  Napi::Value isPlaying(const Napi::CallbackInfo& info);
  Napi::Value isSeekable(const Napi::CallbackInfo& info);
  Napi::Value loops(const Napi::CallbackInfo& info);
  Napi::Value mediaStatus(const Napi::CallbackInfo& info);
  Napi::Value metaData(const Napi::CallbackInfo& info);
  Napi::Value pitchCompensation(const Napi::CallbackInfo& info);
  Napi::Value pitchCompensationAvailability(const Napi::CallbackInfo& info);
  Napi::Value playbackOptions(const Napi::CallbackInfo& info);
  Napi::Value playbackRate(const Napi::CallbackInfo& info);
  Napi::Value playbackState(const Napi::CallbackInfo& info);
  Napi::Value position(const Napi::CallbackInfo& info);
  Napi::Value setActiveAudioTrack(const Napi::CallbackInfo& info);
  Napi::Value setActiveSubtitleTrack(const Napi::CallbackInfo& info);
  Napi::Value setActiveVideoTrack(const Napi::CallbackInfo& info);
  Napi::Value setAudioBufferOutput(const Napi::CallbackInfo& info);
  Napi::Value setAudioOutput(const Napi::CallbackInfo& info);
  Napi::Value setLoops(const Napi::CallbackInfo& info);
  Napi::Value setVideoOutput(const Napi::CallbackInfo& info);
  Napi::Value setVideoSink(const Napi::CallbackInfo& info);
  Napi::Value source(const Napi::CallbackInfo& info);
  // QIODevice isn't supported on NodeGUI yet
//   Napi::Value sourceDevice(const Napi::CallbackInfo& info);
  Napi::Value subtitleTracks(const Napi::CallbackInfo& info);
  Napi::Value videoOutput(const Napi::CallbackInfo& info);
  Napi::Value videoSink(const Napi::CallbackInfo& info);
  Napi::Value videoTracks(const Napi::CallbackInfo& info);

  // Wrapped slots
  Napi::Value pause(const Napi::CallbackInfo& info);
  Napi::Value play(const Napi::CallbackInfo& info);
  Napi::Value resetPlaybackOptions(const Napi::CallbackInfo& info);
  Napi::Value setPitchCompensation(const Napi::CallbackInfo& info);
  Napi::Value setPlaybackOptions(const Napi::CallbackInfo& info);
  Napi::Value setPlaybackRate(const Napi::CallbackInfo& info);
  Napi::Value setPosition(const Napi::CallbackInfo& info);
  Napi::Value setSource(const Napi::CallbackInfo& info);
//   Napi::Value setSourceDevice(const Napi::CallbackInfo& info);
  Napi::Value stop(const Napi::CallbackInfo& info);

  QOBJECT_WRAPPED_METHODS_DECLARATION
};
