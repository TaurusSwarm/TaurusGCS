#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Core/SwarmManager.h"

class TaurusGCS : public QGuiApplication {
    Q_OBJECT
    Q_PROPERTY(SwarmManager* swarmManager READ getSwarmManager NOTIFY swarmManagerChanged)

public:
    TaurusGCS(int argc, char *argv[]);
    QQmlApplicationEngine& getEngine() { return *engine; }
    SwarmManager* getSwarmManager() { return &swarmManager; }

signals:
    void swarmManagerChanged(SwarmManager* swarmManager);

private:
    QQmlApplicationEngine *engine;
    SwarmManager swarmManager;
};