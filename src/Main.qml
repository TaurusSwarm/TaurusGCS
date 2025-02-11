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

    Rectangle {
        width: 640
        height: 480
        Column {
            Text {
                text: taurusGCS.swarmManager.leader ? "Latitude: " + taurusGCS.swarmManager.leader.getTelemetryData().latitude : "No leader"
            }
            Text {
                text: taurusGCS.swarmManager.leader ? "Longitude: " + taurusGCS.swarmManager.leader.getTelemetryData().longitude : "No leader"
            }
            Text {
                text: taurusGCS.swarmManager.leader ? "Altitude: " + taurusGCS.swarmManager.leader.getTelemetryData().altitude_meters : "No leader"
            }
        }
    }
}
