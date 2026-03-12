#ifndef COMMAND_PROCESSOR_HPP
#define COMMAND_PROCESSOR_HPP

#include <string>
#include <vector>
#include <variant>
#include <functional>
#include <memory>
#include <sstream>

class SmartHomeSystem;

using CommandResult = std::variant<
        std::monostate,
        std::string,
        std::vector<std::string>,
        bool,
        int
>;

class CommandProcessor {
private:
    SmartHomeSystem& system;

    CommandResult handleStatus(const std::vector<std::string>& args);
    CommandResult handleTurnOn(const std::vector<std::string>& args);
    CommandResult handleTurnOff(const std::vector<std::string>& args);
    CommandResult handleList(const std::vector<std::string>& args);
    CommandResult handleHelp(const std::vector<std::string>& args);
    CommandResult handleExit(const std::vector<std::string>& args);
public:
    explicit CommandProcessor(SmartHomeSystem& sys);

    CommandResult process(const std::string& input);

    std::vector<std::string> parseArguments(const std::string& input);

    std::vector<std::string> getAvailableCommands() const;
};

#endif