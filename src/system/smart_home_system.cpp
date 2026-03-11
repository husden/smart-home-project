#include "system/smart_home_system.hpp"
#include "devices/device.hpp"
#include "sensors/sensor.hpp"
#include "rules/rule.hpp"
#include <algorithm>
#include <iostream>

void SmartHomeSystem::addDevice(std::unique_ptr<Device> device) {
    if (device) {
        std::cout << "➕ Adding device: " << device->getName() << std::endl;
        devices.push_back(std::move(device));
    }
}

void SmartHomeSystem::addSensor(std::shared_ptr<Sensor> sensor) {
    if (sensor) {
        std::cout << "➕ Adding sensor: " << sensor->getName() << std::endl;
        sensors.push_back(sensor);
    }
}

void SmartHomeSystem::addRule(std::unique_ptr<Rule> rule) {
    if (rule) {
        std::cout << "➕ Adding rule: " << rule->getName() << std::endl;
        rules.push_back(std::move(rule));
    }
}

std::optional<Device*> SmartHomeSystem::findDevice(const std::string& name) {
    auto it = std::find_if(devices.begin(), devices.end(),
                           [&name](const auto& d) { return d->getName() == name; });

    if (it != devices.end()) {
        return it->get();
    }
    return std::nullopt;
}

std::optional<std::shared_ptr<Sensor>> SmartHomeSystem::findSensor(const std::string& name) {
    auto it = std::find_if(sensors.begin(), sensors.end(),
                           [&name](const auto& s) { return s->getName() == name; });

    if (it != sensors.end()) {
        return *it;
    }
    return std::nullopt;
}

void SmartHomeSystem::removeDevice(const std::string& name) {
    auto it = std::find_if(devices.begin(), devices.end(),
                           [&name](const auto& d) { return d->getName() == name; });

    if (it != devices.end()) {
        std::cout << "➖ Removing device: " << name << std::endl;
        devices.erase(it);
    }
}

void SmartHomeSystem::removeRule(const std::string& name) {
    auto it = std::find_if(rules.begin(), rules.end(),
                           [&name](const auto& r) { return r->getName() == name; });

    if (it != rules.end()) {
        std::cout << "➖ Removing rule: " << name << std::endl;
        rules.erase(it);
    }
}

void SmartHomeSystem::updateSensors() {
    for (auto& sensor : sensors) {
        try {
            sensor->readValue();
        } catch (const std::exception& e) {
            std::cerr << "❌ Sensor error " << sensor->getName() << ": " << e.what() << std::endl;
        }
    }
}

void SmartHomeSystem::executeRules() {
    for (auto& rule : rules) {
        if (!rule->isActiveRule()) continue;

        try {
            if (rule->checkCondition()) {
                rule->execute();
            }
        } catch (const std::exception& e) {
            std::cerr << "❌ Rule error " << rule->getName() << ": " << e.what() << std::endl;
        }
    }
}

void SmartHomeSystem::run() {
    std::cout << "\n⚙️ Smart Home System running..." << std::endl;
    updateSensors();
    executeRules();
}

void SmartHomeSystem::printStatus() const {
    std::cout << "\n🏠 === Smart Home Status ===" << std::endl;
    std::cout << "📦 Devices: " << devices.size() << std::endl;
    for (const auto& d : devices) {
        std::cout << "   • " << d->getName() << " [" << (d->isActive() ? "ON" : "OFF") << "]" << std::endl;
    }

    std::cout << "📡 Sensors: " << sensors.size() << std::endl;
    for (const auto& s : sensors) {
        std::cout << "   • " << s->getName() << " = " << s->getValue() << std::endl;
    }

    std::cout << "📋 Rules: " << rules.size() << std::endl;
    for (const auto& r : rules) {
        std::cout << "   • " << r->getName() << (r->isActiveRule() ? " (active)" : " (inactive)") << std::endl;
    }
}