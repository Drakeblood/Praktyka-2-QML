import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import Praktyka.ImageTransformation 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            id: myList
            implicitWidth: 100
            implicitHeight: 400
            anchors.fill: parent

            model: ImageTransformationModel {
                list: imageTransformationList
            }

            delegate: RowLayout {
                width: imageTransformationList.width

                TextField {
                    text: model.name
                    onEditingFinished: model.name = text
                    Layout.fillWidth: true

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        drag.target: parent

                        onClicked: {
                            console.log(model.index)
                            myList.currentItem.opacity = 1
                            myList.currentIndex = model.index
                        }
                    }
                }
            }
        }
    }

    RowLayout {

        Button {
            text: qsTr("-")
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("+")
            onClicked: {
                //imageTransformationListWindow.visible = true
                imageTransformationList.appendItem()
            }
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Duplicate")
            Layout.fillWidth: true
        }
    }
}
