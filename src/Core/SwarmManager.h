#pragma once

#ifndef SWARM_H
#define SWARM_H

#include <QObject>
#include <QVector>
#include <memory>

class Drone; // Forward declaration

#include "Drone.h" // Include Drone.h before defining Swarm

class Swarm {
public:
    Swarm(); // Add constructor declaration
    void addDrone(std::shared_ptr<Drone> drone);
    void removeDrone(const Drone* drone);
    void removeDroneAt(int index);
    void setLeader(std::shared_ptr<Drone> newLeader);
    
    const QVector<std::shared_ptr<Drone>>& getDrones() const { return m_drones; }
    QVector<std::shared_ptr<Drone>>& getDrones() { return m_drones; }
    std::shared_ptr<Drone> getLeader() const { return m_leader; }

private:
    QVector<std::shared_ptr<Drone>> m_drones;
    std::shared_ptr<Drone> m_leader;
};

class SwarmManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(Drone* leader READ getLeader NOTIFY leaderChanged)
    Q_PROPERTY(QVector<Drone*> drones READ getDrones)

public:
    explicit SwarmManager(QObject *parent = nullptr);
    virtual ~SwarmManager();

    /**
     * Swarm member operations
     */
    Q_INVOKABLE void addDrone(const QString& url); // Add a drone to the swarm
    Q_INVOKABLE void removeDrone(const Drone* drone);
    Q_INVOKABLE void removeDrone(int droneId);
    Q_INVOKABLE void setLeader(Drone *drone);
    Q_INVOKABLE void setLeader(int droneId);

    /**
     * Get the list of drones in the swarm
     */
    QVector<Drone*> getDrones() const {
        QVector<Drone*> rawDrones;
        for (const auto& drone : m_swarm.getDrones()) {
            rawDrones.append(drone.get());
        }
        return rawDrones;
    }

    /**
     * Get the leader drone
     */
    Drone* getLeader() const { return m_swarm.getLeader().get(); }

    // Add validation methods
    bool isDroneInSwarm(const Drone* drone) const;
    bool isValidDroneId(int id) const;

signals:
    void leaderChanged(Drone *leader);

private:
    Swarm m_swarm;
};

#endif // SWARM_H