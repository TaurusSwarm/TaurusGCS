#include "SwarmManager.h"
#include "Drone.h"

Swarm::Swarm() : m_leader(nullptr) {
    // Initialize any other members if needed
}

void Swarm::addDrone(std::shared_ptr<Drone> drone) 
{
    if (!drone) return;
    m_drones.append(drone);
}

void Swarm::removeDrone(const Drone* drone) 
{
    for (int i = 0; i < m_drones.size(); ++i) {
        if (m_drones[i].get() == drone) {
            removeDroneAt(i);
            return;
        }
    }
}

void Swarm::removeDroneAt(int index) 
{
    if (index < 0 || index >= m_drones.size()) return;
    
    if (m_leader == m_drones[index]) {
        m_leader.reset();
    }
    m_drones.removeAt(index);
}

void Swarm::setLeader(std::shared_ptr<Drone> newLeader) 
{
    // Clear existing leader status if any
    if (m_leader) {
        m_leader->setLeader(false);
    }

    m_leader = newLeader;

    // Set new leader status
    if (m_leader) {
        m_leader->setLeader(true);
    }
}
