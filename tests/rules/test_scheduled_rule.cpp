#include <gtest/gtest.h>
#include "rules/scheduled_rule.hpp"
#include <thread>

TEST(ScheduledRuleTest, DISABLED_ExecuteAtScheduledTime) {
    bool actionExecuted = false;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto now = std::chrono::system_clock::now();
    auto later = now + std::chrono::milliseconds(100);

    ScheduledRule rule("TestRule",
                       later,
                       [&actionExecuted]() { actionExecuted = true; },
                       false
    );

    EXPECT_FALSE(rule.checkCondition());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_TRUE(rule.checkCondition());

    rule.execute();
    EXPECT_TRUE(actionExecuted);
}

TEST(ScheduledRuleTest, MakeTimeWorks) {
    auto time = ScheduledRule::makeTime(14, 30);

    auto time_t = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::localtime(&time_t);

    EXPECT_EQ(tm.tm_hour, 14);
    EXPECT_EQ(tm.tm_min, 30);
    EXPECT_EQ(tm.tm_sec, 0);
}