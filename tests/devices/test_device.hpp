#ifndef SMART_HOME_PROJECT_TEST_DEVICE_HPP
#define SMART_HOME_PROJECT_TEST_DEVICE_HPP

#include <gtest/gtest.h>

#include "../../cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h"
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

TEST (DeviceTest, TurnOff) {
    TestDevice device("Test Light");

    device.turnOn();
    EXPECT_FALSE(device.isOn());
    EXPECT_EQ(device.getStatus(), "TestDevice is OFF");

}

TEST(DeviceTest,EmptyNameThrows) {
    EXPECT_THROW(TestDevice device(""), InvalidArgumentException);
}

#endif //SMART_HOME_PROJECT_TEST_DEVICE_HPP