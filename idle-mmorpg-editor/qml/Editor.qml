import QtQuick
import Styles 1.0

Rectangle {
    color: "#202020"

    Column {
        anchors.fill: parent

        Rectangle {
			border.color: "#444"
            color: "#303030"
			height: 48

			NavBar {
			}
        }

        Rectangle {
			anchors.bottom: parent.bottom
			anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10
			color: "#202020"

			Text {
                anchors.centerIn: parent
				color: "#888"
				text: "Editor Content"
            }
        }
    }
}
