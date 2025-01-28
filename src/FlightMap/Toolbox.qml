import QtQuick          2.15
import QtQuick.Controls 2.15

Item {
    id:             statusBar
    width:          50
    height:         250

    Rectangle {
        id:         statusBarRect
        width:      parent.width
        height:     parent.height
        radius:     10
        color:      "#1b1b1b"
        visible:    true
    }
}