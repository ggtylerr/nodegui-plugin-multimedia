#pragma once
#include <napi.h>

#include <QMediaTimeRange>

#include "QtCore/QObject/qobject_macro.h"

class QMediaTimeRangeWrap : public Napi::ObjectWrap<QMediaTimeRangeWrap> {
 private:
  std::unique_ptr<QMediaTimeRange> instance;
 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaTimeRangeWrap(const Napi::CallbackInfo& info);
  ~QMediaTimeRangeWrap();
  QMediaTimeRange *getInternalInstance();
  static Napi::FunctionReference constructor;
  // Wrapped Functions
  Napi::Value addInterval(const Napi::CallbackInfo& info);
  Napi::Value addTimeRange(const Napi::CallbackInfo& info);
  Napi::Value clear(const Napi::CallbackInfo& info);
  Napi::Value contains(const Napi::CallbackInfo& info);
  Napi::Value earliestTime(const Napi::CallbackInfo& info);
  Napi::Value intervals(const Napi::CallbackInfo& info);
  Napi::Value isContinuous(const Napi::CallbackInfo& info);
  Napi::Value isEmpty(const Napi::CallbackInfo& info);
  Napi::Value latestTime(const Napi::CallbackInfo& info);
  Napi::Value removeInterval(const Napi::CallbackInfo& info);
  Napi::Value removeTimeRange(const Napi::CallbackInfo& info);
  Napi::Value swap(const Napi::CallbackInfo& info);
  // Operator Functions
  Napi::Value add(const Napi::CallbackInfo& info);
  Napi::Value sub(const Napi::CallbackInfo& info);
  Napi::Value equals(const Napi::CallbackInfo& info);
  // Struct Conversion Functions
  Napi::Object intervalToN(const Napi::Env& env, const QMediaTimeRange::Interval& interval);
  QMediaTimeRange::Interval NToInterval(const Napi::Value& value);

  COMPONENT_WRAPPED_METHODS_DECLARATION
};