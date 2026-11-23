#include "qmediametadata_wrap.h"

#include <QMediaMetaData>

Napi::FunctionReference QMediaMetaDataWrap::constructor;

Napi::Object QMediaMetaDataWrap::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QMediaMetaData", {
        InstanceMethod("asKeyValueRange", &QMediaMetaDataWrap::asKeyValueRange),
        InstanceMethod("clear", &QMediaMetaDataWrap::clear),
        InstanceMethod("insert", &QMediaMetaDataWrap::insert),
        InstanceMethod("isEmpty", &QMediaMetaDataWrap::isEmpty),
        InstanceMethod("keys", &QMediaMetaDataWrap::keys),
        InstanceMethod("remove", &QMediaMetaDataWrap::remove),
        InstanceMethod("stringValue", &QMediaMetaDataWrap::stringValue),
        InstanceMethod("value", &QMediaMetaDataWrap::value),
        StaticMethod("metaDataKeyToString", &StaticQMediaMetaDataWrapMethods::metaDataKeyToString),
        COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaMetaDataWrap)
    });
    constructor = Napi::Persistent(func);
    exports.Set("QMediaMetaData", func);
    return exports;
}

QMediaMetaDataWrap::QMediaMetaDataWrap(const Napi::CallbackInfo& info) : Napi::ObjectWrap<QMediaMetaDataWrap>(info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0) {
        this->instance = std::make_unique<QMediaMetaData>();
    } else if (info.Length() == 1 && info[0].IsExternal()) {
        this->instance.reset(info[0].As<Napi::External<QMediaMetaData>>().Data());
    } else {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaMetaData()").ThrowAsJavaScriptException();
        return;
    }
    this->rawData = this->instance.get();
}

QMediaMetaData* QMediaMetaDataWrap::getInternalInstance() {
    return this->instance.get();
}

Napi::Value QMediaMetaDataWrap::asKeyValueRange(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object out = Napi::Object::New(env);
    for (auto&& [key, val] : this->instance->asKeyValueRange()) {
        const std::string keyStr = QMediaMetaData::metaDataKeyToString(key).toStdString();
        QVariant var = val;
        if (var.isNull()) out.Set(keyStr, env.Null());
        else out.Set(keyStr, QVariantWrap::constructor.New({
            Napi::External<QVariant>::New(env, new QVariant(var))
        }));
    }
    return out;
}

Napi::Value QMediaMetaDataWrap::clear(const Napi::CallbackInfo& info) {
    this->instance->clear();
    return info.Env().Null();
}

Napi::Value QMediaMetaDataWrap::insert(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 2 || !info[0].IsNumber() || !info[1].IsObject()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaMetaData.insert()").ThrowAsJavaScriptException();
        return env.Null();
    }
    Napi::Object variantObject = info[1].As<Napi::Object>();
    QVariantWrap* variantWrap = Napi::ObjectWrap<QVariantWrap>::Unwrap(variantObject);
    QVariant* variant = variantWrap->getInternalInstance();
    this->instance->insert(
        static_cast<QMediaMetaData::Key>(info[0].As<Napi::Number>().Int32Value()), 
        *variant
    );
    return env.Null();
}

Napi::Value QMediaMetaDataWrap::isEmpty(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), this->instance->isEmpty());
}

Napi::Value QMediaMetaDataWrap::keys(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<QMediaMetaData::Key> keys = this->instance->keys();
    int length = keys.length();
    Napi::Array out = Napi::Array::New(env, length);
    for (int i = 0; i < length; i++) {
        out[i] = Napi::Number::New(env, keys[i]);
    }
    return out;
}

Napi::Value QMediaMetaDataWrap::remove(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaMetaData.remove()").ThrowAsJavaScriptException();
        return env.Null();
    }
    this->instance->remove(
        static_cast<QMediaMetaData::Key>(
            info[0].As<Napi::Number>().Int32Value()
        )
    );
    return env.Null();
}

Napi::Value QMediaMetaDataWrap::stringValue(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaMetaData.stringValue()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Value::From(env, (
        this->instance->stringValue(
            static_cast<QMediaMetaData::Key>(
                info[0].As<Napi::Number>().Int32Value()
            )
        )).toStdString()
    );
}

Napi::Value QMediaMetaDataWrap::value(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaMetaData.value()").ThrowAsJavaScriptException();
        return env.Null();
    }
    QVariant variant = this->instance->value(
        static_cast<QMediaMetaData::Key>(
            info[0].As<Napi::Number>().Int32Value()
        )
    );
    return QVariantWrap::constructor.New(
        {Napi::External<QVariant>::New(env, new QVariant(variant))}
    );
}

Napi::Value StaticQMediaMetaDataWrapMethods::metaDataKeyToString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Wrong number/type of arguments, refer to QMediaMetaData.metaDataKeyToString()").ThrowAsJavaScriptException();
        return env.Null();
    }
    return Napi::Value::From(env, (
        QMediaMetaData::metaDataKeyToString(
            static_cast<QMediaMetaData::Key>(
                info[0].As<Napi::Number>().Int32Value()
            )
        ).toStdString()
    ));
}
