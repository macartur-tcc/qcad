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

#ifndef RSCALESELECTIONOPERATION_H
#define RSCALESELECTIONOPERATION_H

#include "operations_global.h"

#include "RDocument.h"
#include "REntity.h"
#include "RExporter.h"
#include "ROperation.h"
#include "RVector.h"


/**
 * Implementation of an operation that scales a selection
 * by a given factor.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RScaleSelectionOperation : public ROperation {
public:
    RScaleSelectionOperation(const RVector& factors, const RVector& referencePoint);
    RScaleSelectionOperation(double factor, const RVector& referencePoint);

    virtual ~RScaleSelectionOperation() { }
    
    virtual RTransaction apply(RDocument& document, bool preview = false) const;

private:
    RVector referencePoint;
    RVector factors;
};

Q_DECLARE_METATYPE(RScaleSelectionOperation*)

#endif
