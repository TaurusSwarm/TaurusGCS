#include "Drone.h"
#include "Telemetry.h"
#include <mavsdk/mavsdk.h>
#include <QMutex>
#include <QThread>

Drone::Drone(QObject *parent, std::shared_ptr<mavsdk::Mavsdk> mavsdk, int droneId, bool isLeader)
    : QObject(parent), m_mavsdk(mavsdk), m_droneId(droneId), m_isLeader(isLeader)
{
    if (m_mavsdk == nullptr) {
        qWarning() << "Mavsdk instance is null.";
        return;
    }

    // Wait for system discovery with timeout
    int retryCount = 0;
    const int maxRetries = 10;
    const int retryDelay = 500; // ms

    while (retryCount < maxRetries) {
        auto maybe_system = m_mavsdk->first_autopilot(0.5); // Short timeout for each try
        
        if (maybe_system.has_value()) {
            m_system = maybe_system.value();
            
            if (m_system && m_system->is_connected()) {
                qDebug() << "System discovered and connected.";
                break;
            }
        }
        
        QThread::msleep(retryDelay);
        retryCount++;
        qDebug() << "Waiting for system connection, attempt" << retryCount;
    }

    if (!m_system || !m_system->is_connected()) {
        qWarning() << "Failed to connect to system after" << maxRetries << "attempts";
        return;
    }

    // Create Telemetry object only after ensuring system is connected
    m_telemetry = std::make_unique<Telemetry>(this, m_system);

    if (!m_telemetry) {
        qWarning() << "Failed to create telemetry object.";
        return;
    }
}

Drone::~Drone()
{
    m_telemetry.reset();
    m_system.reset();
    m_mavsdk.reset();
}

void Drone::setLeader(bool leader)
{
    m_isLeader = leader;
}

bool Drone::isLeader() const
{
    return m_isLeader;
}

TelemetryDataQML Drone::getTelemetryData() const {
    TelemetryDataQML data;

    if (m_telemetry && m_system) {
        const auto& telemetryData = m_telemetry->data();

        data.setLatitude(telemetryData.m_position.latitude_deg);
        data.setLongitude(telemetryData.m_position.longitude_deg);
        data.setAltitudeMeters(telemetryData.m_altitude.altitude_relative_m);
        data.setVelocityNorthMS(telemetryData.m_velocityNed.north_m_s);
        data.setVelocityEastMS(telemetryData.m_velocityNed.east_m_s);
        data.setVelocityDownMS(telemetryData.m_velocityNed.down_m_s);
        data.setBatteryVoltageV(telemetryData.m_battery.voltage_v);
        data.setBatteryRemaining(telemetryData.m_battery.remaining_percent);
        data.setGpsNumSatellites(telemetryData.m_gpsInfo.num_satellites);
    }

    return data;
}

bool Drone::arm()
{
    if (!m_system) return false;
    auto action = mavsdk::Action{m_system};
    return action.arm() == mavsdk::Action::Result::Success;
}

bool Drone::disarm()
{
    if (!m_system) return false;
    auto action = mavsdk::Action{m_system};
    return action.disarm() == mavsdk::Action::Result::Success;
}

bool Drone::takeoff()
{
    if (!m_system) return false;
    auto action = mavsdk::Action{m_system};
    return action.takeoff() == mavsdk::Action::Result::Success;
}

bool Drone::land()
{
    if (!m_system) return false;
    auto action = mavsdk::Action{m_system};
    return action.land() == mavsdk::Action::Result::Success;
}

void Drone::onTelemetryUpdate(const TelemetryDataQML& data)
{
    emit telemetryDataChanged(data);
}