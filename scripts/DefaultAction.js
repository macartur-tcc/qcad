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

include("EAction.js");
include("Select/Select.js");
include("Widgets/CadToolBar/CadToolBar.js");

/**
 * \class DefaultAction
 * \brief Default action which is active when no other tool
 * or action is active. Implements basic entity selection 
 * and drag and drop.
 */
function DefaultAction(guiAction) {
    EAction.call(this, guiAction);
}

DefaultAction.prototype = new EAction();

DefaultAction.State = {
    Neutral : 0,
    Dragging : 1,
    SettingCorner2 : 2,
    MovingEntity : 3,
    MovingEntityInBlock : 4,
    SettingEntity : 5,
    MovingReference : 6,
    SettingReference : 7
};

DefaultAction.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    //this.snapRangePixels = RSettings.getSnapRange();
    //this.minSnapRangePixels = Math.min(this.snapRangePixels / 2, 10);
    this.pickRangePixels = RSettings.getPickRange();
    this.minPickRangePixels = Math.min(this.pickRangePixels / 2, 10);
    this.d1Model = RVector.invalid;
    this.d1Screen = RVector.invalid;
    this.d2Model = RVector.invalid;
    this.d2Screen = RVector.invalid;
    this.di = this.getDocumentInterface();
    this.document = this.getDocument();
    this.setState(DefaultAction.State.Neutral);
    this.blockRefId = RObject.INVALID_ID;
    this.entityInBlockId = RObject.INVALID_ID;
};

DefaultAction.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    var appWin = EAction.getMainWindow();

    if (this.state === DefaultAction.State.MovingReference
            || this.state === DefaultAction.State.SettingReference
            || this.state === DefaultAction.State.MovingEntity
            || this.state === DefaultAction.State.MovingEntityInBlock
            || this.state === DefaultAction.State.SettingEntity) {
        this.di.setClickMode(RAction.PickCoordinate);
        this.setCrosshairCursor();
        EAction.showSnapTools();
    } else {
        this.di.setClickMode(RAction.PickingDisabled);
        this.setArrowCursor();
    }

    switch (this.state) {
    case DefaultAction.State.Neutral:
        this.d1Model = RVector.invalid;
        this.d1Screen = RVector.invalid;
        this.d2Model = RVector.invalid;
        this.d2Screen = RVector.invalid;
        var ltip = qsTr("Select entity or region");
        if (this.di.hasSelection()) {
            ltip += "\n" + qsTr("Move entity or reference");
        }
        this.setLeftMouseTip(ltip);
        this.setRightMouseTip("");
        this.setCommandPrompt();
        break;
    case DefaultAction.State.Dragging:
        this.d2Model = RVector.invalid;
        this.d2Screen = RVector.invalid;
        break;
    case DefaultAction.State.SettingCorner2:
        this.setLeftMouseTip(qsTr("Set second corner"));
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingReference:
    case DefaultAction.State.SettingReference:
        this.setLeftMouseTip(
                qsTr("Specify target point of reference point")
        );
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingEntity:
    case DefaultAction.State.SettingEntity:
        this.setLeftMouseTip(
                qsTr("Specify target point of selection")
        );
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingEntityInBlock:
        this.setLeftMouseTip(
                qsTr("Move entity to desired location")
        );
        break;
    default:
        break;
    }
};

DefaultAction.prototype.suspendEvent = function() {
    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(false);
    }
};

DefaultAction.prototype.resumeEvent = function() {
    EAction.prototype.resumeEvent.call(this);
};

DefaultAction.prototype.mouseMoveEvent = function(event) {
    // we're in the middle of panning: don't do anything:
    if (event.buttons().valueOf() === Qt.MidButton.valueOf() ||
        (event.buttons().valueOf() === Qt.LeftButton.valueOf() &&
         event.modifiers().valueOf() === Qt.ControlModifier.valueOf())) {
         return;
    }

    var view, referencePoint, entityId, range;
    
    if (isNull(this.pickRangePixels)) {
        return;
    }

    view = event.getGraphicsView();

    switch (this.state) {
    case DefaultAction.State.Neutral:
        var screenPosition = event.getScreenPosition();
        referencePoint = view.getClosestReferencePoint(screenPosition, this.minPickRangePixels);
        if (referencePoint.isValid()) {
            this.highlightReferencePoint(referencePoint);
        } else {
            range = view.mapDistanceFromView(this.pickRangePixels);
            var strictRange = view.mapDistanceFromView(10);
            RMouseEvent.setOriginalMousePos(event.globalPos());
            entityId = this.di.getClosestEntity(event.getModelPosition(), range, strictRange, false);
            RMouseEvent.resetOriginalMousePos();
            if (entityId !== RObject.INVALID_ID && this.document.isEntityEditable(entityId)) {
                this.highlightEntity(entityId);
            }
        }
        break;

    case DefaultAction.State.Dragging:
        this.d2Model = event.getModelPosition();
        this.d2Screen = event.getScreenPosition();
        view = event.getGraphicsView();
        if (!this.d1Screen.equalsFuzzy(this.d2Screen, 10 /*this.minPickRangePixels*/)) {
            // if the dragging started on top of a reference point,
            // start moving the reference point:
            referencePoint = view.getClosestReferencePoint(this.d1Screen, this.minPickRangePixels);
            if (referencePoint.isValid()) {
                this.d1Model = referencePoint;
                this.di.setRelativeZero(this.d1Model);
                this.setState(DefaultAction.State.MovingReference);
            } else {
                // if the dragging started on top of an entity,
                // start moving the entity:
                entityId = view.getClosestEntity(this.d1Screen, this.minPickRangePixels, 10, false);

                // in block easy drag and drop:
                if (entityId !== RObject.INVALID_ID) {
                    var doc = this.getDocument();
                    if (!isNull(doc)) {
                        var entity = doc.queryEntityDirect(entityId);
                        if (isBlockReferenceEntity(entity)) {
                            var blockId = entity.getReferencedBlockId();
                            var block = doc.queryBlock(blockId);
                            if (!isNull(block)) {
                                range = view.mapDistanceFromView(this.pickRangePixels);
                                if (Math.abs(entity.getScaleFactors().x)>0) {
                                    range /= Math.abs(entity.getScaleFactors().x);
                                }
                                // cursor, mapped to block coordinates:
                                var pBlock = entity.mapToBlock(this.d1Model);
                                var box = new RBox(pBlock, range);
                                var candidateIds = doc.queryIntersectedEntitiesXY(box, true, false, blockId);
                                var entityInBlockId;
                                if (candidateIds.length===1) {
                                    entityInBlockId = candidateIds[0];
                                }
                                else {
                                    entityInBlockId = doc.queryClosestXY(candidateIds, pBlock, range*2, false, range/2);
                                }
                                var entityInBlock = doc.queryEntityDirect(entityInBlockId);
                                if (!isNull(entityInBlock) && getInBlockEasyDragAndDrop(entityInBlock)) {
                                    var refP = entityInBlock.getReferencePoints();
                                    if (refP.length>0) {
                                        this.d1Model = refP[0]; //entity.mapToBlock(refP[0]);
                                    }
                                    else {
                                        this.d1Model = pBlock;
                                    }
                                    this.entityInBlockId = entityInBlockId;
                                    this.blockRefId = entityId;
                                    this.setState(DefaultAction.State.MovingEntityInBlock);
                                    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapFree/SnapFree.js");
                                    if (!isNull(guiAction)) {
                                        guiAction.slotTrigger();
                                    }
                                    this.di.setSnap(new RSnapFree());
                                    break;
                                }
                            }
                        }
                    }
                }

                if (entityId !== RObject.INVALID_ID && this.document.hasSelection()) {
                    // move start point of dragging operation to closest
                    // reference point:
                    // TODO: use auto snap instead here (optional?):
                    this.d1Model = view.getClosestReferencePoint(entityId, this.d1Screen);
                    this.di.setRelativeZero(this.d1Model);
                    this.setState(DefaultAction.State.MovingEntity);
                } else {
                    // if the dragging started in an empty space,
                    // start box selection:
                    this.setState(DefaultAction.State.SettingCorner2);
                    // make sure one mouse move is enough to get a visible preview 
                    // (for testing, one mouse move event has to be enough):
                    this.mouseMoveEvent(event);
                }
            }
        }
        break;

    case DefaultAction.State.SettingCorner2:
        this.d2Model = event.getModelPosition();
        Select.previewSelectionBox(
            this.getDocumentInterface(),
            new RBox(this.d1Model, this.d2Model),
            this.d1Model.x > this.d2Model.x
        );
        break;

    // easy in block entity drag and drop (point mark labels):
//    case DefaultAction.State.MovingEntityInBlock:
//        this.moveEntityInBlock(event.getModelPosition(), true);
//        break;

    default:
        break;
    }
};

DefaultAction.prototype.getEntityIdUnderCursor = function(event, range) {
    var view = event.getGraphicsView();
    if (isNull(range)) {
        range = this.pickRangePixels;
    }

    range = view.mapDistanceFromView(range);

    var strictRange = view.mapDistanceFromView(10);
    return this.di.getClosestEntity(event.getModelPosition(), range, strictRange, false);
};

DefaultAction.prototype.mouseReleaseEvent = function(event) {
    var persistentSelection = RSettings.getBoolValue("GraphicsView/PersistentSelection", false);
    var view, range, strictRange, entityId;

    var add = false;
    if ((event.modifiers().valueOf() === Qt.ShiftModifier.valueOf()) ||
            (event.modifiers().valueOf() === Qt.ControlModifier.valueOf()) ||
            persistentSelection===true) {

        add = true;
    }

    if (event.button() === Qt.LeftButton) {
        switch (this.state) {
        case DefaultAction.State.Dragging:
            entityId = this.getEntityIdUnderCursor(event);
            //qDebug("entity id: ", entityId);
            if (entityId !== -1) {
                if (add && this.document.isSelected(entityId)) {
                    this.deselectEntity(entityId);
                }
                else {
                    this.selectEntity(entityId, add);
                }
            } else {
                if (!add) {
                    if (persistentSelection===false) {
                        this.di.clearSelection();
                    }
                }
            }
            this.di.clearPreview();
            this.di.repaintViews();
            this.setState(DefaultAction.State.Neutral);
            break;

        case DefaultAction.State.SettingCorner2:
            this.di.clearPreview();
            this.d2Model = event.getModelPosition();

            if ((event.modifiers().valueOf() == Qt.ShiftModifier.valueOf()) ||
                (event.modifiers().valueOf() == Qt.ControlModifier.valueOf()) ||
                persistentSelection===true) {

                // add all entities in window to the selection:
                this.di.selectBoxXY(new RBox(this.d1Model, this.d2Model), true);
            } else {
                // select entities in window only:
                this.di.selectBoxXY(new RBox(this.d1Model, this.d2Model), false);
            }
            // event.setConsumed(true);
            this.setState(DefaultAction.State.Neutral);
            break;

        // easy in block entity drag and drop (point mark labels):
//        case DefaultAction.State.MovingEntityInBlock:
//            this.moveEntityInBlock(event.getModelPosition(), false);
//            break;

        default:
            break;
        }
    } else if (event.button() == Qt.RightButton) {
        var handled = false;

        if (this.state!==DefaultAction.State.Neutral && this.state!==DefaultAction.State.MovingEntityInBlock) {
            this.di.clearPreview();
            this.di.repaintViews();
            this.setState(DefaultAction.State.Neutral);
            handled = true;
        }

        else if (this.state===DefaultAction.State.Neutral) {
            var rightClickRange = RSettings.getIntValue("GraphicsView/RightClickRange", 10);
            entityId = this.getEntityIdUnderCursor(event, rightClickRange);

            var rightClickToDeselect = RSettings.getBoolValue("GraphicsView/RightClickToDeselect", false);
            var rightClickEntityContextMenu = RSettings.getBoolValue("GraphicsView/RightClickEntityContextMenu", false);

            // right-click on entity can be used to show context menu:
            if (entityId!==-1) {
                // show entity context menu:
                if (rightClickEntityContextMenu) {
                    var appWin = EAction.getMainWindow();
                    appWin.showContextMenu(entityId);
                    handled = true;
                }

                // use right-click on entity to select entity:
                if (rightClickToDeselect) {
                    this.selectEntity(entityId, add);
                    handled = true;
                }
            }
            else {
                // use right-click into empty area to deselect everything:
                if (rightClickToDeselect) {
                    if (this.di.hasSelection()) {
                        this.di.clearSelection();
                        this.di.clearPreview();
                        this.di.repaintViews();
                        handled = true;
                    }
                }
            }
        }

        if (!handled) {
            CadToolBar.back();
        }
    }
};

DefaultAction.prototype.mousePressEvent = function(event) {
    if (event.button() == Qt.LeftButton
            && event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {
        if (this.state == DefaultAction.State.Neutral) {
            this.d1Model = event.getModelPosition();
            this.d1Screen = event.getScreenPosition();
            this.setState(DefaultAction.State.Dragging);
            this.di.clearPreview();
        }
    }
};

DefaultAction.prototype.mouseDoubleClickEvent = function(event) {
    if (event.button() == Qt.LeftButton && this.state===DefaultAction.State.Neutral) {
        var view = event.getGraphicsView();
        var range = view.mapDistanceFromView(this.pickRangePixels);
        var strictRange = view.mapDistanceFromView(10);
        var entityId = this.di.getClosestEntity(event.getModelPosition(), range, strictRange, false);
        if (entityId===RObject.INVALID_ID) {
            return;
        }

        this.entityDoubleClicked(entityId, event);
    }
    EAction.prototype.mouseDoubleClickEvent.call(this, event);
};

DefaultAction.prototype.escapeEvent = function(event) {
    this.di.clearPreview();
    this.di.repaintViews();
    CadToolBar.back();
    this.setState(DefaultAction.State.Neutral);
};

DefaultAction.prototype.pickCoordinate = function(event, preview) {
    var op;

    switch (this.state) {
    case DefaultAction.State.MovingReference:
    case DefaultAction.State.SettingReference:
        if (preview) {
            this.d2Model = event.getModelPosition();
            op = new RMoveReferencePointOperation(this.d1Model, this.d2Model);
            this.di.previewOperation(op);
        }
        else {
            if (this.state===DefaultAction.State.MovingReference) {
                this.setState(DefaultAction.State.SettingReference);
            }
            else {
                this.d2Model = event.getModelPosition();
                op = new RMoveReferencePointOperation(this.d1Model, this.d2Model);
                op.setText(qsTr("Move Reference Point"));
                this.di.applyOperation(op);
                this.di.clearPreview();
                this.di.repaintViews();
                CadToolBar.back();
                this.setState(DefaultAction.State.Neutral);
            }
        }
        break;

    case DefaultAction.State.MovingEntity:
    case DefaultAction.State.SettingEntity:
        if (preview) {
            this.d2Model = event.getModelPosition();
            op = new RMoveSelectionOperation(this.d1Model, this.d2Model);
            this.di.previewOperation(op);
        }
        else {
            if (this.state===DefaultAction.State.MovingEntity) {
                this.setState(DefaultAction.State.SettingEntity);
            }
            else {
                this.d2Model = event.getModelPosition();
                op = new RMoveSelectionOperation(this.d1Model, this.d2Model);
                op.setText(qsTr("Move Selection"));
                this.di.applyOperation(op);
                this.di.clearPreview();
                this.di.repaintViews();
                CadToolBar.back();
                this.setState(DefaultAction.State.Neutral);
            }
        }
        break;

    // easy in block entity drag and drop (point mark labels):
    case DefaultAction.State.MovingEntityInBlock:
        var doc = this.getDocument();
        if (isNull(doc)) {
            break;
        }
        var blockRef = doc.queryEntity(this.blockRefId);
        if (isNull(blockRef)) {
            break;
        }
        this.d2Model = blockRef.mapToBlock(event.getModelPosition());
        var entityInBlock = doc.queryEntity(this.entityInBlockId);
        entityInBlock.move(this.d2Model.operator_subtract(this.d1Model));
        op = new RAddObjectsOperation();
        op.setText(qsTr("Move Entity"));
        op.addObject(entityInBlock, false);
        if (preview) {
            this.di.previewOperation(op);
        }
        else {
            doc.removeFromSpatialIndex(blockRef);
            this.di.applyOperation(op);
            blockRef.update();
            doc.addToSpatialIndex(blockRef);
            this.setState(DefaultAction.State.Neutral);
            var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapAuto/SnapAuto.js");
            if (!isNull(guiAction)) {
                guiAction.slotTrigger();
            }
            this.di.setSnap(new RSnapAuto());
        }
        break;

    default:
        break;
    }
};

/**
 * Called when the mouse cursor hovers over an entity.
 */
DefaultAction.prototype.highlightEntity = function(entityId) {
    if (isNull(this.di)) {
        return;
    }

    this.di.highlightEntity(entityId);
};

/**
 * Called when the mouse cursor hovers over a reference point.
 */
DefaultAction.prototype.highlightReferencePoint = function(referencePoint) {
    if (isNull(this.di)) {
        return;
    }

    this.di.highlightReferencePoint(referencePoint);
};

/**
 * Called when the user deselects a single entity.
 */
DefaultAction.prototype.deselectEntity = function(entityId) {
    if (isNull(this.di)) {
        return;
    }

    this.di.deselectEntity(entityId);
};

/**
 * Called when the user selects a single entity.
 */
DefaultAction.prototype.selectEntity = function(entityId, add) {
    if (isNull(this.di)) {
        return;
    }

    this.di.selectEntity(entityId, add);
};

/**
 * Called when the user selects a single entity.
 */
DefaultAction.prototype.entityDoubleClicked = function(entityId, event) {
    if (isNull(this.document) || isNull(this.di)) {
        return;
    }

    var entity = this.document.queryEntity(entityId);

    if (isTextEntity(entity) ||
        isAttributeEntity(entity) ||
        isAttributeDefinitionEntity(entity)) {

        if (RSettings.getBoolValue("GraphicsView/DoubleClickEditText", true)===true) {
            include("scripts/Modify/EditText/EditText.js");
            EditText.editText(entity);
        }
    }
    else if (isBlockReferenceEntity(entity)) {
        // in block text editing with double-click:
        var blockId = entity.getReferencedBlockId();
        var block = this.document.queryBlock(blockId);
        if (!isNull(block)) {
            var view = event.getGraphicsView();
            var range = view.mapDistanceFromView(this.pickRangePixels);
            // cursor, mapped to block coordinates:
            var pBlock = entity.mapToBlock(event.getModelPosition());
            var box = new RBox(
                pBlock.operator_subtract(new RVector(range,range)),
                pBlock.operator_add(new RVector(range,range))
            );
            var res = this.document.queryIntersectedEntitiesXY(box, true, false, blockId);
            var entityInBlockId;
            if (res.length===1) {
                entityInBlockId = res[0];
            }
            else {
                entityInBlockId = this.document.queryClosestXY(res, pBlock, range*2, false);
            }
            var entityInBlock = this.document.queryEntity(entityInBlockId);
            if (!isNull(entityInBlock) && isTextBasedEntity(entityInBlock) && getInBlockTextEdit(entityInBlock)) {
                include("scripts/Modify/EditText/EditText.js");
                EditText.editText(entityInBlock);
                return;
            }
        }

        if (RSettings.getBoolValue("GraphicsView/DoubleClickEditBlock", false)===true) {
            include("scripts/Block/Block.js");
            Block.editBlock(this.di, entity.getReferencedBlockName());
        }
    }
};
