#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include "system/smart_home_system.hpp"
#include "system/command_processor.hpp"
#include "exceptions/exceptions.hpp"
#include "devices/light.hpp"
#include "devices/thermostat.hpp"
#include "sensors/temperature_sensor.hpp"
#include "sensors/motion_sensor.hpp"
#include "rules/condition_rule.hpp"
#include "rules/scheduled_rule.hpp"

void setupDemoSystem(SmartHomeSystem& home) {
    std::cout << "\n🔧 Setting up demo smart home...\n";

    auto livingRoomLight = std::make_unique<Light>("LivingRoomLight");
    auto bedroomLight = std::make_unique<Light>("BedroomLight");
    auto mainThermostat = std::make_unique<Thermostat>("MainThermostat");

    auto motionSensor = std::make_shared<MotionSensor>("Hall Motion Sensor");
    auto tempSensor = std::make_shared<TemperatureSensor>("Outside Temp Sensor");

    home.addDevice(std::move(livingRoomLight));
    home.addDevice(std::move(bedroomLight));
    home.addDevice(std::move(mainThermostat));

    home.addSensor(motionSensor);
    home.addSensor(tempSensor);

    auto motionRule = std::make_unique<ConditionRule>(
            "Motion Light Rule",
            [motionSensor]() {
                auto value = motionSensor->readValue();
                return value.has_value() && value.value() > 0.5;
            },
            [&home]() {
                auto device = home.findDevice("LivingRoomLight");
                if (device.has_value()) {
                    device.value()->turnOn();
                    std::cout << "  🔔 Motion detected! Light turned on.\n";
                }
            }
    );

    auto nightRule = std::make_unique<ScheduledRule>(
            "Night Off Rule",
            ScheduledRule::makeTime(23, 0),
            [&home]() {
                auto device = home.findDevice("BedroomLight");
                if (device.has_value()) {
                    device.value()->turnOff();
                    std::cout << "  🌙 Good night! Bedroom light turned off.\n";
                }
            },
            true
    );

    auto tempRule = std::make_unique<ConditionRule>(
            "Cold Weather Rule",
            [tempSensor]() {
                auto value = tempSensor->readValue();
                return value.has_value() && value.value() < 10.0;
            },
            [&home]() {
                auto device = home.findDevice("MainThermostat");
                if (device.has_value()) {
                    device.value()->turnOn();
                    std::cout << "  ❄️ It's cold! Heating turned on.\n";
                }
            }
    );

    home.addRule(std::move(motionRule));
    home.addRule(std::move(nightRule));
    home.addRule(std::move(tempRule));

    std::cout << "✅ Demo system ready with 3 devices, 2 sensors, 3 rules\n\n";
}

int main() {
    try {
        std::cout << "╔════════════════════════════════════╗\n";
        std::cout << "║     🏠 SMART HOME SYSTEM v1.0     ║\n";
        std::cout << "╚════════════════════════════════════╝\n\n";

        SmartHomeSystem home;
        setupDemoSystem(home);

        CommandProcessor cmd(home);

        std::cout << "Commands: help, status, list, on/off <device>, exit\n";
        std::cout << "Type 'help' for full list\n\n";

        std::cout << "📋 Running initial system check...\n";
        home.run();

        std::string input;
        std::cout << "\n> ";

        while (std::getline(std::cin, input)) {
            try {
                auto result = cmd.process(input);

                std::visit([](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, std::monostate>) {
                    }
                    else if constexpr (std::is_same_v<T, std::string>) {
                        std::cout << arg << std::endl;
                    }
                    else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
                        for (const auto& line : arg) {
                            std::cout << line << std::endl;
                        }
                    }
                    else if constexpr (std::is_same_v<T, bool>) {
                        std::cout << (arg ? "true" : "false") << std::endl;
                    }
                    else if constexpr (std::is_same_v<T, int>) {
                        std::cout << arg << std::endl;
                    }
                }, result);

                if (input == "exit" || input == "quit") {
                    break;
                }

                home.run();

            } catch (const CommandException& e) {
                std::cerr << "❌ " << e.what() << std::endl;
                std::cout << "Type 'help' for available commands" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "❌ Error: " << e.what() << std::endl;
            }

            std::cout << "\n> ";
        }

        std::cout << "\n👋 Goodbye! Smart Home System shutting down.\n";

    } catch (const std::exception& e) {
        std::cerr << "❌ Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}