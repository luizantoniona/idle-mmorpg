import QtQuick

Rectangle {
    id: navBar
    height: 48
    color: "#303030"
    border.color: "#444"

    Row {
        anchors.verticalCenter: parent.verticalCenter
        spacing: 12
        anchors.left: parent.left
        anchors.leftMargin: 16

        Text {
            text: "Visual Editor"
            color: "white"
        }
        Text {
            text: "|"
            color: "#777"
        }
        Text {
            text: "Textual Editor"
            color: "#777"
        }
    }
}
