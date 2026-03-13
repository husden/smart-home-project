#include <gtest/gtest.h>
#include "sensors/motion_sensor.hpp"
#include "sensors/temperature_sensor.hpp"


TEST(MotionSensorTest, Constructor) {
    MotionSensor sensor("TestSensor");
    EXPECT_EQ(sensor.getName(), "TestSensor");
    EXPECT_TRUE(sensor.isOperational());
    EXPECT_EQ(sensor.getSensorType(), "Motion");
}

TEST(MotionSensorTest, InitialStateNoMotion) {
    MotionSensor sensor("TestSensor");
    auto value = sensor.readValue();
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), 0.0);
}

TEST(MotionSensorTest, TriggerMotion) {
    MotionSensor sensor("TestSensor");
    sensor.triggerMotion();
    auto value = sensor.readValue();
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), 1.0);
}

TEST(MotionSensorTest, ClearMotion) {
    MotionSensor sensor("TestSensor");
    sensor.triggerMotion();
    sensor.clearMotion();
    auto value = sensor.readValue();
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), 0.0);
}

TEST(MotionSensorTest, MultipleTriggers) {
    MotionSensor sensor("TestSensor");
    sensor.triggerMotion();
    sensor.triggerMotion();
    auto value = sensor.readValue();
    EXPECT_EQ(value.value(), 1.0);
    sensor.clearMotion();
    sensor.clearMotion();
    value = sensor.readValue();
    EXPECT_EQ(value.value(), 0.0);
}

TEST(MotionSensorTest, ReadValueReturnsOptional) {
    MotionSensor sensor("TestSensor");
    auto value = sensor.readValue();
    EXPECT_TRUE(value.has_value());
}

TEST(TemperatureSensorTest, Constructor) {
    TemperatureSensor sensor("TestSensor");
    EXPECT_EQ(sensor.getName(), "TestSensor");
    EXPECT_TRUE(sensor.isOperational());
    EXPECT_EQ(sensor.getSensorType(), "Temperature");
}

TEST(TemperatureSensorTest, InitialValue) {
    TemperatureSensor sensor("TestSensor");
    auto value = sensor.readValue();
    ASSERT_TRUE(value.has_value());
    EXPECT_GE(value.value(), 15.0);
    EXPECT_LE(value.value(), 35.0);
}

TEST(TemperatureSensorTest, SimulateReading) {
    TemperatureSensor sensor("TestSensor");
    sensor.simulateReading(25.0);
    auto value = sensor.readValue();
    ASSERT_TRUE(value.has_value());
    EXPECT_NEAR(value.value(), 25.0, 1.0);
    sensor.simulateReading(18.5);
    value = sensor.readValue();
    EXPECT_NEAR(value.value(), 18.5, 1.0);
}

TEST(TemperatureSensorTest, RandomVariation) {
    TemperatureSensor sensor("TestSensor");
    sensor.simulateReading(20.0);
    auto first = sensor.readValue();
    auto second = sensor.readValue();
    EXPECT_NE(first, second);
}

TEST(TemperatureSensorTest, Boundaries) {
    TemperatureSensor sensor("TestSensor");
    for (int i = 0; i < 100; ++i) {
        sensor.simulateReading(10.0);
        auto val = sensor.readValue();
        EXPECT_GE(val.value(), 15.0);
        sensor.simulateReading(40.0);
        val = sensor.readValue();
        EXPECT_LE(val.value(), 35.0);
    }
}

TEST(TemperatureSensorTest, ReadValueReturnsOptional) {
    TemperatureSensor sensor("TestSensor");
    auto value = sensor.readValue();
    EXPECT_TRUE(value.has_value());
}