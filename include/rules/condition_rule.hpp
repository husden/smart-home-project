#ifndef CONDITION_RULE_HPP
#define CONDITION_RULE_HPP

#include "rule.hpp"
#include <functional>
#include <memory>
#include <vector>

class Sensor;

class ConditionRule : public Rule {
private:
    std::function<bool()> condition;
    std::function<void()> action;
    std::vector<std::shared_ptr<Sensor>> relevantSensors;

public:
    ConditionRule(const std::string& name,
                  std::function<bool()> cond,
                  std::function<void()> act,
                  const std::string& desc = "");

    bool checkCondition() override;
    void execute() override;

    void addSensor(std::shared_ptr<Sensor> sensor);

    std::string toString() const override;
};

#endif