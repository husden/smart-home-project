
#ifndef SMART_HOME_PROJECT_SENSOR_HPP
#define SMART_HOME_PROJECT_SENSOR_HPP

#include <string>
#include <optional>

#include "../exceptions/exceptions.hpp"
class Sensor {
private:
    std::string name_;
    bool isOperational_;
public:
    virtual ~Sensor() = default;
    virtual std::optional<double> readValue() = 0;
    virtual std::string getSensorType() const = 0;
    virtual std::string getName() const = 0;

    bool isOperational() const { return isOperational_; }
protected:
    explicit Sensor(std::string name)
    : name_(std::move(name)), isOperational_(true) {
        if (name_.empty()) {
            throw InvalidArgumentException("Sensor name cannot be empty");
        }
    }
};


#endif //SMART_HOME_PROJECT_SENSOR_HPP