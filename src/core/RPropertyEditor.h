#pragma once
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

#ifndef RPROPERTYEDITOR_H
#define RPROPERTYEDITOR_H

#include "core_global.h"

#include <QCoreApplication>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

#include "RDocument.h"
#include "RObject.h"
#include "RPropertyListener.h"


/**
 * Base class for property editors. Provides basic functionality that
 * is common to any property editor implementation.
 *
 * \ingroup core
 * \scriptable
 * \generateScriptShell
 */
class QCADCORE_EXPORT RPropertyEditor: public RPropertyListener {

    Q_DECLARE_TR_FUNCTIONS(RPropertyEditor)

public:
    RPropertyEditor();
    virtual ~RPropertyEditor();

    // from RPropertyListener interface:
    virtual void updateFromDocument(RDocument* document, bool onlyChanges,
            RS::EntityType entityTypeFilter = RS::EntityAll, bool manual = false);
    virtual void updateFromObject(RObject* object, RDocument* document = NULL);
    virtual void clearEditor();
    void propertyChanged(RPropertyTypeId propertyTypeId, QVariant propertyValue,
                         RS::EntityType entityTypeFilter = RS::EntityAll,
                         QVariant::Type typeHint = QVariant::Invalid);
    void listPropertyChanged(RPropertyTypeId propertyTypeId,
                         int index, QVariant propertyValue,
                         RS::EntityType entityTypeFilter = RS::EntityAll);

    QStringList getGroupTitles();
    QStringList getPropertyTitles(const QString& group);
    QVariant getPropertyValue(const RPropertyTypeId& propertyTypeId);
    QVariant getPropertyValue(const QString& group, const QString& title);
    RPropertyAttributes getPropertyAttributes(const RPropertyTypeId& propertyTypeId);
    RPropertyAttributes getPropertyAttributes(const QString& group, const QString& title);
    QList<RS::EntityType> getTypes();
    int getTypeCount(RS::EntityType type);

    static bool checkType(RS::EntityType type, RS::EntityType filter);

protected:
    virtual void updateEditor(RObject& object, bool doUpdateGui,
            RDocument* document = NULL);

    /**
     * Updates the user interface of this property editor. This is the
     * only part of the property editor that depends on the user interface
     * and GUI toolkit that is available.
     */
    virtual void updateGui(
        bool onlyChanges = false,
        RS::EntityType entityTypeFilter = RS::EntityAll) {

        Q_UNUSED(onlyChanges)
        Q_UNUSED(entityTypeFilter)
    }

    void updateProperty(const RPropertyTypeId& propertyTypeId, RObject& object,
            RDocument* document);
    void removeAllButThese(const QMultiMap<QString, QString>& propertyTitles, bool customOnly=false);

protected:
    //! key / value / attributes
    typedef QMap<QString, QPair<QVariant, RPropertyAttributes> > RPropertyMap;
    //! group key / key,value,attributes
    typedef QMap<QString, RPropertyMap> RPropertyGroupMap;

    QStringList groupOrder;
    QMap<QString, QStringList> propertyOrder;
    RPropertyGroupMap combinedProperties;
    QMap<RS::EntityType, int> combinedTypes;
    bool guiUpToDate;
    bool updatesDisabled;
};

Q_DECLARE_METATYPE(RPropertyEditor*)

#endif
