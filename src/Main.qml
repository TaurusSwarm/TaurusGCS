import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow
{
    id:                         applicationWindow
    title:                      "UAV Sync"
    visible:                    true
    width:                      1280
    height:                     720

    FlightMap {
        id:                     flightMap
        visible:                true
    }
}
