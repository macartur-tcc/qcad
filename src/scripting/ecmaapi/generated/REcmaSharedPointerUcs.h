#pragma once
// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMASHAREDPOINTERUCS_H
        #define RECMASHAREDPOINTERUCS_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RUcs.h"
            
            typedef QSharedPointer<RUcs> RUcsPointer;
        

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaSharedPointerUcs {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getRObject(QScriptContext *context,
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
        clone
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSelectedForPropertyEditing
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setOrigin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setXAxisDirection
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setYAxisDirection
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getZAxisDirection
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mapFromUcs
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mapToUcs
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RUcs* getSelf(const QString& fName, QScriptContext* context)
    ;static RUcs* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  QScriptValue data
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue isNull
    (QScriptContext *context, QScriptEngine *engine)
    ;};
    #endif
    