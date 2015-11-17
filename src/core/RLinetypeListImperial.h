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

#ifndef RLINETYPELISTIMPERIAL_H
#define RLINETYPELISTIMPERIAL_H

#include "core_global.h"

#include "RLinetypeList.h"

/**
 * The global list of imperial linetypes.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RLinetypeListImperial : public RLinetypeList {
public:
    static void init();

    static void uninit() {
        res.uninit();
    }

    static QStringList getNames() {
        return res.getNames();
    }

    static RLinetypePattern* get(const QString& name) {
        return res.get(name);
    }

private:
    static RResourceList<RLinetypePattern> res;
};

Q_DECLARE_METATYPE(RLinetypeListImperial)
Q_DECLARE_METATYPE(RLinetypeListImperial*)

#endif
