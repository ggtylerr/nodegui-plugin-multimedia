#pragma once
#include <napi.h>
#include <stdlib.h>
#include <type_traits>

#include "QtCore/QObject/qobject_macro.h"

class Helper {
    public:
        static void handleSimpleSignal(const Napi::FunctionReference& emitOnNode, const char *name);
        static void handleSimpleSignalString(const Napi::FunctionReference& emitOnNode, const char *name, QString var);
        static void handleSimpleSignalNumber(const Napi::FunctionReference& emitOnNode, const char *name, double var);
        static void handleSimpleSignalBool(const Napi::FunctionReference& emitOnNode, const char *name, bool var);

        // Handles a simple, void returned signal with an enum classed variable.
        template <typename Enum>
        static void handleSimpleSignalEnum(const Napi::FunctionReference& emitOnNode, const char *name, Enum var) {
            static_assert(std::is_enum_v<Enum>, "Enum must be an enum type.");
            handleSimpleSignalNumber(emitOnNode, name, static_cast<int>(var));
        }

        static QObject* getQObjectFromValue(const Napi::Value& value);
        static QWidget* getQWidgetFromValue(const Napi::Value& value);
};
