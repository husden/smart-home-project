#include <iostream>
#include "system/smart_home_system.hpp"
#include "system/command_processor.hpp"
#include "exceptions/exceptions.hpp"

int main() {
    std::cout << "🏠 Smart Home System v1.0" << std::endl;
    std::cout << "Type 'help' for commands\n" << std::endl;

    SmartHomeSystem home;
    CommandProcessor cmd(home);

    std::string input;
    std::cout << "> ";

    while (std::getline(std::cin, input)) {
        try {
            auto result = cmd.process(input);
            std::visit([](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::cout << arg << std::endl;
            } else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
                for (const auto& line : arg) {
                    std::cout << line << std::endl;
                }
            } else if constexpr (std::is_same_v<T, bool>) {
                std::cout << (arg ? "true" : "false") << std::endl;
            } else if constexpr (std::is_same_v<T, int>) {
                std::cout << arg << std::endl;
            }
            }, result);

        } catch (const CommandException& e) {
            std::cerr << "❌ " << e.what() << std::endl;
            std::cout << "Type 'help' for available commands" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "❌ Error: " << e.what() << std::endl;
        }

        std::cout << "> ";
    }

    return 0;
}