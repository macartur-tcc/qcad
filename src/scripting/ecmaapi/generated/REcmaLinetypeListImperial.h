#pragma once
// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMALINETYPELISTIMPERIAL_H
        #define RECMALINETYPELISTIMPERIAL_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RLinetypeListImperial.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaLinetypeListImperial {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getRLinetypeList(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        init
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        uninit
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getNames
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        get
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RLinetypeListImperial* getSelf(const QString& fName, QScriptContext* context)
    ;static RLinetypeListImperial* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    