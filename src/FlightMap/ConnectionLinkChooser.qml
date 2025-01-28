import QtQuick          2.15
import QtQuick.Controls 2.15

Item {
    id:         connectionLinkChooser
    width:      200
    height:     25
    
    // Rectangle {
    //     id:         connectionLinkRect
    //     width:      parent.width
    //     height:     parent.height
    //     radius:     10
    //     color:      "#1b1b1b"
    // }

    ComboBox {
        model: ListModel {
            id: model
            ListElement { text: "/dev/ttyUSB0" }
            ListElement { text: "Siyi HM30" }
        }
        width:                  parent.width
        height:                 parent.height
        anchors.centerIn:       parent
        // background: Rectangle {
        //     anchors.right:  parent.right
        //     anchors.top:    parent.top
        //     visible:        true
        //     width:          parent.width * 0.8
        //     height:         parent.height * 0.8
        // }
    }
}