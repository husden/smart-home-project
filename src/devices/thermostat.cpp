#include "devices/thermostat.hpp"
#include "exceptions/exceptions.hpp"


Thermostat::Thermostat(const std::string& name)
    : Device(name), targetTemperature_(22.0) {}

void Thermostat::turnOn() {
    isOn_ = true;
}

void Thermostat::turnOff() {
    isOn_ = false;
}

std::string Thermostat::getStatus() const {
    if (isOn_) {
        return "Thermostat is ON, maintaining " + std::to_string(targetTemperature_) + "°C";
    } else {
        return "Thermostat is OFF";
    }
}

std::string Thermostat::getType() const {
    return "Thermostat";
}

void Thermostat::setTargetTemperature(double temp) {
    if (temp < MIN_TEMPERATURE || temp > MAX_TEMPERATURE) {
        throw InvalidArgumentException("Temperature out of range");
    }
    targetTemperature_ = temp;
}