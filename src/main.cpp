#include <iostream>
#include <string>
#include "system/smart_home_system.hpp"
#include "system/command_processor.hpp"
#include "exceptions/exceptions.hpp"

int main() {
    std::cout << "Smart Home System (TEST MODE)" << std::endl;
    SmartHomeSystem home;
    std::cout << "System created successfully!" << std::endl;
    return 0;
}