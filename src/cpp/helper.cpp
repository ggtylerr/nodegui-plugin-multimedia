#include "helper.h"

#include <core/WrapperCache/wrappercache.h>
#include <type_traits>

#include <QWidget>

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
    if (!value.IsObject()) return nullptr;

    Napi::Object obj = value.As<Napi::Object>();

    // Grab native element if it isn't passed directly
    if (obj.Has("native") && obj.Get("native").IsObject()) {
        obj = obj.Get("native").As<Napi::Object>();
    }

    // Grab if accessor is available
    if (obj.Has("__external_qobject__")) {
        Napi::Value ext = obj.Get("__external_qobject__");
        if (ext.IsFunction()) {
            Napi::Value fun = ext.As<Napi::Function>().Call(obj, {});
            if (fun.IsExternal()) {
                return fun.As<Napi::External<QObject>>().Data();
            }
        }
    }

    return nullptr;
}

QWidget* Helper::getQWidgetFromValue(const Napi::Value& value) {
    if (value.IsNull() || value.IsUndefined()) return nullptr;
    if (value.IsExternal()) return value.As<Napi::External<QWidget>>().Data();
    if (!value.IsObject()) return nullptr;

    Napi::Object obj = value.As<Napi::Object>();

    // Grab native element if it isn't passed directly
    if (obj.Has("native") && obj.Get("native").IsObject()) {
        obj = obj.Get("native").As<Napi::Object>();
    }

    // Grab if accessor is available (prob not)
    if (obj.Has("__external_qwidget__")) {
        Napi::Value ext = obj.Get("__external_qwidget__");
        if (ext.IsFunction()) {
            Napi::Value fun = ext.As<Napi::Function>().Call(obj, {});
            if (fun.IsExternal()) {
                return fun.As<Napi::External<QWidget>>().Data();
            }
        }
    }

    // Grab as a QObject instead if it isn't
    if (obj.Has("__external_qobject__")) {
        return qobject_cast<QWidget*>(getQObjectFromValue(obj));
    }

    return nullptr;
}
