import QtQuick          2.15
import QtQuick.Controls 2.15

Item {
    id:         tray
    width:      parent.width - 20
    height:     trayRect.height

    Rectangle {
        id:             trayRect
        color:          "#1b1b1b"
        width:          parent.width
        height:         50
        radius:         10
        visible:        true

        Rectangle {
            id:                     logoRect
            width:                  tray.height * 0.8
            height:                 tray.height * 0.8
            color:                  "#2a2a2a"
            radius:                 10
            border.width:           1
            border.color:           "#222222"
            anchors {
                left:               parent.left
                bottom:             parent.bottom
                leftMargin:         tray.height * 0.1
                bottomMargin:       tray.height * 0.1
            }

            Image {
                id:                 logo
                source:             "qrc:/icons/logo.svg"
                width:              parent.height * 0.5
                height:             parent.height * 0.5
                anchors.centerIn:   parent
            }
        }

        LinkButton {
            id:                     linkButton
            visible:                true
            anchors.top:            parent.top
            anchors.topMargin:      (parent.height - height) * 0.5
            anchors.right:          parent.right
            anchors.rightMargin:    anchors.topMargin
        }

        ConnectionLinkChooser {
            id:                     connectionLinkChooser
            visible:                true
            anchors.right:          linkButton.left
            anchors.rightMargin:    10
            anchors.top:            linkButton.top
        }
    }
}
