#include "TaurusGCS.h"
#include <QQmlContext> // Add this line

TaurusGCS::TaurusGCS(int argc, char *argv[]) : QGuiApplication(argc, argv) {
    engine = new QQmlApplicationEngine(this);

    // Add a drone and set it as leader
    swarmManager.addDrone("udp://:14550");
    if (!swarmManager.getDrones().isEmpty()) {
        swarmManager.setLeader(swarmManager.getDrones().first());
        emit swarmManagerChanged(&swarmManager);
    }
}
