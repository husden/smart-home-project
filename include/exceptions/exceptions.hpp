#ifndef SMART_HOME_PROJECT_EXCEPTIONS_HPP
#define SMART_HOME_PROJECT_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class SmartHomeException : public std::runtime_error {
public:
    explicit SmartHomeException(const std::string& message)
        : std::runtime_error(message){}
};

class DeviceException : public SmartHomeException {
public:
    explicit DeviceException(const std::string& message)
        : SmartHomeException("Device error: " + message) {}
};

class DeviceNotFoundException : public DeviceException {
public:
    explicit DeviceNotFoundException(const std::string& deviceName)
        : DeviceException("Device '" + deviceName + "' not found") {}
};

class DeviceOfflineException : public DeviceException {
public:
    explicit DeviceOfflineException(const std::string& deviceName)
    : DeviceException("Device '" + deviceName + "' is offline") {}
};


class InvalidArgumentException: public SmartHomeException {
public:
    explicit InvalidArgumentException(const std::string& argumentName)
        : SmartHomeException("Invalid argument: " + argumentName) {}
};

class SensorException : public SmartHomeException {
public:
    explicit SensorException(const std::string& message)
        :SmartHomeException("Sensor error: " + message){}
};

class SensorBrokenException : public SensorException {
public:
    explicit SensorBrokenException(const std::string& sensorName)
        : SensorException("Sensor '" + sensorName + "' is broken") {}
};

class CommandException : public SmartHomeException {
public:
    explicit CommandException(const std::string& commandName)
            : SmartHomeException("Unknown command: '" + commandName + "'") {}
};

#endif