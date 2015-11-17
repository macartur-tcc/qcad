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

#ifndef RFONT_H
#define RFONT_H

#include "core_global.h"

#include <QMetaType>
#include <QChar>
#include <QMap>
#include <QPainterPath>
#include <QString>
#include <QStringList>


/**
 * Represents a CXF font.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RFont {
public:
    RFont();
    RFont(const QString& fileName);
    ~RFont();

    bool isValid() const {
        return !fileName.isEmpty();
    }

    /** \return the fileName of this font. */
    QString getFileName() const {
        return fileName;
    }

    /** \return the encoding of this font. */
    QString getEncoding() const {
        return encoding;
    }

    /** \return the alternative names of this font. */
    const QStringList getNames() const {
        return names;
    }

    /** \return the author(s) of this font. */
    const QStringList getAuthors() const {
        return authors;
    }

    /** \return Default letter spacing for this font */
    double getLetterSpacing() const {
        return letterSpacing;
    }

    /** \return Default word spacing for this font */
    double getWordSpacing() const {
        return wordSpacing;
    }

    /** \return Default line spacing factor for this font */
    double getLineSpacingFactor() const {
        return lineSpacingFactor;
    }

    bool load();

    /**
     * \return True if this font is already loaded.
     */
    bool isLoaded() const {
        return loaded;
    }

    /**
     * \nonscriptable
     */
    QMap<QChar, QPainterPath> getGlyphMap() const {
        return glyphMap;
    }

    /**
     * \nonscriptable
     */
    QPainterPath getGlyph(const QChar& ch, bool draft = false) const;

    /**
     * \nonscriptable
     */
    QPainterPath getShape(const QString& name) const;

    /**
     * \nonscriptable
     */
    QString getShapeName(const QChar& ch) const;

    //int countGlyphs() {
    //    return glyphMap.count();
    //}

    //QPainterPath glyphAt(int i) {
    //    return glyphMap.values()
    //}

private:
    //! list of glyphs as painter paths (letters)
    QMap<QChar, QPainterPath> glyphMap;
    QMap<QString, QPainterPath> shapeMap;
    QMap<QChar, QString> numNameMap;
    QMap<QChar, QPainterPath> glyphDraftMap;

    //! Font file name
    QString fileName;

    //! Font encoding (see docu for QTextCodec)
    QString encoding;

    //! Font names
    QStringList names;

    //! Authors
    QStringList authors;

    //! Is this font currently loaded into memory?
    bool loaded;

    //! Default letter spacing for this font
    double letterSpacing;

    //! Default word spacing for this font
    double wordSpacing;

    //! Default line spacing factor for this font
    double lineSpacingFactor;
};

Q_DECLARE_METATYPE(RFont)
Q_DECLARE_METATYPE(RFont*)

#endif
