#include "sensors/temperature_sensor.hpp"
#include <cstdlib>

TemperatureSensor::TemperatureSensor(const std::string& name)
    : Sensor(name), simulatedTemperature_(22.0) {}

std::optional<double> TemperatureSensor::readValue() {
    if (!isOperational()) {
        return std::nullopt;
    }

    simulatedTemperature_ += (static_cast<double>(rand()) / RAND_MAX - 0.5);
    if (simulatedTemperature_ < 15.0) simulatedTemperature_ = 15.0;
    if (simulatedTemperature_ > 35.0) simulatedTemperature_ = 35.0;
    return simulatedTemperature_;
}

std::string TemperatureSensor::getSensorType() const { return "Temperature"; }

void TemperatureSensor::simulateReading(double value) {
    simulatedTemperature_ = value;
}