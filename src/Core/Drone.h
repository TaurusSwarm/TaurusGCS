#pragma once

#ifndef DRONE_H
#define DRONE_H

#include <QObject>
#include <memory>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
class Telemetry;

// Move to separate header
struct TelemetryDataQML {
    // Add constructor and validation
    TelemetryDataQML() : latitude(0), longitude(0), altitude_meters(0) /* ... */ {}
    
    bool isValid() const {
        return latitude != 0 || longitude != 0;
    }

    // Make members private with accessors
private:
    double latitude;
    double longitude;
    float altitude_meters;
    float velocity_north_m_s;
    float velocity_east_m_s;
    float velocity_down_m_s;
    float battery_voltage_v;
    float battery_remaining;
    int gps_num_satellites;

public:
    double getLatitude() const { return latitude; }
    void setLatitude(double val) { latitude = val; }
    double getLongitude() const { return longitude; }
    void setLongitude(double val) { longitude = val; }
    float getAltitudeMeters() const { return altitude_meters; }
    void setAltitudeMeters(float val) { altitude_meters = val; }
    float getVelocityNorthMS() const { return velocity_north_m_s; }
    void setVelocityNorthMS(float val) { velocity_north_m_s = val; }
    float getVelocityEastMS() const { return velocity_east_m_s; }
    void setVelocityEastMS(float val) { velocity_east_m_s = val; }
    float getVelocityDownMS() const { return velocity_down_m_s; }
    void setVelocityDownMS(float val) { velocity_down_m_s = val; }
    float getBatteryVoltageV() const { return battery_voltage_v; }
    void setBatteryVoltageV(float val) { battery_voltage_v = val; }
    float getBatteryRemaining() const { return battery_remaining; }
    void setBatteryRemaining(float val) { battery_remaining = val; }
    int getGpsNumSatellites() const { return gps_num_satellites; }
    void setGpsNumSatellites(int val) { gps_num_satellites = val; }
};

Q_DECLARE_METATYPE(TelemetryDataQML)

class Drone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLeader READ isLeader WRITE setLeader)
    Q_PROPERTY(int droneId READ droneId)

public:
    explicit Drone(QObject *parent = nullptr, std::shared_ptr<mavsdk::Mavsdk> mavsdk = nullptr, int droneId = -1, bool isLeader = false);
    ~Drone();

    void setLeader(bool leader);
    bool isLeader() const;
    int droneId() const { return m_droneId; }

    Q_INVOKABLE TelemetryDataQML getTelemetryData() const;

    virtual bool arm();
    virtual bool disarm();
    virtual bool takeoff();
    virtual bool land();

    bool isConnected() const;
    bool hasTelemetry() const;

signals:
    void telemetryDataChanged(const TelemetryDataQML& telemetryData);

protected:
    virtual void onTelemetryUpdate(const TelemetryDataQML& data);

private:
    Drone(const Drone&) = delete;
    Drone& operator=(const Drone&) = delete;

    std::shared_ptr<mavsdk::Mavsdk> m_mavsdk;
    std::shared_ptr<mavsdk::System> m_system;
    std::unique_ptr<Telemetry> m_telemetry;

    int m_droneId;
    bool m_isLeader;
};

#endif // DRONE_H