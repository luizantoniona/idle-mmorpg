import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
	id: root

	border.color: "#333"
	color: "#151515"

	RowLayout {
		anchors.fill: parent
		spacing: 10

		ColumnLayout {
			anchors.bottom: parent.bottom
			anchors.margins: 10
			anchors.top: parent.top
			spacing: 8
			width: 150

			Text {
				color: "white"
				font.bold: true
				text: "Navigation"
			}

			Button {
				text: "Creatures"
			}

			Button {
				text: "Items"
			}

			Button {
				text: "Spells"
			}

			Button {
				text: "World"
			}
		}
	}
}
