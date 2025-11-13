import QtQuick
import QtQuick.Controls

Rectangle {
    color: "#151515"
    border.color: "#333"

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        Text {
            text: "Navigation"
            color: "white"
            font.bold: true
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
