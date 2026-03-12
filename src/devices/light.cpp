#include "devices/light.hpp"
#include "exceptions/exceptions.hpp"

Light::Light(const std::string& name)
    : Device(name), brightness_(0) {}
void Light::turnOn() {
    isOn_ = true;
    brightness_ = 50;
}

void Light::turnOff() {
    isOn_ = false;
    brightness_ = 0;
}

std::string Light::getStatus() const {
    if (isOn_) {
        return "Light is ON at " + std::to_string(brightness_) + "%";
    }else {
        return "Light is OFF";
    }
}

std::string Light::getType() const {
    return "Light";
}

void Light::setBrightness(int level) {
    if (level < MIN_BRIGHTNESS || level > MAX_BRIGHTNESS) {
        throw InvalidArgumentException("Brightness out of range");
    }
    brightness_ = level;
}