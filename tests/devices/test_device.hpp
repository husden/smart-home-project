#ifndef SMART_HOME_PROJECT_TEST_DEVICE_HPP
#define SMART_HOME_PROJECT_TEST_DEVICE_HPP

#include <gtest/gtest.h>
#include "devices/device.hpp"
#include "exceptions/exceptions.hpp"

class TestDevice : public Device {
public:
    explicit TestDevice(const std::string& name) : Device(name) {}

    void turnOn() override { isOn_ = true; }
    void turnOff() override { isOn_ = false; }

    std::string getStatus() const override {
        return isOn_ ? "TestDevice is ON" : "TestDevice is OFF";
    }
    std::string getName() const override { return name_; }
    std::string getType() const override { return "TestDevice"; }
};

TEST(DeviceTest, CreateDevice) {
    TestDevice device("Test Light");
    EXPECT_EQ(device.getName(), "Test Light");
    EXPECT_EQ(device.getType(), "TestDevice");
    EXPECT_FALSE(device.isOn());
}

#endif //SMART_HOME_PROJECT_TEST_DEVICE_HPP