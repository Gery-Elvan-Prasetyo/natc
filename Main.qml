import QtQuick
import QtQuick.Window
import org.kde.layershell 1.0 as LayerShell

Window {
    id: root
    visible: true
    width: 1200
    height: 44
    color: "#171923"
    title: "Serpantinum Native"

    LayerShell.Window.anchors:
        LayerShell.Window.AnchorTop |
        LayerShell.Window.AnchorLeft |
        LayerShell.Window.AnchorRight
    LayerShell.Window.layer: LayerShell.Window.LayerTop
    LayerShell.Window.exclusionZone: 44
    LayerShell.Window.keyboardInteractivity:
        LayerShell.Window.KeyboardInteractivityNone
    LayerShell.Window.scope: "serpantinum-bar"

    property string clockText: ""

    function updateClock() {
        clockText = Qt.formatDateTime(new Date(), "ddd, dd MMM  HH:mm:ss")
    }

    Component.onCompleted: updateClock()

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: root.updateClock()
    }

    Text {
        anchors.left: parent.left
        anchors.leftMargin: 18
        anchors.verticalCenter: parent.verticalCenter
        text: "SERPANTINUM"
        color: "#cdd6f4"
        font.pixelSize: 14
        font.bold: true
    }

    Text {
        anchors.centerIn: parent
        text: "NATIVE  •  PROTOTYPE"
        color: "#a6adc8"
        font.pixelSize: 11
    }

    Text {
        anchors.right: parent.right
        anchors.rightMargin: 18
        anchors.verticalCenter: parent.verticalCenter
        text: root.clockText
        color: "#cdd6f4"
        font.pixelSize: 13
        font.family: "monospace"
    }
}
