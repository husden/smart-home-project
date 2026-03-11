#include "rules/scheduled_rule.hpp"
#include <iostream>

ScheduledRule::ScheduledRule(const std::string& name,
                             std::chrono::system_clock::time_point time,
                             std::function<void()> act,
                             bool repeat,
                             const std::string& desc)
        : Rule(name, desc), scheduledTime(time), action(act), repeatDaily(repeat) {}

bool ScheduledRule::checkCondition() {
    if (!isActive) return false;

    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - scheduledTime);

    return diff.count() >= 0 && diff.count() < 1;
}

void ScheduledRule::execute() {
    if (checkCondition()) {
        try {
            action();
            std::cout << "⏰ Scheduled rule executed: " << name << std::endl;

            if (repeatDaily) {
                scheduledTime += std::chrono::hours(24);
                std::cout << "   Next execution: " << toString() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "❌ Error executing scheduled rule " << name << ": " << e.what() << std::endl;
        }
    }
}

void ScheduledRule::setTime(std::chrono::system_clock::time_point time) {
    scheduledTime = time;
}

std::string ScheduledRule::toString() const {
    auto time_t = std::chrono::system_clock::to_time_t(scheduledTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");

    return "ScheduledRule: " + name + " at " + ss.str() +
           " (repeat: " + (repeatDaily ? "daily" : "once") + ")";
}

std::chrono::system_clock::time_point ScheduledRule::makeTime(int hours, int minutes, int seconds) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time_t);

    tm.tm_hour = hours;
    tm.tm_min = minutes;
    tm.tm_sec = seconds;

    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}