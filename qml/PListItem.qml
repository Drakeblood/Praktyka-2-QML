import QtQuick 2.0

Item {
    id: listItem
    property ListView listViewReference: null
    height: 20

    Rectangle {
        id: dragRect
        width: listViewReference.width
        height: listItem.height
        color: "salmon"
        border.color: Qt.darker(color)

        Text {
            anchors.centerIn: parent
            text: "option"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: dragRect

            drag.onActiveChanged: {
                console.log("mouseArea: onActiveChanged")
                if (mouseArea.drag.active) {
                    listViewReference.dragItemIndex = index;
                }
                dragRect.Drag.drop();
            }
        }

        states: [
            State {
                when: dragRect.Drag.active
                ParentChange {
                    target: dragRect
                    parent: rowContainer
                }

                AnchorChanges {
                    target: dragRect
                    anchors.horizontalCenter: undefined
                    anchors.verticalCenter: undefined
                }
            }
        ]

        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: dragRect.width / 2
        Drag.hotSpot.y: dragRect.height / 2
    }
}
