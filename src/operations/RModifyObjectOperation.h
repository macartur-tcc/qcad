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

#ifndef RMODIFYOBJECTOPERATION_H_
#define RMODIFYOBJECTOPERATION_H_

#include "operations_global.h"

#include "RAddObjectOperation.h"

/**
 * Implementation of an operation that adds entities.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RModifyObjectOperation: public RAddObjectOperation {
public:
    RModifyObjectOperation(QSharedPointer<RObject> object, bool undoable = true);
    virtual ~RModifyObjectOperation() {}
};

Q_DECLARE_METATYPE(RModifyObjectOperation*);

#endif /* RMODIFYOBJECTOPERATION_H_ */
