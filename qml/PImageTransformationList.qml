import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Praktyka.ImageTransformation 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            implicitWidth: 250
            implicitHeight: 250
            anchors.fill: parent
            clip: true

            model: ImageTransformationModel {
                list: imageTransformationList
            }

            delegate: RowLayout {
                width: parent.width

                TextField {
                    text: model.name
                    onEditingFinished: model.name = text
                    Layout.fillWidth: true

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        drag.target: parent

                        onClicked: {
                            imageTransformationList.doTransform(model.imageTransform)
                        }
                    }
                }
            }
        }
    }

    RowLayout {

        Button {
            text: qsTr("+")
            onClicked: {
                imageTransformationList.appendItem()
                imageTransformationListWindow.visible = true
            }
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Remove completed")
            onClicked: imageTransformationList.removeCompletedItems()
            Layout.fillWidth: true
        }
    }
}
