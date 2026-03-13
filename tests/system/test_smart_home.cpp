#include <gtest/gtest.h>
#include "system/smart_home_system.hpp"
#include "devices/light.hpp"
#include "sensors/motion_sensor.hpp"
#include "rules/condition_rule.hpp"
#include <string>
#include <vector>

TEST(SmartHomeSystemTest, AddAndFindDevice) {
SmartHomeSystem home;

auto light = std::make_unique<Light>("TestLight");
home.addDevice(std::move(light));

auto found = home.findDevice("TestLight");
EXPECT_TRUE(found.has_value());

auto notFound = home.findDevice("NonExistent");
EXPECT_FALSE(notFound.has_value());
}

TEST(SmartHomeSystemTest, AddAndFindSensor) {
SmartHomeSystem home;

auto sensor = std::make_shared<MotionSensor>("TestSensor");
home.addSensor(sensor);

auto found = home.findSensor("TestSensor");
EXPECT_TRUE(found.has_value());
}

TEST(SmartHomeSystemTest, DISABLED_AddRule) {
SmartHomeSystem home;

auto rule = std::make_unique<ConditionRule>(
        "TestRule",
        []() { return true; },
        []() {}
);
home.addRule(std::move(rule));

EXPECT_EQ(home.getRuleCount(), 1);
}