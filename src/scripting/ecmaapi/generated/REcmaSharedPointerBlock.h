// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMASHAREDPOINTERBLOCK_H
        #define RECMASHAREDPOINTERBLOCK_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RBlock.h"
            
            typedef QSharedPointer<RBlock> RBlockPointer;
        

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaSharedPointerBlock {

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
        getType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clone
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isFrozen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFrozen
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isAnonymous
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAnonymous
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setOrigin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getOrigin
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSelectedForPropertyEditing
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RBlock* getSelf(const QString& fName, QScriptContext* context)
    ;static RBlock* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  QScriptValue data
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue isNull
    (QScriptContext *context, QScriptEngine *engine)
    ;};
    #endif
    