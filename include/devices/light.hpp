#ifndef SMART_HOME_PROJECT_LIGHT_HPP
#define SMART_HOME_PROJECT_LIGHT_HPP

#include "device.hpp"

class Light : public Device {
public:
    explicit Light(const std::string& name);

    void turnOn() override;
    void turnOff() override;
    std::string getStatus() const override;
    std::string getType() const override;

    std::string getName() const override { return name_; }

    void setBrightness(int level);
    int getBrightness() const { return brightness_; }

private:
    int brightness_;
};

#endif