#pragma once



	// ***** AUTOGENERATED CODE, DO NOT EDIT *****
    
        #ifndef RECMASHELLLISTVIEW_H
        #define RECMASHELLLISTVIEW_H

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RListView.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class REcmaShellListView : public RListView {

        public:
      
    // Destructor:
    
            ~REcmaShellListView();
        static RListView* getSelf(const QString& fName, QScriptContext* context)
    ;static REcmaShellListView* getSelfShell(const QString& fName, QScriptContext* context)
    ;
    
    
    // Constructors:
    
      REcmaShellListView(
                QWidget * parent
        = 0
            );
        
    
    
      void contextMenuEvent(
                QContextMenuEvent * e
            );
        
    
    
      void mousePressEvent(
                QMouseEvent * e
            );
        
    
    
      void mouseReleaseEvent(
                QMouseEvent * e
            );
        
    
    
      void mouseMoveEvent(
                QMouseEvent * e
            );
        
    
    
      void dragEnterEvent(
                QDragEnterEvent * e
            );
        
    
    
      void dragMoveEvent(
                QDragMoveEvent * e
            );
        
    
    
      void dropEvent(
                QDropEvent * e
            );
        
    
    
      void startDrag(
                Qt::DropActions supportedActions
            );
        
    
    
      void selectionChanged(
                const QItemSelection & selected, const QItemSelection & deselected
            );
        
    
    
      void currentChanged(
                const QModelIndex & current, const QModelIndex & previous
            );
        
    
  

    // protected methods (only available for ECMA shell classes) (generated by xsl2xpp.xsl):
	static  QScriptValue
        contextMenuEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mousePressEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mouseReleaseEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mouseMoveEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        dragEnterEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        dragMoveEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        dropEvent
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        startDrag
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        selectionChanged
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        currentChanged
        (QScriptContext* context, QScriptEngine* engine) 
        ;QScriptValue __qtscript_self;
            };
            Q_DECLARE_METATYPE(REcmaShellListView*)
        
	#endif
    