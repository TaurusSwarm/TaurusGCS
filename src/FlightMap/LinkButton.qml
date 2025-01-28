import QtQuick          2.15
import QtQuick.Controls 2.15

Button {
    id:                 connectionButton
    text:               qsTr("Link")
    font.pixelSize:     15
    width:              100
    height:             25

    Connections {

    }

    contentItem: Text {
        text:                   connectionButton.text
        font:                   connectionButton.font
        color:                  "#ffffff"
        verticalAlignment:      Text.AlignVCenter
        anchors.right:          connectionButton.right
    }

    background: Rectangle {
        width:      parent.width
        height:     parent.height
        color:      "red"
        radius:     5

        Image {
            source:                 "qrc:/icons/link.svg"
            visible:                true
            height:                 parent.height * 0.7
            width:                  height
            anchors.top:            parent.top
            anchors.topMargin:      parent.height * 0.15
            anchors.right:          parent.right
            anchors.rightMargin:    anchors.topMargin * 2
        }
    }
}