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

#ifndef REXPORTLISTENERADAPTER_H_
#define REXPORTLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RExportListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RExportListenerAdapter: public QObject, public RExportListener {
Q_OBJECT

public:
    virtual ~RExportListenerAdapter() { }

    virtual void preExportEvent(RDocumentInterface* documentInterface) {
        emit preExport(documentInterface);
    }
    virtual void postExportEvent(RDocumentInterface* documentInterface) {
        emit postExport(documentInterface);
    }

signals:
    void preExport(RDocumentInterface* documentInterface);
    void postExport(RDocumentInterface* documentInterface);
};

Q_DECLARE_METATYPE(RExportListenerAdapter*)

#endif
