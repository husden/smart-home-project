#ifndef SCHEDULED_RULE_HPP
#define SCHEDULED_RULE_HPP

#include "rule.hpp"
#include <chrono>
#include <functional>
#include <ctime>
#include <iomanip>
#include <sstream>

class ScheduledRule : public Rule {
private:
    std::chrono::system_clock::time_point scheduledTime;
    std::function<void()> action;
    bool repeatDaily;

public:
    ScheduledRule(const std::string& name,
                  std::chrono::system_clock::time_point time,
                  std::function<void()> act,
                  bool repeat = false,
                  const std::string& desc = "");

    bool checkCondition() override;
    void execute() override;

    void setTime(std::chrono::system_clock::time_point time);
    std::chrono::system_clock::time_point getTime() const { return scheduledTime; }

    std::string toString() const override;

    static std::chrono::system_clock::time_point makeTime(int hours, int minutes, int seconds = 0);
};

#endif