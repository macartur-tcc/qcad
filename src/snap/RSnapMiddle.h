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

#ifndef RSNAPMIDDLE_H
#define RSNAPMIDDLE_H

#include "snap_global.h"

#include "RSnapEntityBase.h"

class RMouseEvent;

/**
 * \brief Middle snapper implementation.
 *
 * \scriptable
 *
 * \ingroup snap
 */
class QCADSNAP_EXPORT RSnapMiddle : public RSnapEntityBase {
public:
    virtual ~RSnapMiddle() {}

protected:
    virtual QList<RVector> snapEntity(
        QSharedPointer<REntity> entity,
        const RVector& point,
        const RBox& queryBox,
        RGraphicsView& view);
};

Q_DECLARE_METATYPE(RSnapMiddle*)

#endif
