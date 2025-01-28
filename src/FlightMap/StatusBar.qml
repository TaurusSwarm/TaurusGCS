import QtQuick          2.15
import QtQuick.Controls 2.15

Item {
    id:             statusBar
    width:          parent.width - 20
    height:         statusBarRect.height

    Rectangle {
        id:         statusBarRect
        width:      parent.width
        height:     25
        radius:     10
        color:      "#1b1b1b"
        visible:    true
    }
}