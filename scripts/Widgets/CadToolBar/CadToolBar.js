/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("CadToolBarPanel.js");


/**
 * CAD tool bar with configurable number of columns of tool buttons.
 *
 * \param parent A QToolBar
 */
function CadToolBar(parent) {
    QWidget.call(this, parent);

    var buttonSize = RSettings.getIntValue("CadToolBar/IconSize", 32) * 1.25;
    
    this.includeBasePath = includeBasePath;

    // widget inside toolbar is needed to allow two rows of
    // tool buttons in a layout:
    this.objectName="CadToolBar";
    this.minimumWidth = buttonSize;
    this.minimumHeight = buttonSize;
    var stackedLayout = new QStackedLayout();
    stackedLayout.objectName = "StackedLayout";
    stackedLayout.setContentsMargins(0,0,0,0);
    this.setLayout(stackedLayout);

    RMainWindowQt.getMainWindow().escape.connect(CadToolBar, "back");
}

CadToolBar.prototype = new QWidget();

CadToolBar.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("CAD Toolbar")];
};

CadToolBar.applyPreferences = function(doc) {
    if (!isNull(doc)) {
        // document settings: nothing to do
        return;
    }

    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    var cadToolBar = appWin.findChild("CadToolBar");
    CadToolBar.prototype.updateIconSize.call(cadToolBar);
};

CadToolBar.prototype.contextMenuEvent = function(event) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    var panelName = CadToolBar.getCurrentPanelName();
    if (panelName!=="MainToolsPanel") {
        CadToolBar.showPanel("MainToolsPanel");
    }
    else {
        var tb = appWin.findChild("CadQToolBar");

        if (tb.floating && !RSettings.isQt(5)) {
            var menu = new QMenu(this);
            menu.objectName = "ContextMenu";
            // force tool bar to be vertical:
            var action = menu.addAction(qsTr("Vertical/Horizontal"));
            action.triggered.connect(function(checked) {
                var verticalWhenFloating = RSettings.getBoolValue("CadToolBar/VerticalWhenFloating", false);
                RSettings.setValue("CadToolBar/VerticalWhenFloating", !verticalWhenFloating);

                var cadToolBar = appWin.findChild("CadToolBar");
                CadToolBar.prototype.updateIconSize.call(cadToolBar);
            });
            menu.exec(QCursor.pos());
        }
    }
};

CadToolBar.back = function() {
    var panel = CadToolBar.getCurrentPanel();
    if (isNull(panel)) {
        return;
    }

    // no back for main tools panel:
    if (panel.objectName==="MainToolsPanel") {
        return;
    }

    CadToolBar.showPanel(panel.backMenuName, true);
};

CadToolBar.getPanel = function(title, name, hasBackButton) {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }
    var cadToolBar = appWin.findChild("CadToolBar");
    if (isNull(cadToolBar)) {
        return undefined;
    }

    var stackedLayout = cadToolBar.layout();

    var panel = cadToolBar.findChild(name);
    if (!isNull(panel)) {
        return panel;
    }

    panel = new CadToolBarPanel(cadToolBar, hasBackButton);
    panel.objectName = name;
    stackedLayout.addWidget(panel);
    return panel;
};

CadToolBar.showPanel = function(name, isBack) {
    if (isNull(isBack)) {
        isBack = false;
    }

    if (isNull(name)) {
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    if (isNull(appWin)) {
        return;
    }

    var cadToolBar = appWin.findChild("CadToolBar");
    if (isNull(cadToolBar)) {
        return;
    }

    var backMenuName = CadToolBar.getCurrentPanelName();

    var stackedLayout = cadToolBar.layout();
    var panel = cadToolBar.findChild(name);
    if (isNull(panel)) {
        qWarning("CadToolBar: panel does not exist: ", name);
        return;
    }

    for (var i=0; i<stackedLayout.count(); ++i) {
        var w = stackedLayout.widget(i);
        if (!isNull(w)) {
            w.minimumHeight = 0;
            w.minimumWidth = 0;
        }
    }
    stackedLayout.setCurrentWidget(panel);

    if (!isBack && backMenuName!==panel.objectName && backMenuName!=="SnapToolsPanel") {
        CadToolBarPanel.setBackMenuName(panel, backMenuName);
    }
};

CadToolBar.getCurrentPanel = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    var cadToolBar = appWin.findChild("CadToolBar");
    if (isNull(cadToolBar)) {
        return undefined;
    }

    var stackedLayout = cadToolBar.layout();

    if (stackedLayout.currentIndex<0 || stackedLayout.currentIndex >= stackedLayout.count()) {
        return undefined;
    }

    return stackedLayout.widget(stackedLayout.currentIndex);
};

CadToolBar.getCurrentPanelName = function() {
    var w = CadToolBar.getCurrentPanel();
    if (isNull(w)) {
        return "";
    }

    return w.objectName;
};

CadToolBar.prototype.updateIconSize = function() {
    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);
    var buttonSize = iconSize * 1.25;

    //qDebug("conf iconSize:", iconSize);

    var toolBar = this.parentWidget();
    //qDebug("toolBar:", toolBar.objectName);
    //qDebug("icon size before:", toolBar.iconSize);
    //toolBar.iconSize = new QSize(columns*iconSize, columns*iconSize);
    //toolBar.iconSize = new QSize(iconSize, iconSize);
    //this.minimumWidth = buttonSize;
    //this.minimumHeight = buttonSize;
    //qDebug("icon size after:", toolBar.iconSize);

    //CadToolBar.setIconSize(this, iconSize);

    // workaround for QToolBar bug (not resizing when layout changes):
    if (toolBar.floating) {
        toolBar.resize(toolBar.sizeHint.width(), toolBar.sizeHint.height());
    }

//    toolBar.update();
};

//CadToolBar.setIconSize = function(widget, iconSize) {
//    if (isNull(widget)) {
//        return;
//    }
//    if (!isQWidget(widget) || !isFunction(widget.children)) {
//        return;
//    }

//    var children = widget.children();
//    for (var i = 0; i < children.length; ++i) {
//        var c = children[i];

//        if (!c || isDeleted(c)) {
//            break;
//        }

//        if (isOfType(c, QToolButton)) {
//            c.iconSize = iconSize;
//            continue;
//        }

//        CadToolBar.setIconSize(c);
//    }
//};

CadToolBar.init = function() {
    var appWin = EAction.getMainWindow();

    var toolBar = appWin.findChild("CadQToolBar");
    if (isNull(toolBar)) {
        return;
    }

    if (RSettings.isQt(5)) {
        // tool bar buttons under Qt 5 have no border:
        toolBar.styleSheet =
              "QToolButton {"
            + "  border: 1px solid #969696;"
            //+ "  border-radius: 6px; "
            + "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f8f8f8, stop: 0.2 #e3e3e3, stop: 1 #f9f9f9);"
            + "}"
            + "QToolButton:checked {"
            + "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b7b7b7, stop: 0.8 #cfcfcf, stop: 1 #d1d1d1);"
            + "}"
            + "QToolButton:pressed {"
            + "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #a4a4a4, stop: 0.8 #b3b3b3, stop: 1 #b5b5b5);"
            + "}";
    }

    if (RSettings.getStringValue("CadToolBar/Location", "left")==="top") {
        appWin.addToolBarBreak();
        appWin.addToolBar(Qt.TopToolBarArea, toolBar);
    }
    else {
        appWin.addToolBar(Qt.LeftToolBarArea, toolBar);
    }
};

CadToolBar.postInit = function() {
    var appWin = EAction.getMainWindow();
    if (isNull(appWin)) {
        return;
    }
    var toolBar = appWin.findChild("CadQToolBar");
    if (isNull(toolBar)) {
        return;
    }

    RSettings.setValue("CadToolBar/VerticalWhenFloating", toolBar.size.width() < toolBar.size.height());
};
