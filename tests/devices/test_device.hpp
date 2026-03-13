#ifndef SMART_HOME_PROJECT_TEST_DEVICE_HPP
#define SMART_HOME_PROJECT_TEST_DEVICE_HPP

#include <gtest/gtest.h>
#include "devices/light.hpp"
#include "devices/thermostat.hpp"
#include "exceptions/exceptions.hpp"

TEST(LightTest, Constructor) {
    Light light("TestLight");
    EXPECT_EQ(light.getName(), "TestLight");
    EXPECT_FALSE(light.isOn());
    EXPECT_EQ(light.getBrightness(), 0);
}

TEST(LightTest, TurnOnOff) {
    Light light("TestLight");

    light.turnOn();
    EXPECT_TRUE(light.isOn());
    EXPECT_EQ(light.getBrightness(), 50);

    light.turnOff();
    EXPECT_FALSE(light.isOn());
    EXPECT_EQ(light.getBrightness(), 0);
}

TEST(LightTest, SetBrightness) {
    Light light("TestLight");

    light.setBrightness(75);
    EXPECT_EQ(light.getBrightness(), 75);

    light.setBrightness(0);
    EXPECT_EQ(light.getBrightness(), 0);

    light.setBrightness(100);
    EXPECT_EQ(light.getBrightness(), 100);
}

TEST(LightTest, SetBrightnessOutOfRange) {
    Light light("TestLight");

    EXPECT_THROW(light.setBrightness(-10), InvalidArgumentException);
    EXPECT_THROW(light.setBrightness(150), InvalidArgumentException);
}

TEST(LightTest, GetStatus) {
    Light light("TestLight");

    light.turnOn();
    light.setBrightness(80);
    std::string status = light.getStatus();
    EXPECT_NE(status.find("ON"), std::string::npos);
    EXPECT_NE(status.find("80"), std::string::npos);

    light.turnOff();
    status = light.getStatus();
    EXPECT_NE(status.find("OFF"), std::string::npos);
}

TEST(LightTest, GetType) {
    Light light("TestLight");
    EXPECT_EQ(light.getType(), "Light");
}

TEST(ThermostatTest, Constructor) {
    Thermostat thermo("TestThermo");
    EXPECT_EQ(thermo.getName(), "TestThermo");
    EXPECT_FALSE(thermo.isOn());
    EXPECT_EQ(thermo.getTargetTemperature(), 22.0);
}

TEST(ThermostatTest, TurnOnOff) {
    Thermostat thermo("TestThermo");

    thermo.turnOn();
    EXPECT_TRUE(thermo.isOn());

    thermo.turnOff();
    EXPECT_FALSE(thermo.isOn());
}

TEST(ThermostatTest, SetTargetTemperature) {
    Thermostat thermo("TestThermo");

    thermo.setTargetTemperature(23.5);
    EXPECT_EQ(thermo.getTargetTemperature(), 23.5);

    thermo.setTargetTemperature(18.0);
    EXPECT_EQ(thermo.getTargetTemperature(), 18.0);

    thermo.setTargetTemperature(30.0);
    EXPECT_EQ(thermo.getTargetTemperature(), 30.0);
}

TEST(ThermostatTest, SetTargetTemperatureOutOfRange) {
    Thermostat thermo("TestThermo");

    EXPECT_THROW(thermo.setTargetTemperature(0.0), InvalidArgumentException);
    EXPECT_THROW(thermo.setTargetTemperature(40.0), InvalidArgumentException);
    EXPECT_THROW(thermo.setTargetTemperature(-5.0), InvalidArgumentException);
}

TEST(ThermostatTest, GetStatus) {
    Thermostat thermo("TestThermo");

    thermo.turnOn();
    thermo.setTargetTemperature(24.0);
    std::string status = thermo.getStatus();
    EXPECT_NE(status.find("ON"), std::string::npos);
    EXPECT_NE(status.find("24.0"), std::string::npos);

    thermo.turnOff();
    status = thermo.getStatus();
    EXPECT_NE(status.find("OFF"), std::string::npos);
}

TEST(ThermostatTest, GetType) {
    Thermostat thermo("TestThermo");
    EXPECT_EQ(thermo.getType(), "Thermostat");
}

#endif // SMART_HOME_PROJECT_TEST_DEVICE_HPP