#pragma once
// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #ifndef RECMAELLIPSEDATA_H
        #define RECMAELLIPSEDATA_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "REllipseData.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaEllipseData {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getREntityData(QScriptContext *context,
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
        getEllipse
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFoci
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCenter
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMajorRadius
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMajorPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getMinorPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setMinorPoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getRatio
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getStartParam
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getEndParam
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isFullEllipse
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getParamTo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getSweep
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPointAt
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        moveReferencePoint
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        reverse
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        castToShape
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getShapes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue copy
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static REllipseData* getSelf(const QString& fName, QScriptContext* context)
    ;static REllipseData* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    