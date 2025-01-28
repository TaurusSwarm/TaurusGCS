import QtQuick          2.15
import QtQuick.Controls 2.15
import QtLocation       5.15
import QtPositioning    5.15

Item {
    id:         flightMap
    width:      parent.width
    height:     parent.height

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id:             map
        anchors.fill:   parent
        plugin:         mapPlugin
        center:         QtPositioning.coordinate(41.01, 28.96)
        zoomLevel:      14

        WheelHandler {
            id: wheel
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale:  1/120
            target:         map
            property:       "zoomLevel"
        }

        DragHandler {
            id:                     drag
            target:                 null
            onTranslationChanged:   (delta) => map.pan(-delta.x, -delta.y)
        }

        Shortcut {
            enabled:        map.zoomLevel < map.maximumZoomLevel
            sequence:       StandardKey.ZoomIn
            onActivated:    map.zoomLevel = Math.round(map.zoomLevel + 1)
        }

        Shortcut {
            enabled:        map.zoomLevel > map.minimumZoomLevel
            sequence:       StandardKey.ZoomOut
            onActivated:    map.zoomLevel = Math.round(map.zoomLevel - 1)
        }
    }

    Toolbox {
        id:                     flightMapToolbox
        visible:                true
        anchors.top:            parent.top
        anchors.topMargin:      10
        anchors.left:           parent.left
        anchors.leftMargin:     10
    }

    Tray
    {
        id:                     trayId
        visible:                true
        anchors.bottom:         statusBar.top
        anchors.bottomMargin:   5
        anchors.left:           parent.left
        anchors.leftMargin:     10
    }

    StatusBar
    {
        id:                     statusBar
        visible:                true
        anchors.bottom:         parent.bottom
        anchors.bottomMargin:   5
        anchors.left:           parent.left
        anchors.leftMargin:     10
    }
    
    
}
