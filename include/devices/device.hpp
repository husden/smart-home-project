#ifndef SMART_HOME_PROJECT_DEVICE_HPP
#define SMART_HOME_PROJECT_DEVICE_HPP

#include <string>
#include "exceptions/exceptions.hpp"

class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatus() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;

    bool isOn() const { return isOn_; }
    bool isActive() const { return isOn_; }

    static constexpr int MIN_BRIGHTNESS = 0;
    static constexpr int MAX_BRIGHTNESS = 100;
    static constexpr double MIN_TEMPERATURE = 5.0;
    static constexpr double MAX_TEMPERATURE = 35.0;

protected:
    explicit Device(std::string name) : name_(std::move(name)), isOn_(false) {
        if (name_.empty()){
        throw InvalidArgumentException("Device name cannot be empty");
        }
    }
    std::string name_;
    bool isOn_;

};

#endif //SMART_HOME_PROJECT_DEVICE_HPP