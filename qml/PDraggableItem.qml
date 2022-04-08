/*
 * listviewdragitem
 *
 * An example of reordering items in a ListView via drag'n'drop.
 *
 * Author: Aurélien Gâteau
 * License: BSD
 */
import QtQuick 2.0

Item {
    id: root

    default property Item contentItem

    // This item will become the parent of the dragged item during the drag operation
    property Item draggedItemParent

    signal moveItemRequested(int from, int to)

    width: contentItem.width
    height: contentItem.height

    // Make contentItem a child of contentItemWrapper
    onContentItemChanged: {
        console.log("onContentItemChanged: " + this)
        contentItem.parent = contentItemWrapper
    }

    Rectangle {
        id: contentItemWrapper
        anchors.fill: parent
        Drag.active: dragArea.drag.active

        Drag.hotSpot {
            x: contentItem.width / 2
            y: contentItem.height / 2
        }

        MouseArea {
            id: dragArea
            anchors.fill: parent
            drag.target: parent
            // Keep the dragged item at the same X position. Nice for lists, but not mandatory
            drag.axis: Drag.YAxis
            // Disable smoothed so that the Item pixel from where we started the drag remains under the mouse cursor
            drag.smoothed: false

            onReleased: {
                if (drag.active) {
                    console.log("onReleased: " + this)
                    emitMoveItemRequested()
                }
            }
            onClicked: {
                console.log("onClicked")

                editableImageModifierListView.currentItem.opacity = 1
                editableImageModifierListView.currentIndex = model.index
                editableImageModifierListView.currentItem.opacity = 0.7

                let paramNames = editableImageModifierList.getModifierParamNames(editableImageModifierListView.currentIndex)
                let params = editableImageModifierList.getModifierParams(editableImageModifierListView.currentIndex)

                if(paramNames.length > 0 && params.length > 0)
                {
                    let inputTextFields = parametersRectangle.children[0].children;

                    for(let i = 0; i < paramNames.length && i < params.length && i < inputTextFields.length; i++)
                    {
                        inputTextFields[i].parameterHeader = paramNames[i]
                        inputTextFields[i].parameterValue = params[i]
                    }
                    parametersRectangle.visible = true
                }
                else
                {
                    parametersRectangle.visible = false
                }
            }
        }
    }

    states: [
        State {
            when: dragArea.drag.active
            name: "dragging"

            ParentChange {
                target: contentItemWrapper
                parent: draggedItemParent
            }

            PropertyChanges {
                target: contentItemWrapper
                opacity: 0.9
                anchors.fill: undefined
                width: contentItem.width
                height: contentItem.height
            }

            PropertyChanges {
                target: root
                height: 0
            }
        }
    ]

    Loader {
        id: topDropAreaLoader
        active: model.index === 0
        anchors {
            left: parent.left
            right: parent.right
            bottom: root.verticalCenter
        }
        height: contentItem.height
        sourceComponent: Component {

            PDraggableItemDropArea {
                dropIndex: 0
            }
        }
    }

    PDraggableItemDropArea {
        anchors {
            left: parent.left
            right: parent.right
            top: root.verticalCenter
        }
        height: contentItem.height
        dropIndex: model.index + 1
    }

    function emitMoveItemRequested() {
        var dropArea = contentItemWrapper.Drag.target
        if (!dropArea) {
            return
        }
        var dropIndex = dropArea.dropIndex

        // If the target item is below us, then decrement dropIndex because the target item is going to move up when
        // our item leaves its place
        if (model.index < dropIndex) {
            dropIndex--
        }
        if (model.index === dropIndex) {
            return
        }
        root.moveItemRequested(model.index, dropIndex)
    }
}
