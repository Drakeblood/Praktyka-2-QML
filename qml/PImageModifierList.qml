import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import Praktyka.ImageModifiers 1.0

Rectangle {
    width: parent.width
    height: parent.height

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            color: "lightblue"
            height: 50
            Layout.fillWidth: true

            Text {
                anchors.centerIn: parent
                text: "Image modifiers"
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: imageModifierListView

                model: ListModel {
                    id: imageModifierListModel
                }

                delegate: RowLayout {

                    Rectangle {
                        height: imageModifierTextLabel.height * 2
                        width: imageModifierListView.width
                        color: "grey"

                        Text {
                            id: imageModifierTextLabel
                            anchors.centerIn: parent
                            text: model.text
                        }

                        // Bottom line border
                        Rectangle {
                            anchors {
                                left: parent.left
                                right: parent.right
                                bottom: parent.bottom
                            }
                            height: 1
                            color: "lightgrey"
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            //drag.target: parent

                            onClicked: {
                                imageModifierListView.currentItem.opacity = 1
                                imageModifierListView.currentIndex = model.index
                                imageModifierListView.currentItem.opacity = 0.7
                            }
                        }
                    }
                }

                Component.onCompleted: {
                    imageModifierListModel.append({text: "Flip Horizontally"})
                    imageModifierListModel.append({text: "Rotate Image"})
                    imageModifierListModel.append({text: "Gaussian Blur"})
                    imageModifierListModel.append({text: "Contrast"})
                    imageModifierListModel.append({text: "Brightness"})
                    imageModifierListModel.append({text: "Gaussian Noise"})
                }
            }
        }

        RowLayout {

            Button {
                text: qsTr("+")
                onClicked: {
                    editableImageModifierList.appendModifier(imageModifierListView.currentIndex)
                }
                Layout.fillWidth: true
            }
        }
    }
}
