#pragma once
#include <napi.h>

#include <QPlaybackOptions>

#include "QtCore/QObject/qobject_macro.h"

class QPlaybackOptionsWrap : public Napi::ObjectWrap<QPlaybackOptionsWrap> {
 private:
  std::unique_ptr<QPlaybackOptions> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QPlaybackOptionsWrap(const Napi::CallbackInfo& info);
  QPlaybackOptions *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value networkTimeout(const Napi::CallbackInfo& info);
  Napi::Value playbackIntent(const Napi::CallbackInfo& info);
  // qsizetype isn't supported on NodeGUI yet
//   Napi::Value probeSize(const Napi::CallbackInfo& info);
  Napi::Value resetNetworkTimeout(const Napi::CallbackInfo& info);
  Napi::Value resetPlaybackIntent(const Napi::CallbackInfo& info);
  Napi::Value resetProbeSize(const Napi::CallbackInfo& info);
  Napi::Value setNetworkTimeout(const Napi::CallbackInfo& info);
  Napi::Value setPlaybackIntent(const Napi::CallbackInfo& info);
  // qsizetype isn't supported on NodeGUI yet
//   Napi::Value setProbeSize(const Napi::CallbackInfo& info);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};