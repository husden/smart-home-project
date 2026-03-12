#include <gtest/gtest.h>
#include "rules/condition_rule.hpp"
#include "sensors/motion_sensor.hpp"
#include <memory>

TEST(ConditionRuleTest, ConditionTrueExecutesAction) {
bool actionExecuted = false;

auto sensor = std::make_shared<MotionSensor>("TestSensor");
sensor->triggerMotion();

ConditionRule rule("TestRule",
                   [sensor]() {
                       auto val = sensor->readValue();
                       return val.has_value() && val.value() > 0.5;
                   },
                   [&actionExecuted]() { actionExecuted = true; }
);

EXPECT_TRUE(rule.checkCondition());
rule.execute();
EXPECT_TRUE(actionExecuted);
}

TEST(ConditionRuleTest, ConditionFalseDoesNotExecute) {
bool actionExecuted = false;

auto sensor = std::make_shared<MotionSensor>("TestSensor");
sensor->clearMotion();

ConditionRule rule("TestRule",
                   [sensor]() {
                       auto val = sensor->readValue();
                       return val.has_value() && val.value() > 0.5;
                   },
                   [&actionExecuted]() { actionExecuted = true; }
);

EXPECT_FALSE(rule.checkCondition());
rule.execute();
EXPECT_FALSE(actionExecuted);
}