#ifndef SMART_HOME_SYSTEM_HPP
#define SMART_HOME_SYSTEM_HPP

#include <memory>
#include <vector>
#include <optional>
#include <string>

class Device;
class Sensor;
class Rule;

class SmartHomeSystem {
private:
    std::vector<std::unique_ptr<Device>> devices;
    std::vector<std::shared_ptr<Sensor>> sensors;
    std::vector<std::unique_ptr<Rule>> rules;

public:
    SmartHomeSystem() = default;
    ~SmartHomeSystem() = default;

    void addDevice(std::unique_ptr<Device> device);
    std::optional<Device*> findDevice(const std::string& name);
    void removeDevice(const std::string& name);

    void addSensor(std::shared_ptr<Sensor> sensor);
    std::optional<std::shared_ptr<Sensor>> findSensor(const std::string& name);

    void addRule(std::unique_ptr<Rule> rule);
    void removeRule(const std::string& name);

    void run();
    void printStatus() const;
    void updateSensors();
    void executeRules();

    size_t getDeviceCount() const { return devices.size(); }
    size_t getSensorCount() const { return sensors.size(); }
    size_t getRuleCount() const { return rules.size(); }
};

#endif