#include "qmediatimerange_wrap.h"

#include <QMediaTimeRange>

Napi::FunctionReference QMediaTimeRangeWrap::constructor;

Napi::Object QMediaTimeRangeWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QMediaTimeRange", {
        InstanceMethod("addInterval", &QMediaTimeRangeWrap::addInterval),
        InstanceMethod("addTimeRange", &QMediaTimeRangeWrap::addTimeRange),
        InstanceMethod("clear", &QMediaTimeRangeWrap::clear),
        InstanceMethod("contains", &QMediaTimeRangeWrap::contains),
        InstanceMethod("earliestTime", &QMediaTimeRangeWrap::earliestTime),
        InstanceMethod("intervals", &QMediaTimeRangeWrap::intervals),
        InstanceMethod("isContinuous", &QMediaTimeRangeWrap::isContinuous),
        InstanceMethod("isEmpty", &QMediaTimeRangeWrap::isEmpty),
        InstanceMethod("latestTime", &QMediaTimeRangeWrap::latestTime),
        InstanceMethod("removeInterval", &QMediaTimeRangeWrap::removeInterval),
        InstanceMethod("removeTimeRange", &QMediaTimeRangeWrap::removeTimeRange),
        InstanceMethod("swap", &QMediaTimeRangeWrap::swap),
        
        InstanceMethod("add", &QMediaTimeRangeWrap::add),
        InstanceMethod("sub", &QMediaTimeRangeWrap::sub),
        InstanceMethod("equals", &QMediaTimeRangeWrap::equals),

        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaTimeRangeWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QMediaTimeRange", func);
    return exports;
}

QMediaTimeRangeWrap::QMediaTimeRangeWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QMediaTimeRangeWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        // QMediaTimeRange()
        this->instance = std::make_unique<QMediaTimeRange>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        // QMediaTimeRange(&range)
        QMediaTimeRange* range = info[0].As<Napi::External<QMediaTimeRange>>().Data();
        this->instance = std::make_unique<QMediaTimeRange>(*range);
    } else if (info.Length() == 1 && info[0].IsObject()) {
        Napi::Object obj = info[0].As<Napi::Object>();
        if (obj.Has("start") && obj.Has("end")) {
            if (obj.Get("start").IsNumber() && obj.Get("end").IsNumber()) {
                // QMediaTimeRange(&interval)
                this->instance = std::make_unique<QMediaTimeRange>(QMediaTimeRangeWrap::NToInterval(info[0]));
            }
        } else {
            // QMediaTimeRange(&&other)
            QMediaTimeRangeWrap* other = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(obj);
            this->instance = std::make_unique<QMediaTimeRange>(*other->getInternalInstance());
        }
    } else if (info.Length() == 2 && info[0].IsNumber() && info[1].IsNumber()) {
        // QMediaTimeRange(start, end)
        qint64 start = info[0].As<Napi::Number>().Int64Value();
        qint64 end = info[1].As<Napi::Number>().Int64Value();
        this->instance = std::make_unique<QMediaTimeRange>(start, end);
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange()").ThrowAsJavaScriptException();
        this->instance.reset();
    }
}

QMediaTimeRangeWrap::~QMediaTimeRangeWrap() {
    this->instance.reset();
}

QMediaTimeRange* QMediaTimeRangeWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QMediaTimeRangeWrap::addInterval(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // interval
    if (info.Length() == 1 && info[0].IsObject()) {
        Napi::Object obj = info[0].As<Napi::Object>();
        if (obj.Has("start") && obj.Has("end")) {
            if (obj.Get("start").IsNumber() && obj.Get("end").IsNumber()) {
                (*this->instance).addInterval(QMediaTimeRangeWrap::NToInterval(info[0]));
            }
        }
    }
    // start + end
    else if (info.Length() == 2 && info[0].IsNumber() && info[1].IsNumber()) {
        qint64 start = info[0].As<Napi::Number>().Int64Value();
        qint64 end = info[1].As<Napi::Number>().Int64Value();
        (*this->instance).addInterval(start, end);
    }
    else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.addInterval()").ThrowAsJavaScriptException();
    }
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::addTimeRange(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.addTimeRange()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QMediaTimeRangeWrap* rangeWrap = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(info[0].As<Napi::Object>());
    QMediaTimeRange* range = rangeWrap->getInternalInstance();
    (*this->instance).addTimeRange(*range);
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::clear(const Napi::CallbackInfo& info) {
    this->instance->clear();
    return info.Env().Null();
}

Napi::Value QMediaTimeRangeWrap::contains(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.contains()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Boolean::New(env, (*this->instance).contains(
        info[0].As<Napi::Number>().Int64Value()
    ));
}

Napi::Value QMediaTimeRangeWrap::earliestTime(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), (*this->instance).earliestTime());
}

Napi::Value QMediaTimeRangeWrap::intervals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QMediaTimeRange::Interval> intervals = this->instance->intervals();
    int length = intervals.length();
    Napi::Array out = Napi::Array::New(env, length);
    for (int i = 0; i < length; i++) {
        QMediaTimeRange::Interval interval = intervals[i];
        out[i] = QMediaTimeRangeWrap::intervalToN(env, interval);
    }
    return out;
}

Napi::Value QMediaTimeRangeWrap::isContinuous(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), (*this->instance).isContinuous());
}

Napi::Value QMediaTimeRangeWrap::isEmpty(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), (*this->instance).isEmpty());
}

Napi::Value QMediaTimeRangeWrap::latestTime(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), (*this->instance).latestTime());
}

Napi::Value QMediaTimeRangeWrap::removeInterval(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // interval
    if (info.Length() == 1 && info[0].IsObject()) {
        Napi::Object obj = info[0].As<Napi::Object>();
        if (obj.Has("start") && obj.Has("end")) {
            if (obj.Get("start").IsNumber() && obj.Get("end").IsNumber()) {
                (*this->instance).removeInterval(QMediaTimeRangeWrap::NToInterval(info[0]));
            }
        }
    }
    // start + end
    else if (info.Length() == 2 && info[0].IsNumber() && info[1].IsNumber()) {
        qint64 start = info[0].As<Napi::Number>().Int64Value();
        qint64 end = info[1].As<Napi::Number>().Int64Value();
        (*this->instance).removeInterval(start, end);
    }
    else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.removeInterval()").ThrowAsJavaScriptException();
    }
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::removeTimeRange(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.removeTimeRange()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QMediaTimeRangeWrap* rangeWrap = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(info[0].As<Napi::Object>());
    QMediaTimeRange* range = rangeWrap->getInternalInstance();
    (*this->instance).removeTimeRange(*range);
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::swap(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.swap()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QMediaTimeRangeWrap* rangeWrap = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(info[0].As<Napi::Object>());
    QMediaTimeRange* range = rangeWrap->getInternalInstance();
    (*this->instance).swap(*range);
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::add(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.add()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object obj = info[0].As<Napi::Object>();
    // interval
    if (obj.Has("start") && obj.Has("end")) {
        if (obj.Get("start").IsNumber() && obj.Get("end").IsNumber()) {
            *this->instance += QMediaTimeRangeWrap::NToInterval(info[0]);
            return env.Null();
        }
    }
    // range
    QMediaTimeRangeWrap* rangeWrap = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(obj);
    QMediaTimeRange* range = rangeWrap->getInternalInstance();
    *this->instance += *range;
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::sub(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.sub()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object obj = info[0].As<Napi::Object>();
    // interval
    if (obj.Has("start") && obj.Has("end")) {
        if (obj.Get("start").IsNumber() && obj.Get("end").IsNumber()) {
            *this->instance -= QMediaTimeRangeWrap::NToInterval(info[0]);
            return env.Null();
        }
    }
    // range
    QMediaTimeRangeWrap* rangeWrap = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(obj);
    QMediaTimeRange* range = rangeWrap->getInternalInstance();
    *this->instance -= *range;
    return env.Null();
}

Napi::Value QMediaTimeRangeWrap::equals(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaTimeRange.equals()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object rangeObj = info[0].As<Napi::Object>();
    QMediaTimeRangeWrap* rangeWrap = Napi::ObjectWrap<QMediaTimeRangeWrap>::Unwrap(rangeObj);
    QMediaTimeRange* range = rangeWrap->getInternalInstance();
    return Napi::Boolean::New(env, (*this->instance == *range));
}

Napi::Object QMediaTimeRangeWrap::intervalToN(const Napi::Env& env, const QMediaTimeRange::Interval& interval) {
    Napi::Object out = Napi::Object::New(env);
    out.Set("start", Napi::Number::New(env, static_cast<double>(interval.start())));
    out.Set("end", Napi::Number::New(env, static_cast<double>(interval.end())));
    return out;
}

QMediaTimeRange::Interval QMediaTimeRangeWrap::NToInterval(const Napi::Value& value) {
    Napi::Object out = value.As<Napi::Object>();
    qint64 start = out.Get("start").As<Napi::Number>().Int64Value();
    qint64 end = out.Get("end").As<Napi::Number>().Int64Value();
    return QMediaTimeRange::Interval(start, end);
}
