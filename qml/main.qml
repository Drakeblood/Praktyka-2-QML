import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
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

            Column {
                anchors.fill: parent
                spacing: 7
                anchors.topMargin: 20

                Button {
                    id: loadImageButton
                    text: qsTr("Load an image")
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        openFileDialog.open()
                    }
                }

                PParameter {
                    parameterHeader: "Image count"
                    parameterValue: "5"

                    onInputTextChanged: {
                        if(parameterValue != "")
                        {
                            imageSaver.saveCount = parameterValue;
                        }
                    }
                }

                TextEdit {
                    id: imgurLinkTextEdit
                    width: parent.width
                    height: 15
                    readOnly: true
                    wrapMode: Text.WordWrap
                    selectByMouse: true
                    color: "#F0E2E2"
                    text: ""

                    Connections {
                        target: imgurUploader

                        function onUploadedImageUrlChanged(){
                            imgurLinkTextEdit.text = imgurUploader.uploadedImageUrl
                        }
                    }
                }

                Button {
                    id: saveImagesButton
                    text: qsTr("Save images")
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        saveFileDialog.open();
                    }
                }

                Button {
                    id: uploadToImgurButton
                    text: qsTr("Upload to imgur")
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        imgurUploader.upload("test", "ttest")
                    }
                }
            }

            Image {
                id: loadedImage
                width: parent.width
                height: parent.height / 3
                anchors.bottom: parent.bottom
            }

            FileDialog {
                id: openFileDialog
                title: "Please choose a file"
                folder: shortcuts.desktop
                nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
                onAccepted: {
                    if(loadedImage.source != openFileDialog.fileUrl)
                    {
                        console.log("You chose: " + fileUrl + " - Previous: " + loadedImage.source)

                        loadedImage.source = fileUrl
                        imageStreamer.loadImage(fileUrl)
                    }
                    else
                    {
                        console.log("Image has been already loaded")
                    }
                }
                onRejected: {
                    console.log("Open image canceled")
                }
            }

            FolderDialog {
                id: saveFileDialog
                title: "Please choose a location"
                currentFolder: openFileDialog.shortcuts.desktop
                onAccepted: {
                    console.log("You chose: " + folder)
                    imageSaver.saveLocation = folder
                    imageSaver.saveImages()
                }
                onRejected: {
                    console.log("Save images canceled")
                }
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

                        Connections {
                            target: editableImageModifierList

                            function onListItemChanged() {
                                livePreviewImageModifierExecutor.executeModifiers()
                            }

                            function onPostItemRemoved() {
                                parametersRectangle.visible = false
                            }
                        }

                        function changeItemFocus(index) {
                            if(index >= 0)
                            {
                                if(currentItem != null)
                                {
                                    editableImageModifierListView.currentItem.opacity = 1
                                }
                                editableImageModifierListView.currentIndex = index
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
                                    return
                                }
                            }
                            parametersRectangle.visible = false
                        }

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
                        onClicked: {
                            editableImageModifierList.removeModifier(editableImageModifierListView.currentIndex);
                        }
                    }

                    Button {
                        text: qsTr("+")
                        Layout.fillWidth: true
                        onClicked: {
                            imageModifierListWindow.visible = true
                        }
                    }

                    Button {
                        text: qsTr("Duplicate")
                        Layout.fillWidth: true
                        onClicked: {
                            editableImageModifierList.cloneModifier(editableImageModifierListView.currentIndex);
                        }
                    }
                }
            }
        }

        //------------------------Live preview images------------------------

        Connections {
            target: imageStreamer

            property bool flipFlop: true //need different id each time
            function onQImagesUpdated() {
                livePreviewImage1.source = "image://imageProvider/0" + flipFlop;
                livePreviewImage2.source = "image://imageProvider/1" + flipFlop;
                flipFlop = !flipFlop;
            }
        }

        Rectangle {
            color: "#333333";
            width: parent.width / 3
            height: parent.height

            Column {
                width: parent.width
                height: parent.height
                spacing: 10

                Rectangle {
                    id: parametersRectangle
                    color: "#333333";
                    width: parent.width
                    height: parent.height / 3
                    visible: false

                    Column {
                        width: parent.width
                        height: parent.height
                        spacing: 10

                        PParameter {

                        }

                        PParameter {

                        }
                    }

                    Button {
                        text: "Save"
                        height: 30
                        width: 70
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottomMargin: 20

                        onClicked: {
                            let params = editableImageModifierList.getModifierParams(editableImageModifierListView.currentIndex)

                            if(params.length > 0)
                            {
                                let inputTextFields = parametersRectangle.children[0].children;
                                let values = [];

                                for(let i = 0; i < params.length && i < inputTextFields.length; i++)
                                {
                                    values.push(inputTextFields[i].parameterValue);
                                }
                                editableImageModifierList.setModifierParams(editableImageModifierListView.currentIndex, values)
                                livePreviewImageModifierExecutor.executeModifiers()
                            }
                        }
                    }
                }

                Image {
                    id: livePreviewImage2
                    width: parent.width
                    height: parent.height / 3
                }

                Image {
                    id: livePreviewImage1
                    width: parent.width
                    height: parent.height / 3
                }
            }
        }
    }
}
