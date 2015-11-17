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
#ifndef RSHAPESEXPORTER_H
#define RSHAPESEXPORTER_H

#include "RShape.h"
#include "RExporter.h"

/**
 * Exports entities into a list of shapes.
 */
class RShapesExporter : public RExporter {
public:
    RShapesExporter(RExporter& exporter, const QList<QSharedPointer<RShape> >& shapes, double offset);
    virtual void exportLineSegment(const RLine& line, double angle = RNANDOUBLE);

    virtual RLinetypePattern getLinetypePattern() {
        return exporter.getLinetypePattern();
    }
    double getLineTypePatternScale(const RLinetypePattern& p) const {
        return exporter.getLineTypePatternScale(p);
    }

    virtual void exportPainterPaths(const QList<RPainterPath>& paths) {
        exporter.exportPainterPaths(paths);
    }

    virtual void exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos);

    virtual void exportXLine(const RXLine& xLine) {}
    virtual void exportRay(const RRay& ray) {}
    virtual void exportPoint(const RPoint& point) {}
    virtual void exportTriangle(const RTriangle& triangle) {}

    RVector getPointAt(double d, int* index = NULL);
    double getAngleAt(double d);
    int getShapeAt(double d);
    void exportShapesBetween(int i1, const RVector& p1, int i2, const RVector& p2);

private:
    RExporter& exporter;
    QList<QSharedPointer<RShape> > shapes;
    std::vector<double> lengthAt;
};

#endif
