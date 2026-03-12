#ifndef SMARTHOME_TEMPERATURE_SENSOR_HPP
#define SMARTHOME_TEMPERATURE_SENSOR_HPP


#include "sensor.hpp"

class TemperatureSensor : public Sensor {
public:
    explicit TemperatureSensor(const std::string& name);
    std::optional<double> readValue() override;
    std::string getSensorType() const override;

    std::string getName() const override { return name_; }

    void simulateReading(double value);

private:
    double simulatedTemperature_;
};

#endif //SMARTHOME_TEMPERATURE_SENSOR_HPP