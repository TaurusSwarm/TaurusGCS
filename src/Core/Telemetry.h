#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMap>
#include <QDateTime>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <memory>

struct TelemetryData {
    mavsdk::Telemetry::AccelerationFrd m_accelerationFrd;
    mavsdk::Telemetry::ActuatorControlTarget m_actuatorControlTarget;
    mavsdk::Telemetry::ActuatorOutputStatus m_actuatorOutputStatus;
    mavsdk::Telemetry::Altitude m_altitude;
    mavsdk::Telemetry::AngularVelocityBody m_angularVelocityBody;
    mavsdk::Telemetry::AngularVelocityFrd m_angularVelocityFrd;
    mavsdk::Telemetry::Battery m_battery;
    mavsdk::Telemetry::Covariance m_covariance;
    mavsdk::Telemetry::DistanceSensor m_distanceSensor;
    mavsdk::Telemetry::EulerAngle m_eulerAngle;
    mavsdk::Telemetry::FixedwingMetrics m_fixedwingMetrics;
    mavsdk::Telemetry::GpsGlobalOrigin m_gpsGlobalOrigin;
    mavsdk::Telemetry::GpsInfo m_gpsInfo;
    mavsdk::Telemetry::GroundTruth m_groundTruth;
    mavsdk::Telemetry::Heading m_heading;
    mavsdk::Telemetry::Health m_health;
    mavsdk::Telemetry::Imu m_imu;
    mavsdk::Telemetry::MagneticFieldFrd m_magneticFieldFrd;
    mavsdk::Telemetry::Odometry m_odometry;
    mavsdk::Telemetry::Position m_position;
    mavsdk::Telemetry::PositionBody m_positionBody;
    mavsdk::Telemetry::PositionNed m_positionNed;
    mavsdk::Telemetry::PositionVelocityNed m_positionVelocityNed;
    mavsdk::Telemetry::Quaternion m_quaternion;
    mavsdk::Telemetry::RawGps m_rawGps;
    mavsdk::Telemetry::RcStatus m_rcStatus;
    mavsdk::Telemetry::ScaledPressure m_scaledPressure;
    mavsdk::Telemetry::StatusText m_statusText;
    mavsdk::Telemetry::VelocityBody m_velocityBody;
    mavsdk::Telemetry::VelocityNed m_velocityNed;
    mavsdk::Telemetry::FlightMode m_flightMode;
    bool m_inAir;
    mavsdk::Telemetry::LandedState m_landedState;
    bool m_armed;
    mavsdk::Telemetry::VtolState m_vtolState;
    bool m_healthAllOk;
    uint64_t m_unixEpochTime;
    mavsdk::Telemetry::Position m_homePosition;
    mavsdk::Telemetry::Imu m_scaledImu;
    mavsdk::Telemetry::Imu m_rawImu;
};

/**
 * Handles telemetry data collection and management
 */
class Telemetry : public QObject {
    Q_OBJECT

public:

    explicit Telemetry(QObject *parent = nullptr, std::shared_ptr<mavsdk::System> system = nullptr);
    ~Telemetry();

    const TelemetryData& data() const { return m_telemetry_data; }
    bool isHealthy() const;

signals:
    void telemetryError(const QString& error);
    void positionChanged(const mavsdk::Telemetry::Position& position);
    void homePositionChanged(const mavsdk::Telemetry::Position& homePosition);
    void inAirChanged(bool inAir);
    void landedStateChanged(mavsdk::Telemetry::LandedState landedState);
    void armedChanged(bool armed);
    void vtolStateChanged(mavsdk::Telemetry::VtolState vtolState);
    void quaternionChanged(const mavsdk::Telemetry::Quaternion& quaternion);
    void eulerAngleChanged(const mavsdk::Telemetry::EulerAngle& eulerAngle);
    void angularVelocityBodyChanged(const mavsdk::Telemetry::AngularVelocityBody& angularVelocityBody);
    void velocityNedChanged(const mavsdk::Telemetry::VelocityNed& velocityNed);
    void gpsInfoChanged(const mavsdk::Telemetry::GpsInfo& gpsInfo);
    void rawGpsChanged(const mavsdk::Telemetry::RawGps& rawGps);
    void batteryChanged(const mavsdk::Telemetry::Battery& battery);
    void flightModeChanged(mavsdk::Telemetry::FlightMode flightMode);
    void healthChanged(const mavsdk::Telemetry::Health& health);
    void rcStatusChanged(const mavsdk::Telemetry::RcStatus& rcStatus);
    void statusTextChanged(const mavsdk::Telemetry::StatusText& statusText);
    void actuatorControlTargetChanged(const mavsdk::Telemetry::ActuatorControlTarget& actuatorControlTarget);
    void actuatorOutputStatusChanged(const mavsdk::Telemetry::ActuatorOutputStatus& actuatorOutputStatus);
    void odometryChanged(const mavsdk::Telemetry::Odometry& odometry);
    void positionVelocityNedChanged(const mavsdk::Telemetry::PositionVelocityNed& positionVelocityNed);
    void groundTruthChanged(const mavsdk::Telemetry::GroundTruth& groundTruth);
    void fixedwingMetricsChanged(const mavsdk::Telemetry::FixedwingMetrics& fixedwingMetrics);
    void imuChanged(const mavsdk::Telemetry::Imu& imu);
    void scaledImuChanged(const mavsdk::Telemetry::Imu& scaledImu);
    void rawImuChanged(const mavsdk::Telemetry::Imu& rawImu);
    void healthAllOkChanged(bool healthAllOk);
    void unixEpochTimeChanged(uint64_t unixEpochTime);
    void distanceSensorChanged(const mavsdk::Telemetry::DistanceSensor& distanceSensor);
    void scaledPressureChanged(const mavsdk::Telemetry::ScaledPressure& scaledPressure);
    void headingChanged(const mavsdk::Telemetry::Heading& heading);
    void altitudeChanged(const mavsdk::Telemetry::Altitude& altitude);

private:
    std::weak_ptr<mavsdk::System> m_system;
    std::shared_ptr<mavsdk::Telemetry> m_telemetry;
    
    TelemetryData m_telemetry_data;

    QTimer m_stalenessTimer;
    QMap<QString, QDateTime> m_lastUpdateTimes;
    
    void startTelemetry();
    void checkTelemetryStaleness();
    void updateLastUpdateTime(const QString& telemetryField);
    bool isTelemetryStaleHelper(int stalenessThreshold) const;
    
    // Callbacks
    mavsdk::Telemetry::PositionCallback m_position_callback;
    mavsdk::Telemetry::PositionCallback m_home_position_callback;
    mavsdk::Telemetry::InAirCallback m_in_air_callback;
    mavsdk::Telemetry::LandedStateCallback m_landed_state_callback;
    mavsdk::Telemetry::ArmedCallback m_armed_callback;
    mavsdk::Telemetry::VtolStateCallback m_vtol_state_callback;
    mavsdk::Telemetry::AttitudeQuaternionCallback m_quaternion_callback;
    mavsdk::Telemetry::AttitudeEulerCallback m_euler_angle_callback;
    mavsdk::Telemetry::AttitudeAngularVelocityBodyCallback m_angular_velocity_body_callback;
    mavsdk::Telemetry::VelocityNedCallback m_velocity_ned_callback;
    mavsdk::Telemetry::GpsInfoCallback m_gps_info_callback;
    mavsdk::Telemetry::RawGpsCallback m_raw_gps_callback;
    mavsdk::Telemetry::BatteryCallback m_battery_callback;
    mavsdk::Telemetry::FlightModeCallback m_flight_mode_callback;
    mavsdk::Telemetry::HealthCallback m_health_callback;
    mavsdk::Telemetry::RcStatusCallback m_rc_status_callback;
    mavsdk::Telemetry::StatusTextCallback m_status_text_callback;
    mavsdk::Telemetry::ActuatorControlTargetCallback m_actuator_control_target_callback;
    mavsdk::Telemetry::ActuatorOutputStatusCallback m_actuator_output_status_callback;
    mavsdk::Telemetry::OdometryCallback m_odometry_callback;
    mavsdk::Telemetry::PositionVelocityNedCallback m_position_velocity_ned_callback;
    mavsdk::Telemetry::GroundTruthCallback m_ground_truth_callback;
    mavsdk::Telemetry::FixedwingMetricsCallback m_fixedwing_metrics_callback;
    mavsdk::Telemetry::ImuCallback m_imu_callback;
    mavsdk::Telemetry::ImuCallback m_scaled_imu_callback;
    mavsdk::Telemetry::ImuCallback m_raw_imu_callback;
    mavsdk::Telemetry::HealthAllOkCallback m_health_all_ok_callback;
    mavsdk::Telemetry::UnixEpochTimeCallback m_unix_epoch_time_callback;
    mavsdk::Telemetry::DistanceSensorCallback m_distance_sensor_callback;
    mavsdk::Telemetry::ScaledPressureCallback m_scaled_pressure_callback;
    mavsdk::Telemetry::HeadingCallback m_heading_callback;
    mavsdk::Telemetry::AltitudeCallback m_altitude_callback;

    // Handles
    mavsdk::Telemetry::PositionHandle m_position_handle;
    mavsdk::Telemetry::PositionHandle m_home_position_handle;
    mavsdk::Telemetry::InAirHandle m_in_air_handle;
    mavsdk::Telemetry::LandedStateHandle m_landed_state_handle;
    mavsdk::Telemetry::ArmedHandle m_armed_handle;
    mavsdk::Telemetry::VtolStateHandle m_vtol_state_handle;
    mavsdk::Telemetry::AttitudeQuaternionHandle m_quaternion_handle;
    mavsdk::Telemetry::AttitudeEulerHandle m_euler_angle_handle;
    mavsdk::Telemetry::AttitudeAngularVelocityBodyHandle m_angular_velocity_body_handle;
    mavsdk::Telemetry::VelocityNedHandle m_velocity_ned_handle;
    mavsdk::Telemetry::GpsInfoHandle m_gps_info_handle;
    mavsdk::Telemetry::RawGpsHandle m_raw_gps_handle;
    mavsdk::Telemetry::BatteryHandle m_battery_handle;
    mavsdk::Telemetry::FlightModeHandle m_flight_mode_handle;
    mavsdk::Telemetry::HealthHandle m_health_handle;
    mavsdk::Telemetry::RcStatusHandle m_rc_status_handle;
    mavsdk::Telemetry::StatusTextHandle m_status_text_handle;
    mavsdk::Telemetry::ActuatorControlTargetHandle m_actuator_control_target_handle;
    mavsdk::Telemetry::ActuatorOutputStatusHandle m_actuator_output_status_handle;
    mavsdk::Telemetry::OdometryHandle m_odometry_handle;
    mavsdk::Telemetry::PositionVelocityNedHandle m_position_velocity_ned_handle;
    mavsdk::Telemetry::GroundTruthHandle m_ground_truth_handle;
    mavsdk::Telemetry::FixedwingMetricsHandle m_fixedwing_metrics_handle;
    mavsdk::Telemetry::ImuHandle m_imu_handle;
    mavsdk::Telemetry::ImuHandle m_scaled_imu_handle;
    mavsdk::Telemetry::ImuHandle m_raw_imu_handle;
    mavsdk::Telemetry::HealthAllOkHandle m_health_all_ok_handle;
    mavsdk::Telemetry::UnixEpochTimeHandle m_unix_epoch_time_handle;
    mavsdk::Telemetry::DistanceSensorHandle m_distance_sensor_handle;
    mavsdk::Telemetry::ScaledPressureHandle m_scaled_pressure_handle;
    mavsdk::Telemetry::HeadingHandle m_heading_handle;
    mavsdk::Telemetry::AltitudeHandle m_altitude_handle;
};

#endif // TELEMETRY_H