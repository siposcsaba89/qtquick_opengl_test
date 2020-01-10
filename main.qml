import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import fbitem 1.0

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Material.theme: Material.Dark
    Material.accent: Material.Yellow


    FbItem {
        id: fb1
        x: 0
        y: 50
        width: 300
        height: 300
        MouseArea {
            id: liverbirdMouseArea
            anchors.fill: parent

            drag.target: parent
            drag.axis: Drag.XandYAxis
        }
    }

    Slider {
        id: blue_color
        from: 1
        value: 25
        to: 255
        width: parent.width
        onMoved:
        {
            fb1.changeBlue(value);
        }
    }

}
