import QtQuick

Rectangle {
    color: "#202020"

    Column {
        anchors.fill: parent

        Rectangle {
            height: 48
            color: "#303030"
            border.color: "#444"

            NavBar {}
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            color: "#202020"

            Text {
                anchors.centerIn: parent
                text: "Editor Content"
                color: "#888"
            }
        }
    }
}
