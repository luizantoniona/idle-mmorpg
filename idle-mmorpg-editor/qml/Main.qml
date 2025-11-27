import QtQuick
import QtQuick.Layouts
import Editor 1.0

Window {
    height: 768
    title: qsTr("Idle MMORPG Editor")
    visible: true
    width: 1280

    Rectangle {
        anchors.fill: parent
        color: "black"

        RowLayout {
            anchors.fill: parent

            FilesBar {
				Layout.fillHeight: true
				Layout.preferredWidth: 240
            }

            Editor {
                Layout.fillHeight: true
				Layout.fillWidth: true
			}
        }
    }
}
