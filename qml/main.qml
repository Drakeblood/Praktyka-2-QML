import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3

import Praktyka.ImageTransformation 1.0

Window {
    id: rootWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    Window {
        id: imageTransformationListWindow
        width: 400
        height: 300
        visible: false

        //PImageTransformationList {

        //}
    }

    Row {
        id: rowContainer
        width: parent.width
        height: parent.height
        spacing: 4

        Rectangle {
            color: "red";
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
        // image modyficators list start
        Item {
            id: mainContent
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
                        text: "A fake toolbar"
                    }
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: listView
                        model: ImageTransformationModel {
                            id: myModel
                            list: imageTransformationList
                        }

                        delegate: DraggableItem {
                            Rectangle {
                                height: textLabel.height * 2
                                width: listView.width
                                color: "white"

                                Text {
                                    id: textLabel
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
                                myModel.move(from, to)
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
        }
        // image modyficators list end

        Rectangle {
            color: "yellow";
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
