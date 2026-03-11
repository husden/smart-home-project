#include "system/command_processor.hpp"
#include "system/smart_home_system.hpp"
#include "exceptions/exceptions.hpp"
#include <iostream>
#include <algorithm>
#include <map>

CommandProcessor::CommandProcessor(SmartHomeSystem& sys) : system(sys) {}

std::vector<std::string> CommandProcessor::parseArguments(const std::string& input) {
    std::vector<std::string> args;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        args.push_back(token);
    }

    return args;
}

CommandResult CommandProcessor::process(const std::string& input) {
    if (input.empty()) {
        return std::monostate{};
    }

    auto args = parseArguments(input);
    if (args.empty()) {
        return std::monostate{};
    }

    std::string command = args[0];
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    args.erase(args.begin());

    try {
        if (command == "status" || command == "st") {
            return handleStatus(args);
        } else if (command == "on" || command == "turnon") {
            return handleTurnOn(args);
        } else if (command == "off" || command == "turnoff") {
            return handleTurnOff(args);
        } else if (command == "list" || command == "ls") {
            return handleList(args);
        } else if (command == "help" || command == "h") {
            return handleHelp(args);
        } else if (command == "exit" || command == "quit") {
            return handleExit(args);
        } else {
            throw CommandException(command);
        }
    } catch (const CommandException& e) {
        throw;
    } catch (const std::exception& e) {
        return std::string("❌ Error: ") + e.what();
    }
}

CommandResult CommandProcessor::handleStatus(const std::vector<std::string>& args) {
    system.printStatus();
    return std::string("✅ Status displayed");
}

CommandResult CommandProcessor::handleTurnOn(const std::vector<std::string>& args) {
    if (args.empty()) {
        return std::string("❌ Error: specify device name. Usage: on <device>");
    }

    std::string deviceName = args[0];
    auto device = system.findDevice(deviceName);

    if (device.has_value()) {
        device.value()->turnOn();
        return std::string("✅ Turned on: " + deviceName);
    } else {
        return std::string("❌ Device not found: " + deviceName);
    }
}

CommandResult CommandProcessor::handleTurnOff(const std::vector<std::string>& args) {
    if (args.empty()) {
        return std::string("❌ Error: specify device name. Usage: off <device>");
    }

    std::string deviceName = args[0];
    auto device = system.findDevice(deviceName);

    if (device.has_value()) {
        device.value()->turnOff();
        return std::string("✅ Turned off: " + deviceName);
    } else {
        return std::string("❌ Device not found: " + deviceName);
    }
}

CommandResult CommandProcessor::handleList(const std::vector<std::string>& args) {
    std::vector<std::string> result;
    result.push_back("📊 System components:");
    result.push_back("  📦 Devices: " + std::to_string(system.getDeviceCount()));
    result.push_back("  📡 Sensors: " + std::to_string(system.getSensorCount()));
    result.push_back("  📋 Rules: " + std::to_string(system.getRuleCount()));
    return result;
}

CommandResult CommandProcessor::handleHelp(const std::vector<std::string>& args) {
    std::vector<std::string> commands = {
            "📚 Available commands:",
            "  status (st)        - show system status",
            "  on <device>        - turn on device",
            "  off <device>       - turn off device",
            "  list (ls)          - list all components",
            "  help (h)           - show this help",
            "  exit (quit)        - exit program"
    };
    return commands;
}

CommandResult CommandProcessor::handleExit(const std::vector<std::string>& args) {
    std::cout << "👋 Shutting down Smart Home System..." << std::endl;
    return std::monostate{};
}

std::vector<std::string> CommandProcessor::getAvailableCommands() const {
    return {
            "status", "on <device>", "off <device>",
            "list", "help", "exit"
    };
}