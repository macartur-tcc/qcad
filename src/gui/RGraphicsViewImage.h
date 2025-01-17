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

#ifndef RGRAPHICSVIEWIMAGE_H
#define RGRAPHICSVIEWIMAGE_H

#include "gui_global.h"

#include <QtCore>
#include <QPinchGesture>

#include "RGraphicsView.h"
#include "RPainterPath.h"

class RAction;
class RDocument;
class RDocumentInterface;
class RGraphicsSceneQt;
class RLine;
class RSnap;
class RSnapRestriction;



/**
 * \brief QImage based 2d graphics view.
 *
 * This graphics view displays a rectangular area of a
 * RGraphicsSceneQt.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RGraphicsViewImage : public RGraphicsView {

public:
    RGraphicsViewImage();
    virtual ~RGraphicsViewImage();

    // TODO: these methods are not found in RGraphicsViewQt, due to the
    // multiple inheritance of RGraphicsViewQt (QWidget and RGraphicsViewImage)
    // unless they are re-declared here again:
    void setViewportNumber(int n) {
        RGraphicsView::setViewportNumber(n);
    }

    int getViewportNumber() const {
        return RGraphicsView::getViewportNumber();
    }

    void setNavigationAction(RAction* action) {
        RGraphicsView::setNavigationAction(action);
    }

    RBox getBox() const {
        return RGraphicsView::getBox();
    }

    void autoZoom(int margin = RDEFAULT_MIN1, bool ignoreEmpty=false) {
        RGraphicsView::autoZoom(margin, ignoreEmpty);
    }

    void zoomTo(const RBox &window, int margin = 0) {
        RGraphicsView::zoomTo(window, margin);
    }

    void zoom(const RVector& center, double factor) {
        RGraphicsView::zoom(center, factor);
    }

    void centerToBox(const RBox& box) {
        RGraphicsView::centerToBox(box);
    }

    void centerToPoint(const RVector& point) {
        RGraphicsView::centerToPoint(point);
    }

    void setGrid(RGrid* grid) {
        RGraphicsView::setGrid(grid);
    }

    RGrid* getGrid() {
        return RGraphicsView::getGrid();
    }

    double getFactor(bool includeStepFactor=true) const {
        return RGraphicsView::getFactor(includeStepFactor);
    }

    void setFactor(double f, bool regen=true) {
        RGraphicsView::setFactor(f, regen);
    }

    RVector getOffset(bool includeStepOffset=true) const {
        return RGraphicsView::getOffset(includeStepOffset);
    }

    void setOffset(const RVector& offset, bool regen=true) {
        RGraphicsView::setOffset(offset, regen);
    }

    QColor getBackgroundColor() {
        return RGraphicsView::getBackgroundColor();
    }

    void setMargin(int m) {
        RGraphicsView::setMargin(m);
    }

    void setColorMode(RGraphicsView::ColorMode cm) {
        RGraphicsView::setColorMode(cm);
    }

    void setHairlineMode(bool on) {
        RGraphicsView::setHairlineMode(on);
    }

    bool getHairlineMode() {
        return RGraphicsView::getHairlineMode();
    }

    void setAntialiasing(bool on) {
        RGraphicsView::setAntialiasing(on);
    }

    bool getAntialiasing() const {
        return RGraphicsView::getAntialiasing();
    }

    RGraphicsScene* getScene() {
        return RGraphicsView::getScene();
    }

    RDocument* getDocument() {
        return RGraphicsView::getDocument();
    }

    RDocumentInterface* getDocumentInterface() {
        return RGraphicsView::getDocumentInterface();
    }

    void setPrinting(bool on) {
        RGraphicsView::setPrinting(on);
    }

    bool isPrinting() const {
        return RGraphicsView::isPrinting();
    }

    void setPrintPreview(bool on) {
        RGraphicsView::setPrintPreview(on);
    }

    bool isPrintPreview() const {
        return RGraphicsView::isPrintPreview();
    }

    void setPrintPointSize(const RVector& s) {
        RGraphicsView::setPrintPointSize(s);
    }

    virtual void simulateMouseMoveEvent() {
        RGraphicsView::simulateMouseMoveEvent();
    }

    void setTextHeightThresholdOverride(int v) {
        RGraphicsView::setTextHeightThresholdOverride(v);
    }

    int getTextHeightThresholdOverride() const {
        return RGraphicsView::getTextHeightThresholdOverride();
    }

    bool isGridVisible() const {
        return RGraphicsView::isGridVisible();
    }

    void setGridVisible(bool on) {
        RGraphicsView::setGridVisible(on);
    }
    
    virtual void setScene(RGraphicsSceneQt* scene, bool regen=true);

    virtual void setBackgroundColor(const QColor& col);

    virtual void regenerate(bool force=false);
    virtual void repaintView();
    virtual void updateImage();

    virtual void giveFocus() {
        return;
    }

    virtual bool hasFocus() {
        return true;
    }

    virtual void removeFocus() {
        return;
    }

    void saveViewport();
    void restoreViewport();

    virtual RVector mapFromView(const RVector& v, double z=0.0) const;
    virtual RVector mapToView(const RVector& v) const;
    virtual double mapDistanceFromView(double d) const;
    virtual double mapDistanceToView(double d) const;
    
    virtual int getWidth() const;
    virtual int getHeight() const;
    void resizeImage(int w, int h);
    
    virtual void paintGridPoint(const RVector& ucsPosition);
    virtual void paintGridLine(const RLine& ucsPosition);
    //virtual void paintCursorLine(const RLine& ucsPosition);

    void setPaintOrigin(bool val);

    void setPanOptimization(bool on);
    bool getPanOptimization();

    virtual void paintEntities(QPainter* painter, const RBox& queryBox);
    virtual void paintEntity(QPainter* painter, REntity::Id id);

    QImage getBuffer() const;
    QTransform getTransform() const;

    virtual void emitUpdateSnapInfo(RSnap* snap, RSnapRestriction* restriction) {
        Q_UNUSED(snap)
        Q_UNUSED(restriction)
    }
    virtual void emitUpdateTextLabel(const RTextLabel& textLabel) {
        Q_UNUSED(textLabel)
    }
    virtual void emitDecorateBackground(QPainter* painter) { Q_UNUSED(painter) }
    virtual void emitDecorateForeground(QPainter* painter) { Q_UNUSED(painter) }

    void clearBackground();
    void addToBackground(const RPainterPath& path);
    void setBackgroundTransform(double bgFactor, const RVector& bgOffset);

    void setColorCorrectionOverride(bool on) {
        colorCorrectionOverride = on;
    }

    bool getColorCorrectionOverride() const {
        return colorCorrectionOverride;
    }

    void setPaintOffset(const RVector& offset) {
        paintOffset = offset;
    }

    RVector getPaintOffset() const {
        return paintOffset;
    }

protected:
    double getPointSize(double pSize);
    virtual void drawDot(QPainter* painter, QPointF pt);
    virtual void drawPlus(QPainter* painter, QPointF pt, double pSize);
    virtual void drawEx(QPainter* painter, QPointF pt, double pSize);
    virtual void drawVBar(QPainter* painter, QPointF pt, double pSize);
    virtual void drawCircle(QPainter* painter, QPointF pt, double pSize);
    virtual void drawSquare(QPainter* painter, QPointF pt, double pSize);

    virtual void paintImage(QPainter* painter, RImageData& image);
    virtual void paintOrigin(QPaintDevice& device);
    virtual void paintReferencePoint(QPainter& painter, const RVector& pos, bool highlight);
    virtual void paintErase(QPaintDevice& device, const QRect& rect = QRect());
    virtual void paintGrid(QPaintDevice& device, const QRect& rect = QRect());
    virtual void paintMetaGrid(QPaintDevice& device, const QRect& rect = QRect());
    virtual void paintCursor(QPaintDevice& device);
    virtual void paintRelativeZero(QPaintDevice& device);
    virtual void paintDocument(const QRect& rect = QRect());
    virtual void paintBackground(QPainter* painter, const QRect& rect = QRect());

    /**
     * \nonscriptable
     */
    QPainter* initPainter(QPaintDevice& device, bool erase, bool screen = false, const QRect& rect = QRect());

    void invalidate(bool force=false);
    void updateGraphicsBuffer();
    void updateTransformation() const;

protected:
    QImage graphicsBuffer;
    QImage graphicsBufferWithPreview;

protected:
    bool panOptimization;
    QMutex mutexSi;

    RGraphicsSceneQt* sceneQt;
    double currentScale;
    QSize lastSize;
    RVector lastOffset;
    double lastFactor;
    bool graphicsBufferNeedsUpdate;
    mutable QTransform transform;
    QTransform previousView;

    QPainter* gridPainter;
    bool doPaintOrigin;

    bool isSelected;
    QSet<RObject::Id> selectedIds;
    int bgColorLightness;

    bool colorCorrectionOverride;
    bool colorCorrection;
    int colorThreshold;

//    int textHeightThresholdOverride;
//    int textHeightThreshold;

    double drawingScale;

    QList<RPainterPath> backgroundDecoration;
    //QTransform backgroundTransform;
    double backgroundFactor;
    RVector backgroundOffset;
    RBox clipBox;
    RVector paintOffset;
};

Q_DECLARE_METATYPE(RGraphicsViewImage*)

#endif
