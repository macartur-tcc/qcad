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
#include "RBlockReferenceEntity.h"
#include "RExporter.h"
#include "RSettings.h"
#include "RStorage.h"

RPropertyTypeId RBlockReferenceEntity::PropertyCustom;
RPropertyTypeId RBlockReferenceEntity::PropertyHandle;
RPropertyTypeId RBlockReferenceEntity::PropertyProtected;
RPropertyTypeId RBlockReferenceEntity::PropertyType;
RPropertyTypeId RBlockReferenceEntity::PropertyBlock;
RPropertyTypeId RBlockReferenceEntity::PropertyLayer;
RPropertyTypeId RBlockReferenceEntity::PropertyLinetype;
RPropertyTypeId RBlockReferenceEntity::PropertyLinetypeScale;
RPropertyTypeId RBlockReferenceEntity::PropertyLineweight;
RPropertyTypeId RBlockReferenceEntity::PropertyColor;
RPropertyTypeId RBlockReferenceEntity::PropertyDisplayedColor;
RPropertyTypeId RBlockReferenceEntity::PropertyDrawOrder;

RPropertyTypeId RBlockReferenceEntity::PropertyReferencedBlock;
RPropertyTypeId RBlockReferenceEntity::PropertyPositionX;
RPropertyTypeId RBlockReferenceEntity::PropertyPositionY;
RPropertyTypeId RBlockReferenceEntity::PropertyPositionZ;
RPropertyTypeId RBlockReferenceEntity::PropertyScaleX;
RPropertyTypeId RBlockReferenceEntity::PropertyScaleY;
RPropertyTypeId RBlockReferenceEntity::PropertyScaleZ;
RPropertyTypeId RBlockReferenceEntity::PropertyRotation;
RPropertyTypeId RBlockReferenceEntity::PropertyColumnCount;
RPropertyTypeId RBlockReferenceEntity::PropertyRowCount;
RPropertyTypeId RBlockReferenceEntity::PropertyColumnSpacing;
RPropertyTypeId RBlockReferenceEntity::PropertyRowSpacing;


RBlockReferenceEntity::RBlockReferenceEntity(RDocument* document,
    const RBlockReferenceData& data, RObject::Id objectId) :
    REntity(document, objectId), data(document, data),
    recursionDepth(0) {
//  if (data.getDocument() == NULL) {
//      return;
//  }
//  RBlock::Id id = &this->data.blockId;
//  while (data.getDocument()->getBlockName(id) != "*Model_Space") {
//      QSharedPointer<RBlock> block = data.getDocument()->queryBlock(id);
//      if (block.isNull()) {
//          break;Y
//      }
//      id = block->getId();
//  }
    RDebug::incCounter("RBlockReferenceEntity");
}

RBlockReferenceEntity::RBlockReferenceEntity(const RBlockReferenceEntity& other) : REntity(other) {
    RDebug::incCounter("RBlockReferenceEntity");
    data = other.data;
}

RBlockReferenceEntity::~RBlockReferenceEntity() {
    RDebug::decCounter("RBlockReferenceEntity");
}

void RBlockReferenceEntity::init() {
    RBlockReferenceEntity::PropertyCustom.generateId(typeid(RBlockReferenceEntity), RObject::PropertyCustom);
    RBlockReferenceEntity::PropertyHandle.generateId(typeid(RBlockReferenceEntity), RObject::PropertyHandle);
    RBlockReferenceEntity::PropertyProtected.generateId(typeid(RBlockReferenceEntity), RObject::PropertyProtected);
    RBlockReferenceEntity::PropertyType.generateId(typeid(RBlockReferenceEntity), REntity::PropertyType);
    RBlockReferenceEntity::PropertyBlock.generateId(typeid(RBlockReferenceEntity), REntity::PropertyBlock);
    RBlockReferenceEntity::PropertyLayer.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLayer);
    RBlockReferenceEntity::PropertyLinetype.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLinetype);
    RBlockReferenceEntity::PropertyLinetypeScale.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLinetypeScale);
    RBlockReferenceEntity::PropertyLineweight.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLineweight);
    RBlockReferenceEntity::PropertyColor.generateId(typeid(RBlockReferenceEntity), REntity::PropertyColor);
    RBlockReferenceEntity::PropertyDisplayedColor.generateId(typeid(RBlockReferenceEntity), REntity::PropertyDisplayedColor);
    RBlockReferenceEntity::PropertyDrawOrder.generateId(typeid(RBlockReferenceEntity), REntity::PropertyDrawOrder);

    RBlockReferenceEntity::PropertyReferencedBlock.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Block"));
    RBlockReferenceEntity::PropertyPositionX.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RBlockReferenceEntity::PropertyPositionY.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RBlockReferenceEntity::PropertyPositionZ.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RBlockReferenceEntity::PropertyScaleX.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Scale"), QT_TRANSLATE_NOOP("REntity", "X"));
    RBlockReferenceEntity::PropertyScaleY.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Scale"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RBlockReferenceEntity::PropertyScaleZ.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Scale"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RBlockReferenceEntity::PropertyRotation.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
    RBlockReferenceEntity::PropertyColumnCount.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Columns"));
    RBlockReferenceEntity::PropertyRowCount.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Rows"));
    RBlockReferenceEntity::PropertyColumnSpacing.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Column Spacing"));
    RBlockReferenceEntity::PropertyRowSpacing.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Row Spacing"));
}

QSet<RPropertyTypeId> RBlockReferenceEntity::getPropertyTypeIds() const {
    QSet<RPropertyTypeId> ret;

    // TODO: move to RObject?
    // add attribute tag / values as properties of the block reference:
    const RDocument* doc = getDocument();
    if (doc!=NULL) {
        QSet<REntity::Id> childIds = doc->queryChildEntities(getId(), RS::EntityAttribute);
        QSet<REntity::Id>::iterator it;
        for (it=childIds.begin(); it!=childIds.end(); it++) {
            REntity::Id childId = *it;
            QSharedPointer<REntity> child = doc->queryEntityDirect(childId);
            if (child.isNull()) {
                continue;
            }

            QSet<RPropertyTypeId> childProperties = child->getPropertyTypeIds();
            QSet<RPropertyTypeId>::iterator it2;
            for (it2=childProperties.begin(); it2!=childProperties.end(); it2++) {
                RPropertyTypeId pid = *it2;
                QPair<QVariant, RPropertyAttributes> p = child->getProperty(pid);
                if (p.second.isVisibleToParent()) {
                    pid.setId(RPropertyTypeId::INVALID_ID);
                    ret.insert(pid);
                    //qDebug() << pid.getCustomPropertyTitle() << " / " << pid.getCustomPropertyName();
                    //qDebug() << p.first.toString();
                }
            }
        }
    }

    ret.unite(REntity::getPropertyTypeIds());
    return ret;
}

bool RBlockReferenceEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

//    if (propertyTypeId==PropertyPositionX) {
//        double d = value - data.position.x;
//        RObject::setMember(data.position.x, value);

//        const RDocument* doc = getDocument();
//        if (doc!=NULL) {
//            QSet<REntity::Id> childIds = doc->queryChildEntities(getId(), RS::EntityAttribute);
//            QSet<REntity::Id>::iterator it;
//            for (it=childIds.begin(); it!=childIds.end(); it++) {
//                REntity::Id childId = *it;
//                QSharedPointer<REntity> child = doc->queryEntity(childId);
//                if (child.isNull()) {
//                    continue;
//                }

//                QSet<RPropertyTypeId> childProperties = child->getPropertyTypeIds();
//                QSet<RPropertyTypeId>::iterator it2;
//                for (it2=childProperties.begin(); it2!=childProperties.end(); it2++) {
//                    RPropertyTypeId pid = *it2;
//                    QPair<QVariant, RPropertyAttributes> p = child->getProperty(pid);
//                    if (p.second.isVisibleToParent() && pid.getCustomPropertyName()==tag) {
//                        //ret.insert(RPropertyTypeId(QT_TRANSLATE_NOOP("REntity", "Attributes"), p.first.toString()));
//                        //return qMakePair(QVariant(p.first), RPropertyAttributes());
//                        child->setProperty(pid, value.toString(), transaction);
//                        transaction->addObject(child);
//                    }
//                }
//            }
//        }
//    }

    ret = ret || RObject::setMember(data.position.x, value, PropertyPositionX == propertyTypeId);
    ret = ret || RObject::setMember(data.position.y, value, PropertyPositionY == propertyTypeId);
    ret = ret || RObject::setMember(data.position.z, value, PropertyPositionZ == propertyTypeId);

    ret = ret || RObject::setMember(data.scaleFactors.x, value, PropertyScaleX == propertyTypeId && fabs(value.toDouble())>RS::PointTolerance);
    ret = ret || RObject::setMember(data.scaleFactors.y, value, PropertyScaleY == propertyTypeId && fabs(value.toDouble())>RS::PointTolerance);
    ret = ret || RObject::setMember(data.scaleFactors.z, value, PropertyScaleZ == propertyTypeId && fabs(value.toDouble())>RS::PointTolerance);

    ret = ret || RObject::setMember(data.rotation, value, PropertyRotation == propertyTypeId);

    ret = ret || RObject::setMember(data.columnCount, value, PropertyColumnCount == propertyTypeId);
    ret = ret || RObject::setMember(data.rowCount, value, PropertyRowCount == propertyTypeId);

    ret = ret || RObject::setMember(data.columnSpacing, value, PropertyColumnSpacing == propertyTypeId);
    ret = ret || RObject::setMember(data.rowSpacing, value, PropertyRowSpacing == propertyTypeId);

    if (propertyTypeId == PropertyReferencedBlock) {
        if (value.type() == QVariant::Int ||
            value.type() == QVariant::LongLong) {

            ret = ret || RObject::setMember(
                getData().referencedBlockId, value.toInt(), true);
        } else if (value.type() == QVariant::String) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                ret = ret || RObject::setMember(getData().referencedBlockId,
                        document->getBlockId(value.toString()), true);
            }
        }
    }

    // allow editing of attributes in the context of a block reference:
    if (transaction && propertyTypeId.isCustom()) {
        if (propertyTypeId.getCustomPropertyTitle()=="Attributes") {
            QString tag = propertyTypeId.getCustomPropertyName();

            const RDocument* doc = getDocument();
            if (doc!=NULL) {
                QSet<REntity::Id> childIds = doc->queryChildEntities(getId(), RS::EntityAttribute);
                QSet<REntity::Id>::iterator it;
                for (it=childIds.begin(); it!=childIds.end(); it++) {
                    REntity::Id childId = *it;
                    QSharedPointer<REntity> child = doc->queryEntity(childId);
                    if (child.isNull()) {
                        continue;
                    }

                    QSet<RPropertyTypeId> childProperties = child->getPropertyTypeIds();
                    QSet<RPropertyTypeId>::iterator it2;
                    for (it2=childProperties.begin(); it2!=childProperties.end(); it2++) {
                        RPropertyTypeId pid = *it2;
                        QPair<QVariant, RPropertyAttributes> p = child->getProperty(pid);
                        if (p.second.isVisibleToParent() && pid.getCustomPropertyName()==tag) {
                            //ret.insert(RPropertyTypeId(QT_TRANSLATE_NOOP("REntity", "Attributes"), p.first.toString()));
                            //return qMakePair(QVariant(p.first), RPropertyAttributes());
                            child->setProperty(pid, value.toString(), transaction);
                            transaction->addObject(child);
                        }
                    }
                }
            }
        }
    }

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RBlockReferenceEntity::getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyPositionX) {
        return qMakePair(QVariant(data.position.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionY) {
        return qMakePair(QVariant(data.position.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionZ) {
        return qMakePair(QVariant(data.position.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleX) {
        return qMakePair(QVariant(data.scaleFactors.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleY) {
        return qMakePair(QVariant(data.scaleFactors.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleZ) {
        return qMakePair(QVariant(data.scaleFactors.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRotation) {
        return qMakePair(QVariant(data.rotation),  RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyColumnCount) {
        return qMakePair(QVariant(data.columnCount), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRowCount) {
        return qMakePair(QVariant(data.rowCount), RPropertyAttributes());
    } else if (propertyTypeId == PropertyColumnSpacing) {
        return qMakePair(QVariant(data.columnSpacing), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRowSpacing) {
        return qMakePair(QVariant(data.rowSpacing), RPropertyAttributes());
    } else if (propertyTypeId == PropertyReferencedBlock) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
                // TODO
                if (!noAttributes) {
                    QSet<QString> blockNames = document->getBlockNames();
                    QSet<QString> filtered;
                    QSet<QString>::iterator it;
                    for (it=blockNames.begin(); it!=blockNames.end(); it++) {
                        if (!(*it).startsWith("*")) {
                            filtered.insert(*it);
                        }
                    }
                    attr.setChoices(filtered);
                }
                return qMakePair(QVariant(document->getBlockName(
                        getData().getReferencedBlockId())), attr);
            }
        } else {
            return qMakePair(QVariant(getData().getReferencedBlockId()),
                    RPropertyAttributes());
        }
    }
    else if (propertyTypeId.isCustom()) {
        if (propertyTypeId.getCustomPropertyTitle()=="Attributes") {
            QString tag = propertyTypeId.getCustomPropertyName();

            const RDocument* doc = getDocument();
            if (doc!=NULL) {
                QSet<REntity::Id> childIds = doc->queryChildEntities(getId(), RS::EntityAttribute);
                QSet<REntity::Id>::iterator it;
                for (it=childIds.begin(); it!=childIds.end(); it++) {
                    REntity::Id childId = *it;
                    QSharedPointer<REntity> child = doc->queryEntityDirect(childId);
                    if (child.isNull()) {
                        continue;
                    }

                    QSet<RPropertyTypeId> childProperties = child->getPropertyTypeIds();
                    QSet<RPropertyTypeId>::iterator it2;
                    for (it2=childProperties.begin(); it2!=childProperties.end(); it2++) {
                        RPropertyTypeId pid = *it2;
                        QPair<QVariant, RPropertyAttributes> p = child->getProperty(pid);
                        if (p.second.isVisibleToParent() && pid.getCustomPropertyName()==tag) {
                            //ret.insert(RPropertyTypeId(QT_TRANSLATE_NOOP("REntity", "Attributes"), p.first.toString()));
                            return qMakePair(QVariant(p.first), RPropertyAttributes());
                        }
                    }
                }
            }

            //document->queryChildEntities(getId());

            //return qMakePair(QVariant("Dummy"), RPropertyAttributes());
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

//void RBlockReferenceEntity::setSelected(bool on) {
//    RDocument* doc = getDocument();
//    if (doc==NULL) {
//        REntity::setSelected(on);
//        return;
//    }

//    QSet<REntity::Id> attributeIds = doc->queryAttributes(getId());
//    qDebug() << "RBlockReferenceEntity::setSelected: attribute IDs: " << attributeIds;
//    QSet<REntity::Id>::iterator it;
//    for (it=attributeIds.begin(); it!=attributeIds.end(); it++) {
//        QSharedPointer<REntity> attribute = doc->queryEntityDirect(*it);
//        if (attribute.isNull()) {
//            qDebug() << "attribute is NULL";
//            continue;
//        }
//        qDebug() << "selecting attribute";
//        attribute->REntity::setSelected(on);
//    }

//    REntity::setSelected(on);
//}

void RBlockReferenceEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    const RDocument* document = getDocument();
    if (document==NULL) {
        qWarning() << "RBlockReferenceEntity::exportEntity: document is NULL";
        return;
    }

    static int recursionDepth = 0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RBlockReferenceEntity::exportEntity: "
            << "maximum recursion depth reached";
        data.groundReferencedBlockId();
        return;
    }

    data.update();

    QSet<REntity::Id> ids = document->queryBlockEntities(data.referencedBlockId);

    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    int i;
    QList<REntity::Id>::iterator it;

    for (int col=0; col<data.columnCount; col++) {
        for (int row=0; row<data.rowCount; row++) {
            for (it = list.begin(), i = 0; it != list.end(); it++, i++) {
                if (preview && i>RSettings::getPreviewEntities()) {
                    break;
                }

                QSharedPointer<REntity> entityBase = data.queryEntity(*it);
                if (entityBase.isNull()) {
                    continue;
                }

                QSharedPointer<REntity> entity;
                if (col!=0 || row!=0) {
                    entity = QSharedPointer<REntity>(entityBase->clone());
                    data.applyColumnRowOffsetTo(*entity, col, row);
//                    RVector offset(col*data.columnSpacing, row*data.rowSpacing);
//                    offset.rotate(data.rotation);
//                    entity->move(offset);
                }
                else {
                    entity = entityBase;
                }

                e.exportEntity(*entity, preview, true, isSelected() || forceSelected);
            }
        }
    }

    // too slow:
//    RDebug::startTimer(4);

//    if (preview) {
//        // TODO: if we interrupted to limit the preview, add bounding box to preview
//        RBox bb = data.getBoundingBox();
//        QList<RLine> l = bb.getLines2d();
//        for (int k=0; k<l.count(); ++k) {
//            e.exportLine(l[k]);
//        }
//    }

//    RDebug::stopTimer(4, "bb");

    recursionDepth--;
}

//bool RBlockReferenceEntity::rotate(double rotation, const RVector& center) {
//    if (document=!NULL && document->hasChildEntities()) {
//        QSet<REntity::Id> childIds = document->queryChildEntities(getId());
//        QSet<REntity::Id>::iterator it;
//        for (it=childIds.begin(); it!=childIds.end(); it++) {
//            REntity::Id childId = *it;
//            QSharedPointer<REntity> child = document->queryEntity(childId);
//            if (child.isNull()) {
//                continue;
//            }
//            child->rotate(rotation, center);
//        }
//    }
//}

void RBlockReferenceEntity::print(QDebug dbg) const {
    dbg.nospace() << "RBlockReferenceEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", position: " << getPosition();
    dbg.nospace() << ", scale: " << getScaleFactors();
    dbg.nospace() << ", rotation: " << getRotation();
    dbg.nospace() << ", referencedBlockId: " << getReferencedBlockId();
    dbg.nospace() << ", referenced block name: " << getDocument()->getBlockName(getReferencedBlockId());
    dbg.nospace() << ")";
}
