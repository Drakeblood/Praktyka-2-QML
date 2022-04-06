import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3

import Praktyka.ImageModifiers 1.0

Window {
    id: rootWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")
    color: "#F0E2E2"

    //------------------------Image modifiers list window------------------------
    Window {
        id: imageModifierListWindow
        width: 500
        height: 400
        visible: false

        PImageModifierList {
            anchors.fill: parent
        }
    }

    //------------------------Main window UI------------------------
    Row {
        id: rowContainer
        width: parent.width
        height: parent.height
        spacing: 4

        Rectangle {
            color: "#333333";
            width: parent.width / 3
            height: parent.height

            Button {
                id: loadImageButton
                text: qsTr("Load an image")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    fileDialog.open()
                }
            }

            Image {
                id: loadedImage
                width: parent.width
                height: parent.height / 3
                anchors.bottom: parent.bottom
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: shortcuts.desktop
                nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
                onAccepted: {
                    if(loadedImage.source != fileUrl)
                    {
                        console.log("You chose: " + fileUrl + " - Previous: " + loadedImage.source)

                        loadedImage.source = fileUrl

                        imageStreamer.loadImage(fileUrl, 0)
                        livePreviewImage1.source = "image://imageProvider/0" + fileUrl

                        imageStreamer.loadImage(fileUrl, 1)
                        livePreviewImage2.source = "image://imageProvider/1" + fileUrl
                    }
                    else
                    {
                        console.log("Image has been already loaded")
                    }
                }
                onRejected: {
                    console.log("Canceled")
                }
            }

            Connections {
                //target: imageProvider

            }
        }
        //------------------------Editable image modifiers list------------------------
        Rectangle {
            id: mainContent
            color: "#333333"
            width: parent.width / 3
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
                        id: editableImageModifierListView

                        model: EditableImageModifierListModel {
                            id: editableImageModifierListModel
                            list: editableImageModifierList
                        }

                        delegate: PDraggableItem {
                            Rectangle {
                                height: editableImageModifierTextLabel.height * 2
                                width: editableImageModifierListView.width
                                color: "white"

                                Text {
                                    id: editableImageModifierTextLabel
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
                            }

                            draggedItemParent: mainContent

                            onMoveItemRequested: {
                                console.log("onMoveItemRequested: " + from + " -> " + to)
                                editableImageModifierListModel.move(from, to)
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
                            imageModifierListWindow.visible = true
                        }
                        Layout.fillWidth: true
                    }

                    Button {
                        text: qsTr("Duplicate")
                        Layout.fillWidth: true
                    }
                }
            }
        }

        //------------------------Live preview images------------------------

        Connections {
            target: imageStreamer

            property int a: 22
            function onQImagesUpdated() {
                livePreviewImage1.source = "image://imageProvider/0" + a++;
                livePreviewImage2.source = "image://imageProvider/1" + a++;
            }
        }

        Rectangle {
            color: "#333333";
            width: parent.width / 3
            height: parent.height

            Image {
                id: livePreviewImage1
                width: parent.width
                height: parent.height / 3
                anchors.bottom: parent.bottom
            }

            Image {
                id: livePreviewImage2
                width: parent.width
                height: parent.height / 3
                anchors.bottom: livePreviewImage1.top
                anchors.bottomMargin: 20
            }
        }
    }
}
