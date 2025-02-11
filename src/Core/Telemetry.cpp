#include <QTimer>
#include <QDebug>
#include "Telemetry.h"

Telemetry::Telemetry(QObject *parent, std::shared_ptr<mavsdk::System> system)
    : QObject(parent), m_system(system)
{
    if (system == nullptr)
    {
        qWarning() << "System pointer is null.";
        return;
    }

    m_telemetry = std::make_shared<mavsdk::Telemetry>(system);

    if (m_telemetry == nullptr)
    {
        qWarning() << "Failed to create telemetry object.";
        return;
    }

    // Initialize last update times for each telemetry field
    m_lastUpdateTimes["position"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["homePosition"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["inAir"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["landedState"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["armed"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["vtolState"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["quaternion"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["eulerAngle"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["angularVelocityBody"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["velocityNed"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["gpsInfo"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["rawGps"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["battery"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["flightMode"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["health"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["rcStatus"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["statusText"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["actuatorControlTarget"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["actuatorOutputStatus"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["odometry"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["positionVelocityNed"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["groundTruth"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["fixedwingMetrics"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["imu"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["scaledImu"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["rawImu"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["healthAllOk"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["unixEpochTime"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["distanceSensor"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["scaledPressure"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["heading"] = QDateTime::currentDateTime();
    m_lastUpdateTimes["altitude"] = QDateTime::currentDateTime();

    // Initialize callbacks
    m_position_callback = [this](mavsdk::Telemetry::Position position) {
        m_telemetry_data.m_position = position;
        emit positionChanged(position);
        updateLastUpdateTime("position");
    };

    m_home_position_callback = [this](mavsdk::Telemetry::Position home_position) {
        m_telemetry_data.m_homePosition = home_position;
        emit homePositionChanged(home_position);
        updateLastUpdateTime("homePosition");
    };

    m_in_air_callback = [this](bool in_air) {
        m_telemetry_data.m_inAir = in_air;
        emit inAirChanged(in_air);
        updateLastUpdateTime("inAir");
    };

    m_landed_state_callback = [this](mavsdk::Telemetry::LandedState landed_state) {
        m_telemetry_data.m_landedState = landed_state;
        emit landedStateChanged(landed_state);
        updateLastUpdateTime("landedState");
    };

    m_armed_callback = [this](bool armed) {
        m_telemetry_data.m_armed = armed;
        emit armedChanged(armed);
        updateLastUpdateTime("armed");
    };

    m_vtol_state_callback = [this](mavsdk::Telemetry::VtolState vtol_state) {
        m_telemetry_data.m_vtolState = vtol_state;
        emit vtolStateChanged(vtol_state);
        updateLastUpdateTime("vtolState");
    };

    m_quaternion_callback = [this](mavsdk::Telemetry::Quaternion quaternion) {
        m_telemetry_data.m_quaternion = quaternion;
        emit quaternionChanged(quaternion);
        updateLastUpdateTime("quaternion");
    };

    m_euler_angle_callback = [this](mavsdk::Telemetry::EulerAngle euler_angle) {
        m_telemetry_data.m_eulerAngle = euler_angle;
        emit eulerAngleChanged(euler_angle);
        updateLastUpdateTime("eulerAngle");
    };

    m_angular_velocity_body_callback = [this](mavsdk::Telemetry::AngularVelocityBody angular_velocity_body) {
        m_telemetry_data.m_angularVelocityBody = angular_velocity_body;
        emit angularVelocityBodyChanged(angular_velocity_body);
        updateLastUpdateTime("angularVelocityBody");
    };

    m_velocity_ned_callback = [this](mavsdk::Telemetry::VelocityNed velocity_ned) {
        m_telemetry_data.m_velocityNed = velocity_ned;
        emit velocityNedChanged(velocity_ned);
        updateLastUpdateTime("velocityNed");
    };

    m_gps_info_callback = [this](mavsdk::Telemetry::GpsInfo gps_info) {
        m_telemetry_data.m_gpsInfo = gps_info;
        emit gpsInfoChanged(gps_info);
        updateLastUpdateTime("gpsInfo");
    };

    m_raw_gps_callback = [this](mavsdk::Telemetry::RawGps raw_gps) {
        m_telemetry_data.m_rawGps = raw_gps;
        emit rawGpsChanged(raw_gps);
        updateLastUpdateTime("rawGps");
    };

    m_battery_callback = [this](mavsdk::Telemetry::Battery battery) {
        m_telemetry_data.m_battery = battery;
        emit batteryChanged(battery);
        updateLastUpdateTime("battery");
    };

    m_flight_mode_callback = [this](mavsdk::Telemetry::FlightMode flight_mode) {
        m_telemetry_data.m_flightMode = flight_mode;
        emit flightModeChanged(flight_mode);
        updateLastUpdateTime("flightMode");
    };

    m_health_callback = [this](mavsdk::Telemetry::Health health) {
        m_telemetry_data.m_health = health;
        emit healthChanged(health);
        updateLastUpdateTime("health");
    };

    m_rc_status_callback = [this](mavsdk::Telemetry::RcStatus rc_status) {
        m_telemetry_data.m_rcStatus = rc_status;
        emit rcStatusChanged(rc_status);
        updateLastUpdateTime("rcStatus");
    };

    m_status_text_callback = [this](mavsdk::Telemetry::StatusText status_text) {
        m_telemetry_data.m_statusText = status_text;
        emit statusTextChanged(status_text);
        updateLastUpdateTime("statusText");
    };

    m_actuator_control_target_callback = [this](mavsdk::Telemetry::ActuatorControlTarget actuator_control_target) {
        m_telemetry_data.m_actuatorControlTarget = actuator_control_target;
        emit actuatorControlTargetChanged(actuator_control_target);
        updateLastUpdateTime("actuatorControlTarget");
    };

    m_actuator_output_status_callback = [this](mavsdk::Telemetry::ActuatorOutputStatus actuator_output_status) {
        m_telemetry_data.m_actuatorOutputStatus = actuator_output_status;
        emit actuatorOutputStatusChanged(actuator_output_status);
        updateLastUpdateTime("actuatorOutputStatus");
    };

    m_odometry_callback = [this](mavsdk::Telemetry::Odometry odometry) {
        m_telemetry_data.m_odometry = odometry;
        emit odometryChanged(odometry);
        updateLastUpdateTime("odometry");
    };

    m_position_velocity_ned_callback = [this](mavsdk::Telemetry::PositionVelocityNed position_velocity_ned) {
        m_telemetry_data.m_positionVelocityNed = position_velocity_ned;
        emit positionVelocityNedChanged(position_velocity_ned);
        updateLastUpdateTime("positionVelocityNed");
    };

    m_ground_truth_callback = [this](mavsdk::Telemetry::GroundTruth ground_truth) {
        m_telemetry_data.m_groundTruth = ground_truth;
        emit groundTruthChanged(ground_truth);
        updateLastUpdateTime("groundTruth");
    };

    m_fixedwing_metrics_callback = [this](mavsdk::Telemetry::FixedwingMetrics fixedwing_metrics) {
        m_telemetry_data.m_fixedwingMetrics = fixedwing_metrics;
        emit fixedwingMetricsChanged(fixedwing_metrics);
        updateLastUpdateTime("fixedwingMetrics");
    };

    m_imu_callback = [this](mavsdk::Telemetry::Imu imu) {
        m_telemetry_data.m_imu = imu;
        emit imuChanged(imu);
        updateLastUpdateTime("imu");
    };

    m_scaled_imu_callback = [this](mavsdk::Telemetry::Imu scaled_imu) {
        m_telemetry_data.m_scaledImu = scaled_imu;
        emit scaledImuChanged(scaled_imu);
        updateLastUpdateTime("scaledImu");
    };

    m_raw_imu_callback = [this](mavsdk::Telemetry::Imu raw_imu) {
        m_telemetry_data.m_rawImu = raw_imu;
        emit rawImuChanged(raw_imu);
        updateLastUpdateTime("rawImu");
    };

    m_health_all_ok_callback = [this](bool health_all_ok) {
        m_telemetry_data.m_healthAllOk = health_all_ok;
        emit healthAllOkChanged(health_all_ok);
        updateLastUpdateTime("healthAllOk");
    };

    m_unix_epoch_time_callback = [this](uint64_t unix_epoch_time) {
        m_telemetry_data.m_unixEpochTime = unix_epoch_time;
        emit unixEpochTimeChanged(unix_epoch_time);
        updateLastUpdateTime("unixEpochTime");
    };

    m_distance_sensor_callback = [this](mavsdk::Telemetry::DistanceSensor distance_sensor) {
        m_telemetry_data.m_distanceSensor = distance_sensor;
        emit distanceSensorChanged(distance_sensor);
        updateLastUpdateTime("distanceSensor");
    };

    m_scaled_pressure_callback = [this](mavsdk::Telemetry::ScaledPressure scaled_pressure) {
        m_telemetry_data.m_scaledPressure = scaled_pressure;
        emit scaledPressureChanged(scaled_pressure);
        updateLastUpdateTime("scaledPressure");
    };

    m_heading_callback = [this](mavsdk::Telemetry::Heading heading) {
        m_telemetry_data.m_heading = heading;
        emit headingChanged(heading);
        updateLastUpdateTime("heading");
    };

    m_altitude_callback = [this](mavsdk::Telemetry::Altitude altitude) {
        m_telemetry_data.m_altitude = altitude;
        emit altitudeChanged(altitude);
        updateLastUpdateTime("altitude");
    };

    startTelemetry();

    // Initialize staleness timer
    m_stalenessTimer.setInterval(1000); // Check every 1 second
    connect(&m_stalenessTimer, &QTimer::timeout, this, &Telemetry::checkTelemetryStaleness);
    m_stalenessTimer.start();
}

void Telemetry::startTelemetry()
{
    if (m_telemetry == nullptr)
    {
        qWarning() << "Telemetry object is null.";
        return;
    }

    m_telemetry->set_rate_position(1.0); 
    m_telemetry->set_rate_home(1.0); 
    m_telemetry->set_rate_in_air(1.0); 
    m_telemetry->set_rate_landed_state(1.0); 
    m_telemetry->set_rate_vtol_state(1.0); 
    m_telemetry->set_rate_attitude_quaternion(1.0); 
    m_telemetry->set_rate_attitude_euler(1.0); 
    m_telemetry->set_rate_velocity_ned(1.0); 
    m_telemetry->set_rate_gps_info(1.0); 
    m_telemetry->set_rate_battery(1.0); 
    m_telemetry->set_rate_rc_status(1.0); 
    m_telemetry->set_rate_actuator_control_target(1.0); 
    m_telemetry->set_rate_actuator_output_status(1.0); 
    m_telemetry->set_rate_odometry(1.0); 
    m_telemetry->set_rate_position_velocity_ned(1.0); 
    m_telemetry->set_rate_ground_truth(1.0);
    m_telemetry->set_rate_fixedwing_metrics(1.0); 
    m_telemetry->set_rate_imu(1.0);
    m_telemetry->set_rate_scaled_imu(1.0);
    m_telemetry->set_rate_raw_imu(1.0); 
    m_telemetry->set_rate_unix_epoch_time(1.0);
    m_telemetry->set_rate_distance_sensor(1.0);
    m_telemetry->set_rate_altitude(1.0);

    m_position_handle = m_telemetry->subscribe_position(m_position_callback);
    m_home_position_handle = m_telemetry->subscribe_home(m_home_position_callback);
    m_in_air_handle = m_telemetry->subscribe_in_air(m_in_air_callback);
    m_landed_state_handle = m_telemetry->subscribe_landed_state(m_landed_state_callback);
    m_armed_handle = m_telemetry->subscribe_armed(m_armed_callback);
    m_vtol_state_handle = m_telemetry->subscribe_vtol_state(m_vtol_state_callback);
    m_quaternion_handle = m_telemetry->subscribe_attitude_quaternion(m_quaternion_callback);
    m_euler_angle_handle = m_telemetry->subscribe_attitude_euler(m_euler_angle_callback);
    m_angular_velocity_body_handle = m_telemetry->subscribe_attitude_angular_velocity_body(m_angular_velocity_body_callback);
    m_velocity_ned_handle = m_telemetry->subscribe_velocity_ned(m_velocity_ned_callback);
    m_gps_info_handle = m_telemetry->subscribe_gps_info(m_gps_info_callback);
    m_raw_gps_handle = m_telemetry->subscribe_raw_gps(m_raw_gps_callback);
    m_battery_handle = m_telemetry->subscribe_battery(m_battery_callback);
    m_flight_mode_handle = m_telemetry->subscribe_flight_mode(m_flight_mode_callback);
    m_health_handle = m_telemetry->subscribe_health(m_health_callback);
    m_rc_status_handle = m_telemetry->subscribe_rc_status(m_rc_status_callback);
    m_status_text_handle = m_telemetry->subscribe_status_text(m_status_text_callback);
    m_actuator_control_target_handle = m_telemetry->subscribe_actuator_control_target(m_actuator_control_target_callback);
    m_actuator_output_status_handle = m_telemetry->subscribe_actuator_output_status(m_actuator_output_status_callback);
    m_odometry_handle = m_telemetry->subscribe_odometry(m_odometry_callback);
    m_position_velocity_ned_handle = m_telemetry->subscribe_position_velocity_ned(m_position_velocity_ned_callback);
    m_ground_truth_handle = m_telemetry->subscribe_ground_truth(m_ground_truth_callback);
    m_fixedwing_metrics_handle = m_telemetry->subscribe_fixedwing_metrics(m_fixedwing_metrics_callback);
    m_imu_handle = m_telemetry->subscribe_imu(m_imu_callback);
    m_scaled_imu_handle = m_telemetry->subscribe_scaled_imu(m_scaled_imu_callback);
    m_raw_imu_handle = m_telemetry->subscribe_raw_imu(m_raw_imu_callback);
    m_health_all_ok_handle = m_telemetry->subscribe_health_all_ok(m_health_all_ok_callback);
    m_unix_epoch_time_handle = m_telemetry->subscribe_unix_epoch_time(m_unix_epoch_time_callback);
    m_distance_sensor_handle = m_telemetry->subscribe_distance_sensor(m_distance_sensor_callback);
    m_scaled_pressure_handle = m_telemetry->subscribe_scaled_pressure(m_scaled_pressure_callback);
    m_heading_handle = m_telemetry->subscribe_heading(m_heading_callback);
    m_altitude_handle = m_telemetry->subscribe_altitude(m_altitude_callback);
}

Telemetry::~Telemetry()
{
    if (m_telemetry) {
        m_telemetry->unsubscribe_position(m_position_handle);
        m_telemetry->unsubscribe_home(m_home_position_handle);
        m_telemetry->unsubscribe_in_air(m_in_air_handle);
        m_telemetry->unsubscribe_landed_state(m_landed_state_handle);
        m_telemetry->unsubscribe_armed(m_armed_handle);
        m_telemetry->unsubscribe_vtol_state(m_vtol_state_handle);
        m_telemetry->unsubscribe_attitude_quaternion(m_quaternion_handle);
        m_telemetry->unsubscribe_attitude_euler(m_euler_angle_handle);
        m_telemetry->unsubscribe_attitude_angular_velocity_body(m_angular_velocity_body_handle);
        m_telemetry->unsubscribe_velocity_ned(m_velocity_ned_handle);
        m_telemetry->unsubscribe_gps_info(m_gps_info_handle);
        m_telemetry->unsubscribe_raw_gps(m_raw_gps_handle);
        m_telemetry->unsubscribe_battery(m_battery_handle);
        m_telemetry->unsubscribe_flight_mode(m_flight_mode_handle);
        m_telemetry->unsubscribe_health(m_health_handle);
        m_telemetry->unsubscribe_rc_status(m_rc_status_handle);
        m_telemetry->unsubscribe_status_text(m_status_text_handle);
        m_telemetry->unsubscribe_actuator_control_target(m_actuator_control_target_handle);
        m_telemetry->unsubscribe_actuator_output_status(m_actuator_output_status_handle);
        m_telemetry->unsubscribe_odometry(m_odometry_handle);
        m_telemetry->unsubscribe_position_velocity_ned(m_position_velocity_ned_handle);
        m_telemetry->unsubscribe_ground_truth(m_ground_truth_handle);
        m_telemetry->unsubscribe_fixedwing_metrics(m_fixedwing_metrics_handle);
        m_telemetry->unsubscribe_imu(m_imu_handle);
        m_telemetry->unsubscribe_scaled_imu(m_scaled_imu_handle);
        m_telemetry->unsubscribe_raw_imu(m_raw_imu_handle);
        m_telemetry->unsubscribe_health_all_ok(m_health_all_ok_handle);
        m_telemetry->unsubscribe_unix_epoch_time(m_unix_epoch_time_handle);
        m_telemetry->unsubscribe_distance_sensor(m_distance_sensor_handle);
        m_telemetry->unsubscribe_scaled_pressure(m_scaled_pressure_handle);
        m_telemetry->unsubscribe_heading(m_heading_handle);
        m_telemetry->unsubscribe_altitude(m_altitude_handle);
    }
}

bool Telemetry::isHealthy() const
{
    if (!m_telemetry) {
        qWarning() << "Telemetry object is null.";
        return false;
    }

    // Check if healthAllOk is true
    if (!m_telemetry_data.m_healthAllOk) {
        qWarning() << "Telemetry health is not OK.";
        return false;
    }

    // Check staleness of telemetry data
    const int stalenessThreshold = 5; // seconds

    if (isTelemetryStaleHelper(stalenessThreshold)) {
        qWarning() << "Telemetry data is stale.";
        return false;
    }

    // If all checks pass, return true
    return true;
}

void Telemetry::updateLastUpdateTime(const QString& field)
{
    if (m_lastUpdateTimes.contains(field)) {
        m_lastUpdateTimes[field] = QDateTime::currentDateTime();
    } else {
        qWarning() << "Telemetry field '" << field << "' not found in update map.";
    }
}

bool Telemetry::isTelemetryStaleHelper(int stalenessThreshold) const
{
    QDateTime currentTime = QDateTime::currentDateTime();

    for (const auto& lastUpdateTime : m_lastUpdateTimes) {
        if (lastUpdateTime.secsTo(currentTime) > stalenessThreshold) {
            return true;
        }
    }

    return false;
}

void Telemetry::checkTelemetryStaleness()
{
    const int stalenessThreshold = 5; // seconds
    QList<QString> staleFields;
    QDateTime currentTime = QDateTime::currentDateTime();

    for (auto it = m_lastUpdateTimes.begin(); it != m_lastUpdateTimes.end(); ++it) {
        if (it.value().secsTo(currentTime) > stalenessThreshold) {
            staleFields.append(it.key());
        }
    }

    if (!staleFields.isEmpty()) {
        QString errorMessage = "Telemetry data is stale for fields: " + staleFields.join(", ");
        emit telemetryError(errorMessage);
    }
}