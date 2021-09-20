//
// Created by luke on 10-08-21.
//

#ifndef LIB_UCOMMAND_H
#define LIB_UCOMMAND_H

#include <cstring>
#include <vector>

namespace Utils
{
    class CommandlineArgument
    {
    public:
        CommandlineArgument();
        CommandlineArgument(unsigned long anArgumentNumber, std::string aVariable, std::string aValue);

        CommandlineArgument& operator=(const CommandlineArgument& aCommandlineArgument);
        bool operator==(uint64_t anArgumentNumber) const;
        bool operator==(const std::string& aVariable) const;
        bool operator==(const CommandlineArgument& aCommandlineArgument) const;
        bool operator<(const CommandlineArgument& aCommandlineArgument) const;

    public:
        unsigned long argumentNumber;
        std::string variable;
        std::string value;
    };

    class [[maybe_unused]] Command
    {
    public:
        [[maybe_unused]] static void setCommandLineArguments(int argc, char* argv[]);
        [[maybe_unused]] static bool isArgGiven(const std::string& variable);
        [[maybe_unused]] static CommandlineArgument& getArg(const std::string& variable);
        [[maybe_unused]] static CommandlineArgument& getArg(uint64_t number);
        [[maybe_unused]] static std::vector<std::string>& getCommandLineFiles();

    private:
        static std::vector<CommandlineArgument> commandlineArguments;
        static std::vector<std::string> commandlineFiles;
    };
}// namespace utils

#endif// LIB_UCOMMAND_H
