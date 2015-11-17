#pragma once



	// ***** AUTOGENERATED CODE, DO NOT EDIT *****
    
        #ifndef RECMASHELLFILEIMPORTERFACTORYADAPTER_H
        #define RECMASHELLFILEIMPORTERFACTORYADAPTER_H

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RFileImporterFactoryAdapter.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class REcmaShellFileImporterFactoryAdapter : public RFileImporterFactoryAdapter {

        public:
      
    // Destructor:
    
            ~REcmaShellFileImporterFactoryAdapter();
        static RFileImporterFactoryAdapter* getSelf(const QString& fName, QScriptContext* context)
    ;static REcmaShellFileImporterFactoryAdapter* getSelfShell(const QString& fName, QScriptContext* context)
    ;
    
    
      QStringList getFilterStrings(
                
            );
        
    
    
      int canImport(
                const QString & fileName, const QString & nameFilter
        = ""
            );
        
    
    
      RFileImporter * instantiate(
                RDocument & document, RMessageHandler * messageHandler
        = NULL, RProgressHandler * progressHandler
        = NULL
            );
        
    
  
        // methods of 1st level base class RFileImporterFactory:
        

    // protected methods (only available for ECMA shell classes) (generated by xsl2xpp.xsl):
	QScriptValue __qtscript_self;
            };
            Q_DECLARE_METATYPE(REcmaShellFileImporterFactoryAdapter*)
        
	#endif
    