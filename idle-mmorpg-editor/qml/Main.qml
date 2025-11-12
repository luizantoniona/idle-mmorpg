import QtQuick
import QtQuick.Layouts

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
                Layout.preferredWidth: 240
                Layout.fillHeight: true
            }

            Editor {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
