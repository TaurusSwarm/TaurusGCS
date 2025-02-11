#include "SwarmManager.h"
#include "Drone.h"
#include <QDebug>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <QThread>

SwarmManager::SwarmManager(QObject *parent) : QObject(parent) {
    m_swarm.setLeader(nullptr);
}

SwarmManager::~SwarmManager() {
    // Nothing needed here since Swarm manages its own cleanup
}

bool SwarmManager::isDroneInSwarm(const Drone* drone) const {
    for (const auto& d : m_swarm.getDrones()) {
        if (d.get() == drone) return true;
    }
    return false;
}

bool SwarmManager::isValidDroneId(int id) const {
    return id >= 0 && id < m_swarm.getDrones().size();
}

void SwarmManager::addDrone(const QString& url) {
    auto config = mavsdk::Mavsdk::Configuration(mavsdk::ComponentType::GroundStation);
    auto mavsdk = std::make_shared<mavsdk::Mavsdk>(config);
        
    if (mavsdk->add_any_connection(url.toStdString()) != mavsdk::ConnectionResult::Success) {
        return;
    }

    Drone *drone = new Drone(nullptr, mavsdk, (int)m_swarm.getDrones().size(), false);
    m_swarm.addDrone(std::shared_ptr<Drone>(drone));
}

void SwarmManager::removeDrone(const Drone* drone) {
    auto& drones = m_swarm.getDrones();
    for (int i = 0; i < drones.size(); ++i) {
        if (drones[i].get() == drone) {
            if (m_swarm.getLeader().get() == drones[i].get()) {
                m_swarm.setLeader(nullptr);
                emit leaderChanged(nullptr);
            }
            m_swarm.removeDroneAt(i);
            return;
        }
    }
}

void SwarmManager::removeDrone(int droneId) {
    auto& drones = m_swarm.getDrones();
    for (int i = 0; i < drones.size(); ++i) {
        if (drones[i]->droneId() == droneId) {
            if (m_swarm.getLeader().get() == drones[i].get()) {
                m_swarm.setLeader(nullptr);
                emit leaderChanged(nullptr);
            }
            m_swarm.removeDroneAt(i);
            return;
        }
    }
}

void SwarmManager::setLeader(Drone* drone) {
    for (const auto& swarmDrone : m_swarm.getDrones()) {
        if (swarmDrone.get() == drone) {
            m_swarm.setLeader(swarmDrone);
            emit leaderChanged(drone);
            return;
        }
    }
    qWarning() << "Drone is not in the swarm. Cannot set as leader.";
}

void SwarmManager::setLeader(int droneId) {
    for (const auto& drone : m_swarm.getDrones()) {
        if (drone->droneId() == droneId) {
            setLeader(drone.get());
            return;
        }
    }
    qWarning() << "Drone with ID " << droneId << " not found in the swarm.";
}
