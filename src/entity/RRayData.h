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

#ifndef RRAYDATA_H
#define RRAYDATA_H

#include "entity_global.h"

#include "REntityData.h"
#include "RRay.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a ray entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RRayData: public REntityData, protected RRay {

    friend class RRayEntity;

protected:
    RRayData(RDocument* document, const RRayData& data);

public:
    RRayData();
    RRayData(const RRay& ray);
    RRayData(const RVector& basePoint, const RVector& dir);

    RRay getRay() {
        return *this;
    }

    RVector getBasePoint() const {
        return RRay::getBasePoint();
    }
    RVector getDirectionVector() const {
        return RRay::getDirectionVector();
    }
    double getAngle() const {
        return RRay::getAngle();
    }

    bool hasFixedAngle() const {
        return fixedAngle;
    }

    void setFixedAngle(bool on) {
        fixedAngle = on;
    }

    bool reverse() {
        return RRay::reverse();
    }

    RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint) {
        return RRay::getTrimEnd(coord, trimPoint);
    }
    void trimStartPoint(const RVector& p) {
        return RRay::trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return RRay::trimEndPoint(p);
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return RRay::getSideOfPoint(point);
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint);

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false) const {
        Q_UNUSED(queryBox)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RRay(*this));
    }

private:
    bool fixedAngle;
};

Q_DECLARE_METATYPE(RRayData)
Q_DECLARE_METATYPE(RRayData*)
Q_DECLARE_METATYPE(const RRayData*)
Q_DECLARE_METATYPE(QSharedPointer<RRayData>)

#endif
