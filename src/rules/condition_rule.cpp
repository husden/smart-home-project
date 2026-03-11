#include "rules/condition_rule.hpp"
#include "sensors/sensor.hpp"
#include <iostream>

ConditionRule::ConditionRule(const std::string& name,
                             std::function<bool()> cond,
                             std::function<void()> act,
                             const std::string& desc)
        : Rule(name, desc), condition(cond), action(act) {}

bool ConditionRule::checkCondition() {
    if (!isActive) return false;

    try {
        return condition();
    } catch (const std::exception& e) {
        std::cerr << "Error in condition for rule " << name << ": " << e.what() << std::endl;
        return false;
    }
}

void ConditionRule::execute() {
    if (checkCondition()) {
        try {
            action();
            std::cout << "✅ Rule executed: " << name << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "❌ Error executing rule " << name << ": " << e.what() << std::endl;
        }
    }
}

void ConditionRule::addSensor(std::shared_ptr<Sensor> sensor) {
    relevantSensors.push_back(sensor);
}

std::string ConditionRule::toString() const {
    return "ConditionRule: " + name + " (active: " + (isActive ? "yes" : "no") + ")";
}