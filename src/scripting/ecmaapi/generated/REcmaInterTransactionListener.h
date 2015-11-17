#pragma once
// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMAINTERTRANSACTIONLISTENER_H
        #define RECMAINTERTRANSACTIONLISTENER_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RInterTransactionListener.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaInterTransactionListener {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        updateInterTransactionListener
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RInterTransactionListener* getSelf(const QString& fName, QScriptContext* context)
    ;static RInterTransactionListener* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    