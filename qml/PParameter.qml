import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property string parameterHeader: "Parameter"
    property string parameterValue: "0"
    signal inputTextChanged;

    width: parent.width
    height: 45

    Column {
        width: parent.width
        height: parent.height
        spacing: 5

        Label {
            width: parent.width
            height: 15
            color: "#F0E2E2"
            text: parameterHeader
        }

        Rectangle {
            width: parent.width
            height: 25
            border.color: "gray"
            border.width: 1

            TextInput {
                anchors.fill: parent
                anchors.margins: 4
                text: parameterValue
                onTextChanged: {
                    console.log("onTextChanged")
                    parameterValue = text
                    inputTextChanged();
                }
            }
        }
    }
}
