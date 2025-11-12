import QtQuick
import QtQuick.Controls
import IdleMMO 1.0

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
            text: "Quests"
        }

        Button {
            text: "World"
        }
    }

    CreatureControl {}
}
