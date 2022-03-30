import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3

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
            width: parent.width / 4
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
                height: parent.height / 4
                anchors.bottom: parent.bottom
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: shortcuts.desktop
                nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
                onAccepted: {
                    console.log("You chose: " + fileUrl)
                    loadedImage.source = fileUrl
                    //loadedImageStreamer.imageLocation = fileUrl
                }
                onRejected: {
                    console.log("Canceled")
                }
            }

            Connections {
                //target: imageProvider

            }
        }

        Rectangle {
            color: "blue";
            width: parent.width / 4
            height: parent.height

            ListView {
                id: imageEditOptionsListView
                width: parent.width
                height: parent.height

                property int dragItemIndex: -1

                model: ListModel {
                    Component.onCompleted: {
                        for (var i = 0; i < 10; ++i) {
                            append({value: i});
                        }
                    }
                }

                delegate: PListItem {
                    id: pListItem
                    listViewReference: imageEditOptionsListView
                }
            }
        }

        Rectangle {
            color: "green";
            width: parent.width / 4
            height: parent.height

            ListView {
                id: chosenImageEditOptionsListView
                width: parent.width
                height: parent.height

                property int dragItemIndex: -1

                model: ListModel {

                }

                DropArea {
                    id: dropArea
                    anchors.fill: parent
                    onDropped: {
                        var newPListItem = PListItem;
                        chosenImageEditOptionsListView.model.append(newPListItem)
                        /*var draggedItem = imageEditOptionsListView.itemAtIndex(imageEditOptionsListView.dragItemIndex);
                        choosenImageEditOptionsListView.model.append(draggedItem);
                        imageEditOptionsListView.dragItemIndex = -1;*/
                    }
                }

                delegate: PListItem {
                    id: pListItem2
                    listViewReference: chosenImageEditOptionsListView
                }
            }
        }

        Rectangle {
            color: "yellow";
            width: parent.width / 4
            height: parent.height

            Image {
                id: livePreviewImage
                width: parent.width
                height: parent.height / 4
                anchors.bottom: parent.bottom
                source: "image://imageProvider/MyImage"
            }

            //PImageTransformationList {
            //    anchors.centerIn: parent
            //}
        }
    }
}
