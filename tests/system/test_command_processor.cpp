
#include <gtest/gtest.h>
#include "system/command_processor.hpp"
#include "system/smart_home_system.hpp"

TEST(CommandProcessorTest, ParseArguments) {
    SmartHomeSystem home;
    CommandProcessor cmd(home);

    auto args = cmd.parseArguments("on LivingRoomLight");
    ASSERT_EQ(args.size(), 2);
    EXPECT_EQ(args[0], "on");
    EXPECT_EQ(args[1], "LivingRoomLight");
}

TEST(CommandProcessorTest, ProcessHelpCommand) {
    SmartHomeSystem home;
    CommandProcessor cmd(home);

    auto result = cmd.process("help");

    bool isVector = std::holds_alternative<std::vector<std::string>>(result);
    EXPECT_TRUE(isVector);

    if (isVector) {
        auto vec = std::get<std::vector<std::string>>(result);
        EXPECT_GT(vec.size(), 0);
    }
}