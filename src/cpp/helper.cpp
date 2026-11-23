#include "helper.h"

#include <core/WrapperCache/wrappercache.h>
#include <type_traits>

// Handles a simple, void returned signal with no variables.
void Helper::handleSimpleSignal(const Napi::FunctionReference& emitOnNode, const char *name) {
    const Napi::Env env = emitOnNode.Env();
    Napi::HandleScope scope(env);
    emitOnNode.Call({ Napi::String::New(env, name) });
}

// Handles a simple, void returned signal with a QString variable.
void Helper::handleSimpleSignalString(const Napi::FunctionReference& emitOnNode, const char *name, QString var) {
    const Napi::Env env = emitOnNode.Env();
    Napi::HandleScope scope(env);
    emitOnNode.Call({ 
        Napi::String::New(env, name),
        Napi::String::New(env, var.toStdString())
    });
}

// Handles a simple, void returned signal with a numerical (int, double, float, qint64, qreal, etc.) variable.
void Helper::handleSimpleSignalNumber(const Napi::FunctionReference& emitOnNode, const char *name, double var) {
    const Napi::Env env = emitOnNode.Env();
    Napi::HandleScope scope(env);
    emitOnNode.Call({ 
        Napi::String::New(env, name),
        Napi::Number::New(env, var)
    });
}

// Handles a simple, void returned signal with a boolean variable.
void Helper::handleSimpleSignalBool(const Napi::FunctionReference& emitOnNode, const char *name, bool var) {
    const Napi::Env env = emitOnNode.Env();
    Napi::HandleScope scope(env);
    emitOnNode.Call({ 
        Napi::String::New(env, name),
        Napi::Value::From(env, var)
    });
}

QObject* Helper::getQObjectFromValue(const Napi::Value& value) {
    if (value.IsNull() || value.IsUndefined()) return nullptr;
    if (value.IsExternal()) return value.As<Napi::External<QObject>>().Data();

    Napi::Object obj = value.As<Napi::Object>();
    return obj
        .Get("__external_qobject__")
        .As<Napi::Function>()
        .Call(obj, {})
        .As<Napi::External<QObject>>().Data();
}
