
#ifndef SMART_HOME_PROJECT_THERMOSTAT_HPP
#define SMART_HOME_PROJECT_THERMOSTAT_HPP

#include "device.hpp"

class Thermostat : public Device {
public:
    explicit Thermostat(const std::string& name);

    void turnOn() override;
    void turnOff() override;
    std::string getStatus() const override;
    std::string getType() const override;

    void setTargetTemperature(double temp);
    double getTargetTemperature() const { return targetTemperature_; }

private:
    double targetTemperature_;
};

#endif //SMART_HOME_PROJECT_THERMOSTAT_HPP