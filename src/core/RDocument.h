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

#ifndef RDOCUMENT_H
#define RDOCUMENT_H

#include "core_global.h"

#include <QString>
#include <QSharedPointer>

#include "RBlock.h"
#include "RBlockReferenceEntity.h"
#include "RDocumentVariables.h"
#include "REntity.h"
#include "RNonCopyable.h"
#include "RRequireHeap.h"
#include "RSpatialIndex.h"
#include "RTransactionStack.h"
#include "RUcs.h"
#include "RLayer.h"
#include "RLinetype.h"
#include "RView.h"

class RVector;
class RStorage;

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

#define RDEFAULT_QLIST_RS_ENTITYTYPE QList<RS::EntityType>()


/**
 * A graphics document contains and owns entities, layers, user coordinate
 * systems, variables, block definitions, etc.
 *
 * Every document maintains a spatial index for fast entity lookups.
 * Documents also handle transactions through a \ref RTransactionStack.
 * A document is backed by an \ref RStorage implementation to
 * store the document for the duration of the document's lifetime.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RDocument : public RRequireHeap, RNonCopyable {
public:
    RDocument(RStorage& storage, RSpatialIndex& spatialIndex);
    virtual ~RDocument();

    void init();
    void initLinetypes(RTransaction* transaction=NULL);
    QList<QSharedPointer<RObject> > getDefaultLinetypes();

    RStorage& getStorage();
    const RStorage& getStorage() const;
    RSpatialIndex& getSpatialIndex();
    RTransactionStack& getTransactionStack();

    void clear();

    REntity::Id queryClosestXY(
        const RVector& wcsPosition,
        double range,
        bool draft,
        double strictRange = RMAXDOUBLE,
        bool includeLockedLayers = true
    );
    REntity::Id queryClosestXY(
        QSet<REntity::Id>& candidates,
        const RVector& wcsPosition,
        double range,
        bool draft,
        double strictRange = RMAXDOUBLE
    );

    QSet<RObject::Id> queryAllObjects() const;
    QSet<REntity::Id> queryAllVisibleEntities() const;
    QSet<REntity::Id> queryAllEntities(bool undone = false, bool allBlocks = false, RS::EntityType type = RS::EntityAll) const;
    QSet<RUcs::Id> queryAllUcs() const;
    QSet<RLayer::Id> queryAllLayers() const;
    QSet<RBlock::Id> queryAllBlocks() const;
    QSet<RView::Id> queryAllViews() const;
    QSet<RLinetype::Id> queryAllLinetypes() const;

    QSet<REntity::Id> queryLayerEntities(RLayer::Id layerId, bool allBlocks = false) const;
    QSet<REntity::Id> queryBlockEntities(RBlock::Id blockId) const;
    QSet<REntity::Id> queryLayerBlockEntities(RLayer::Id layerId, RBlock::Id blockId) const;
    QSet<REntity::Id> queryChildEntities(REntity::Id parentId, RS::EntityType type = RS::EntityAll) const;
    bool hasChildEntities(REntity::Id parentId) const;
    QSet<REntity::Id> queryBlockReferences(RBlock::Id blockId) const;
    QSet<REntity::Id> queryAllBlockReferences() const;

    QSet<REntity::Id> queryContainedEntities(
        const RBox& box
    );

    QSet<REntity::Id> queryInfiniteEntities();
    QSet<REntity::Id> queryIntersectedEntitiesXY(
            const RBox& box,
            bool checkBoundingBoxOnly=false,
            bool includeLockedLayers=true,
            RBlock::Id blockId = RBlock::INVALID_ID,
            const QList<RS::EntityType>& filter = RDEFAULT_QLIST_RS_ENTITYTYPE
    );

    QMap<REntity::Id, QSet<int> > queryIntersectedShapesXY(
        const RBox& box,
        bool checkBoundingBoxOnly=false,
        bool includeLockedLayers=true,
        RBlock::Id blockId = RBlock::INVALID_ID,
        const QList<RS::EntityType>& filter = RDEFAULT_QLIST_RS_ENTITYTYPE
    );

    QSet<REntity::Id> queryContainedEntitiesXY(
        const RBox& box
    );

    QSet<REntity::Id> querySelectedEntities();
    QSet<RObject::Id> queryPropertyEditorObjects();

    QSharedPointer<RDocumentVariables> queryDocumentVariables() const;
    QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const;
    QSharedPointer<RObject> queryObject(RObject::Id objectId) const;
    QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const;
    QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const;
    QSharedPointer<REntity> queryEntity(REntity::Id entityId) const;
    QSharedPointer<REntity> queryEntityDirect(REntity::Id entityId) const;
    QSharedPointer<RUcs> queryUcs(RUcs::Id ucsId) const;
    QSharedPointer<RUcs> queryUcs(const QString& ucsName) const;
    QSharedPointer<RLayer> queryLayer(RLayer::Id layerId) const;
    QSharedPointer<RLayer> queryLayerDirect(RLayer::Id layerId) const;
    QSharedPointer<RLayer> queryLayer(const QString& layerName) const;
    QSharedPointer<RBlock> queryBlock(RBlock::Id blockId) const;
    QSharedPointer<RBlock> queryBlockDirect(RBlock::Id blockId) const;
    QSharedPointer<RBlock> queryBlock(const QString& blockName) const;
    QSharedPointer<RView> queryView(RView::Id viewId) const;
    QSharedPointer<RView> queryView(const QString& viewName) const;
    QSharedPointer<RLinetype> queryLinetype(RLinetype::Id linetypeId) const;
    QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const;

    int countSelectedEntities() const;

    void clearSelection(
        QSet<REntity::Id>* affectedEntities=NULL
    );

    void selectAllEntites(QSet<REntity::Id>* affectedEntities = NULL);

    void selectEntity(
        REntity::Id entityId,
        bool add=false,
        QSet<REntity::Id>* affectedEntities=NULL
    );
    void deselectEntity(
        REntity::Id entityId,
        QSet<REntity::Id>* affectedEntities=NULL
    );
    void selectEntities(
        const QSet<REntity::Id>& entityId,
        bool add=false,
        QSet<REntity::Id>* affectedEntities=NULL
    );
    bool deselectEntities(
        const QSet<REntity::Id>& entityId,
        QSet<REntity::Id>* affectedEntities=NULL
    );
    bool isSelected(REntity::Id entityId);
    bool isLayerLocked(RLayer::Id layerId) const;
    bool isEntityEditable(REntity::Id entityId) const;
    //bool isEntityLayerLocked(REntity::Id entityId) const;
    bool isLayerFrozen(RLayer::Id layerId) const;
    bool isBlockFrozen(RBlock::Id blockId) const;
    bool isEntityLayerFrozen(REntity::Id entityId) const;

    bool hasSelection() const;

    RBox getBoundingBox(bool ignoreHiddenLayers = true, bool ignoreEmpty = false) const;
    RBox getSelectionBox() const;

    //void addToSpatialIndex(RObject& object, bool isNew = false);
    virtual void rebuildSpatialIndex();
    //void addToSpatialIndex(QSharedPointer<REntity> entity);
    void addToSpatialIndex(QSharedPointer<REntity> entity);

    bool blockContainsReferences(RBlock::Id blockId, RBlock::Id referencedBlockId);

    void removeBlockFromSpatialIndex(RBlock::Id blockId);
    bool addBlockToSpatialIndex(RBlock::Id blockId, RObject::Id ignoreBlockId);
    virtual void removeFromSpatialIndex(QSharedPointer<REntity> entity);
    //virtual void removeFromSpatialIndex2(QSharedPointer<REntity> entity);

    void updateAllEntities();

    QList<RTransaction> undo();
    QList<RTransaction> redo();
    bool isUndoAvailable() const;
    bool isRedoAvailable() const;
    void startTransactionGroup();
    int getTransactionGroup() const;
    void resetTransactionStack();

    void setFileName(const QString& fn);
    QString getFileName() const;

    void setFileVersion(const QString& fv);
    QString getFileVersion() const;

    QSharedPointer<RLayer> queryCurrentLayer();
//    RTransaction setCurrentLayer(RLayer::Id layerId);
//    RTransaction setCurrentLayer(const QString& layerName);
//    void setCurrentLayer(RTransaction& transaction, RLayer::Id layerId);
//    void setCurrentLayer(RTransaction& transaction, const QString& layerName);
    void setCurrentLayer(RLayer::Id layerId, RTransaction* transaction=NULL);
    void setCurrentLayer(const QString& layerName, RTransaction* transaction=NULL);
    RLayer::Id getCurrentLayerId();

    void setCurrentColor(const RColor& color);
    RColor getCurrentColor() const;

    void setCurrentLineweight(RLineweight::Lineweight lw);
    RLineweight::Lineweight getCurrentLineweight() const;

    void setCurrentLinetype(RLinetype::Id ltId);
    void setCurrentLinetype(const QString& name);
    void setCurrentLinetypePattern(const RLinetypePattern& p);
    RLinetype::Id getCurrentLinetypeId() const;
    RLinetypePattern getCurrentLinetypePattern() const;

    QSharedPointer<RBlock> queryCurrentBlock();
    void setCurrentBlock(RBlock::Id blockId);
    void setCurrentBlock(const QString& blockName);
    RBlock::Id getCurrentBlockId() const;

//    void setSelectedBlock(RBlock::Id blockId);
//    void setSelectedBlock(const QString& blockName);
//    RBlock::Id getSelectedBlockId() const;

    QSharedPointer<RView> queryCurrentView();
    void setCurrentView(RView::Id viewId);
    void setCurrentView(const QString& viewName);
    RView::Id getCurrentViewId() const;

    QString getTempBlockName() const;
    QString getBlockName(RBlock::Id blockId) const;
    QSet<QString> getBlockNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    QString getLayerName(RLayer::Id layerId) const;
    QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    QSet<QString> getViewNames() const;

    bool hasLayer(const QString& layerName) const;
    bool hasBlock(const QString& blockName) const;
    bool hasView(const QString& viewName) const;
    bool hasLinetype(const QString& linetypeName) const;

    RLayer::Id getLayerId(const QString& layerName) const;
    RBlock::Id getBlockId(const QString& blockName) const;
    RBlock::Id getModelSpaceBlockId() const;

    RLinetype::Id getLinetypeId(const QString& linetypeName) const;
    RLinetype::Id getLinetypeByLayerId() const {
        return linetypeByLayerId;
    }
    RLinetype::Id getLinetypeByBlockId() const {
        return linetypeByBlockId;
    }
    QString getLinetypeName(RLinetype::Id linetypeId) const;
    QString getLinetypeDescription(RLinetype::Id linetypeId) const;
    QString getLinetypeLabel(RLinetype::Id linetypeId) const;
    QSet<QString> getLinetypeNames() const;
    QList<RLinetypePattern> getLinetypePatterns() const;
    bool isByLayer(RLinetype::Id linetypeId) const;
    bool isByBlock(RLinetype::Id linetypeId) const;

    RLineweight::Lineweight getMaxLineweight() const;

    QStringList getVariables() const;
    void setVariable(const QString& key, const QVariant& value, bool overwrite=true);
    QVariant getVariable(const QString& key, const QVariant& defaultValue = RDEFAULT_QVARIANT, bool useSettings = false) const;
    bool hasVariable(const QString& key) const;

    void setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction = NULL);
    void setKnownVariable(RS::KnownVariable key, const RVector& value, RTransaction* transaction = NULL);
    QVariant getKnownVariable(RS::KnownVariable key, const QVariant& defaultValue = RDEFAULT_QVARIANT) const;

    void setUnit(RS::Unit unit, RTransaction* transaction = NULL);
    //void setUnit(RTransaction& transaction, RS::Unit unit);
    RS::Unit getUnit() const;

    bool isMetric() const;

    void setDimensionFont(const QString& f, RTransaction* transaction = NULL);
    QString getDimensionFont() const;

    void setLinetypeScale(double v, RTransaction* transaction = NULL);
    double getLinetypeScale() const;

    QString formatLinear(double value);
    QString formatAngle(double value);

    RS::LinearFormat getLinearFormat();
    int getLinearPrecision();
    bool showLeadingZeroes();
    bool showTrailingZeroes();
    bool showLeadingZeroesAngle();
    bool showTrailingZeroesAngle();
    RS::AngleFormat getAngleFormat();
    int getAnglePrecision();

    bool isModified() const;
    void setModified(bool m);

    void copyVariablesFrom(const RDocument& other);

    /*
    void copyToDocument(const RVector& reference, RDocument& other,
        bool selectionOnly, bool clear, RTransaction& transaction);
    void copyToDocument(REntity& entity, const RVector& reference,
        RDocument& other, RTransaction& transaction);
    */

    static RDocument& getClipboard();

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, RDocument& d);

    void dump();

protected:
    static RDocument* clipboard;

private:
    QString fileName;
    QString fileVersion;

    RStorage& storage;
    // TODO: map of spatial indices (per block), spatial index template to copy for new blocks:
    RSpatialIndex& spatialIndex;
    RTransactionStack transactionStack;
    RBlock::Id modelSpaceBlockId;
    RLinetype::Id linetypeByLayerId;
    RLinetype::Id linetypeByBlockId;
};

Q_DECLARE_METATYPE(RDocument*)
Q_DECLARE_METATYPE(const RDocument*)

#endif
