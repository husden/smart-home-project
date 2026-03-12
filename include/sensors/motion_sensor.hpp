#ifndef SMARTHOME_MOTION_SENSOR_HPP
#define SMARTHOME_MOTION_SENSOR_HPP

#include "sensor.hpp"

class MotionSensor : public Sensor {
public:
    explicit MotionSensor(const std::string& name);
    std::optional<double> readValue() override;
    std::string getSensorType() const override;

    void triggerMotion();
    void clearMotion();

private:
    bool motionDetected_;
};

#endif //SMARTHOME_MOTION_SENSOR_HPP