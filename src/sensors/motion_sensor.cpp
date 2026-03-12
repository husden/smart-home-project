#include "sensors/motion_sensor.hpp"

MotionSensor::MotionSensor(const std::string& name)
    : Sensor(name), motionDetected_(false) {}

std::optional<double> MotionSensor::readValue() {
    if (!isOperational()) {
        return std::nullopt;
    }
    return motionDetected_ ? 1.0 : 0.0;
}

std::string MotionSensor::getSensorType() const { return "Motion"; }

void MotionSensor::triggerMotion() { motionDetected_ = true; }
void MotionSensor::clearMotion() { motionDetected_ = false; }