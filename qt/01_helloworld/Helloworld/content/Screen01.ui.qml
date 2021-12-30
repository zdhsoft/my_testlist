import QtQuick
import QtQuick.Controls
import Helloworld
import Qt.SafeRenderer 1.1

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello Helloworld")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }

    GridView {
        id: gridView
        x: 569
        y: 417
        width: 271
        height: 241
        cellHeight: 70
        cellWidth: 70
        delegate: Item {
            x: 5
            height: 50
            Column {
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    x: 5
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                spacing: 5
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
    }

    Text {
        id: text1
        x: 846
        y: 417
        width: 139
        height: 16
        text: qsTr("Text")
        font.pixelSize: 12
    }

    TextEdit {
        id: textEdit
        x: 954
        y: 628
        width: 80
        height: 20
        text: qsTr("Text Edit")
        font.pixelSize: 12
    }
}
