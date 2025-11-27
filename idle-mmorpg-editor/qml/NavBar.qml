import QtQuick
import Styles 1.0

Rectangle {
    id: navBar

    border.color: "#444"
	color: "#303030"
	height: 48

    Row {
		anchors.left: parent.left
		anchors.leftMargin: 16
		anchors.verticalCenter: parent.verticalCenter
        spacing: 12

        Text {
			color: Colors.white0
			text: "Visual Editor"
		}

        Text {
			color: "#777"
			text: "|"
		}

		Text {
			color: "#777"
			text: "Textual Editor"
        }
    }
}
