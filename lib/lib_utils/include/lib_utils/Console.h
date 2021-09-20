//
// Created by luke on 10-08-21.
//

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string>
#include <vector>

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace Utils
{
    class Console
    {
    public:
        enum Type
        {
            ERROR,   /** @info verbosity: ERROR */
            TRANS,   /** @info verbosity: TRANSITION*/
            INFO,    /** @info verbosity: INFO*/
            WARNING, /** @info verbosity: WARNING*/
            DEBUG,   /** @info verbosity: DEBUG*/
        };

        enum Color
        {
            NORMAL_BLACK [[maybe_unused]] = 30,   /**< @info color code for normal black */
            NORMAL_RED [[maybe_unused]] = 31,     /**< @info color code for normal red */
            NORMAL_GREEN [[maybe_unused]] = 32,   /**< @info color code for normal green */
            NORMAL_YELLOW [[maybe_unused]] = 33,  /**< @info color code for normal yellow*/
            NORMAL_BLUE [[maybe_unused]] = 34,    /**< @info color code for normal blue */
            NORMAL_MAGENTA [[maybe_unused]] = 35, /**< @info color code for normal magenta */
            NORMAL_CYAN [[maybe_unused]] = 36,    /**< @info color code for normal cyan */
            NORMAL_WHITE [[maybe_unused]] = 37,   /**< @info color code for normal white */
            BRIGHT_BLACK [[maybe_unused]] = 90,   /**< @info color code for bright black */
            BRIGHT_RED [[maybe_unused]] = 91,     /**< @info color code for bright red */
            BRIGHT_GREEN [[maybe_unused]] = 92,   /**< @info color code for bright green */
            BRIGHT_YELLOW [[maybe_unused]] = 93,  /**< @info color code for bright yellow*/
            BRIGHT_BLUE [[maybe_unused]] = 94,    /**< @info color code for bright blue */
            BRIGHT_MAGENTA [[maybe_unused]] = 95, /**< @info color code for bright magenta */
            BRIGHT_CYAN [[maybe_unused]] = 96,    /**< @info color code for bright cyan */
            BRIGHT_WHITE [[maybe_unused]] = 97    /**< @info color code for bright white */
        };

    private:
        static uint8_t max_verbosity;
        static std::vector<Type> not_active_types;

    public:
        /**
         * set max verbosity for program
         *
         * @param maxVerbosity [ERROR,TRANS,INFO,WARNING,DEBUG]
         */
        [[maybe_unused]] static void setMaxVerbosity(uint8_t maxVerbosity = DEBUG)
        {
            max_verbosity = maxVerbosity;
        }
        /**
         * deactivate type
         *
         * @param type [ERROR,TRANS,INFO,WARNING,DEBUG]
         */
        [[maybe_unused]] static void deactivateType(const Type& type)
        {
            if (std::find(not_active_types.begin(), not_active_types.end(), type) == not_active_types.end())
            {
                not_active_types.emplace_back(type);
            }
        }
        /**
         * activate type
         *
         * @param type [ERROR,TRANS,INFO,WARNING,DEBUG]
         */
        [[maybe_unused]] static void activateType(const Type& type)
        {
            not_active_types.erase(std::remove(not_active_types.begin(), not_active_types.end(), type),
                                   not_active_types.end());
        }
        /**
         * print error message
         *
         * @tparam T            type of argument list
         * @param message       message to print
         * @param vars          argument list
         * @param printAsList   true for numbered list, false for parameter style
         */
        template<typename T>
        [[maybe_unused]] static void error(const std::string& message, const std::vector<T>& vars,
                                           bool printAsList = false)
        {
            if (isTypeActive(ERROR))
            {
                const std::string gen_msg = (printAsList) ? generateMessageStringAsList(ERROR, message, vars)
                                                          : generateMessageString(ERROR, message, vars);
                print(gen_msg);
            }
        }
        /**
         * print error message
         *
         * @tparam T        type of argument
         * @param message   message to print
         * @param var       argument
         */
        template<typename T>
        [[maybe_unused]] static void error(const std::string& message, T var)
        {
            if (isTypeActive(ERROR))
            {
                print(generateMessageString(ERROR, message, std::vector<T>{var}));
            }
        }
        /**
         * print error message
         *
         * @param message message to print
         */
        [[maybe_unused]] static void error(const std::string& message)
        {
            if (isTypeActive(ERROR))
            {
                print(generateMessageString(ERROR, message, std::vector<int>{}));
            }
        }
        /**
         * print info message
         *
         * @tparam T            type of argument list
         * @param message       message to print
         * @param vars          argument list
         * @param printAsList   true for numbered list, false for parameter style
         */
        template<typename T>
        [[maybe_unused]] static void info(const std::string& message, const std::vector<T>& vars,
                                          bool printAsList = false)
        {
            if (isTypeActive(INFO))
            {
                const std::string gen_msg = (printAsList) ? generateMessageStringAsList(INFO, message, vars)
                                                          : generateMessageString(INFO, message, vars);
                print(gen_msg);
            }
        }
        /**
         * print info message
         *
         * @tparam T        type of argument
         * @param message   message to print
         * @param var       argument
         */
        template<typename T>
        [[maybe_unused]] static void info(const std::string& message, T var)
        {
            if (isTypeActive(INFO))
            {
                print(generateMessageString(INFO, message, std::vector<T>{var}));
            }
        }
        /**
         * print info message
         *
         * @param message message to print
         */
        [[maybe_unused]] static void info(const std::string& message)
        {
            if (isTypeActive(INFO))
            {
                print(generateMessageString(INFO, message, std::vector<int>{}));
            }
        }
        /**
         * print warning message
         *
         * @tparam T            type of argument list
         * @param message       message to print
         * @param vars          argument list
         * @param printAsList   true for numbered list, false for parameter style
         */
        template<typename T>
        [[maybe_unused]] static void warning(const std::string& message, const std::vector<T>& vars,
                                             bool printAsList = false)
        {
            if (isTypeActive(WARNING))
            {
                const std::string gen_msg = (printAsList) ? generateMessageStringAsList(WARNING, message, vars)
                                                          : generateMessageString(WARNING, message, vars);
                print(gen_msg);
            }
        }
        /**
         * print warning message
         *
         * @tparam T        type of argument
         * @param message   message to print
         * @param var       argument
         */
        template<typename T>
        [[maybe_unused]] static void warning(const std::string& message, T var)
        {
            if (isTypeActive(WARNING))
            {
                print(generateMessageString(WARNING, message, std::vector<T>{var}));
            }
        }
        /**
         * print warning message
         *
         * @param message message to print
         */
        [[maybe_unused]] static void warning(const std::string& message)
        {
            if (isTypeActive(WARNING))
            {
                print(generateMessageString(WARNING, message, std::vector<int>{}));
            }
        }
        /**
         * print debug message
         *
         * @tparam T            type of argument list
         * @param message       message to print
         * @param vars          argument list
         * @param printAsList   true for numbered list, false for parameter style
         */
        template<typename T>
        [[maybe_unused]] static void debug(const std::string& message, const std::vector<T>& vars,
                                           bool printAsList = false)
        {
            if (isTypeActive(DEBUG))
            {
                const std::string gen_msg = (printAsList) ? generateMessageStringAsList(DEBUG, message, vars)
                                                          : generateMessageString(DEBUG, message, vars);
                print(gen_msg);
            }
        }
        /**
         * print debug message
         *
         * @tparam T        type of argument
         * @param message   message to print
         * @param var       argument
         */
        template<typename T>
        [[maybe_unused]] static void debug(const std::string& message, T var)
        {
            if (isTypeActive(DEBUG))
            {
                print(generateMessageString(DEBUG, message, std::vector<T>{var}));
            }
        }
        /**
         * print debug message
         *
         * @param message message to print
         */
        [[maybe_unused]] static void debug(const std::string& message)
        {
            if (isTypeActive(DEBUG))
            {
                print(generateMessageString(DEBUG, message, std::vector<int>{}));
            }
        }
        /**
         * print transition message
         *
         * @param message   message to print
         * @param from      state transitioning from
         * @param to        state transitioning to
         */
        [[maybe_unused]] static void transition(const std::string& message, const std::string& from,
                                                const std::string& to)
        {
            if (!isTypeActive(TRANS))
                return;

            std::string transMessage = generateMessageString(TRANS, message, std::vector<int>{});

            std::string transVars = convertToColor(" [", BRIGHT_CYAN);

            transVars += convertToColor(from, NORMAL_RED);
            transVars += convertToColor(" -> ", BRIGHT_CYAN);
            transVars += convertToColor(to, NORMAL_GREEN);

            transVars += convertToColor("]", BRIGHT_CYAN);

            print(transMessage + transVars);
        }
        /**
         * convert string to colored string
         *
         * @param text      text to convert
         * @param color     color to convert to
         * @return          converted string
         */
        static std::string convertToColor(const std::string& text, Color color)
        {
            return "\x1B[" + std::to_string(color) + "m" + text + "\033[0m";
        }

    private:
        static std::string getTypeMessage(const Type& messageType)
        {
            switch (messageType)
            {
                case ERROR:
                    return convertToColor("[ERROR]\t", BRIGHT_RED);
                case TRANS:
                    return convertToColor("[TRANS]\t", BRIGHT_MAGENTA);
                case INFO:
                    return convertToColor("[INFO]\t", BRIGHT_GREEN);
                case WARNING:
                    return convertToColor("[WARN]\t", BRIGHT_YELLOW);
                case DEBUG:
                    return convertToColor("[DEBUG]\t", BRIGHT_MAGENTA);
                default:
                    return convertToColor("[UNDEFINED]\t", NORMAL_BLACK);
            }
        }

        template<typename T>
        static std::string generateMessageString(const Type& messageType, const std::string& message,
                                                 const std::vector<T>& vars)
        {
            std::vector<std::string> varsAsString;
            for_each(vars.begin(), vars.end(), [&](T var) {
                varsAsString.template emplace_back(convertToString(var));
            });
            return generateMessageString(messageType, message, varsAsString);
        }
        static std::string generateMessageString(const Type& messageType, const std::string& message,
                                                 const std::vector<std::string>& vars)
        {
            std::string varString = convertToColor("(", BRIGHT_CYAN);
            for_each(vars.begin(), vars.end(), [&](const std::string& var) {
                varString += convertToColor(var, NORMAL_WHITE) + ", ";
            });
            varString = varString.substr(0, varString.length() - 2) + convertToColor(")", BRIGHT_CYAN);
            std::string totString = getTypeMessage(messageType) + message + ((vars.empty()) ? "" : " " + varString);
            return totString;
        }
        template<typename T>
        static std::string generateMessageStringAsList(const Type& messageType, const std::string& message,
                                                       const std::vector<T>& vars)
        {
            std::vector<std::string> varsAsString;
            for_each(vars.begin(), vars.end(), [&](T var) {
                varsAsString.template emplace_back(convertToString(var));
            });
            return generateMessageStringAsList(messageType, message, varsAsString);
        }
        static std::string generateMessageStringAsList(const Type& messageType, const std::string& message,
                                                       const std::vector<std::string>& vars)
        {
            std::string varString;
            for (std::size_t i = 0; i < vars.size(); ++i)
            {
                std::string indexStr = convertToColor("[", BRIGHT_CYAN) +
                                       convertToColor(std::to_string(i), NORMAL_WHITE) +
                                       convertToColor("]", BRIGHT_CYAN);

                varString += "  " + indexStr + convertToColor(" -> ", BRIGHT_YELLOW);
                varString += convertToColor(vars[i], NORMAL_WHITE) + ((i != vars.size() - 1) ? "\n" : "");
            }

            std::string totString = getTypeMessage(messageType) + convertToColor(message, BRIGHT_WHITE) + " = \n";
            totString += ((vars.empty()) ? "" : varString);
            return totString;
        }
        template<typename T>
        static std::string convertToString(T var)
        {
            std::string valueString;
            if (std::is_same<T, bool>::value)
            {
                valueString = (static_cast<bool>(var)) ? convertToColor("true", NORMAL_GREEN)
                                                       : convertToColor("false", NORMAL_RED);
            }
            else if (std::is_same<T, float>::value || std::is_same<T, double>::value)
            {
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << var;
                valueString = convertToColor(stream.str(), NORMAL_WHITE);
            }
            else
            {
                try
                {
                    std::ostringstream oss;
                    oss << var;
                    valueString = convertToColor(oss.str(), NORMAL_WHITE);
                }
                catch (...)
                {
                    valueString = convertToColor("[undefined]", NORMAL_WHITE);
                }
            }
            return valueString;
        }
        static void print(const std::string& message)
        {
            std::cout << message << std::endl;
        }
        static bool isTypeActive(const Type& type)
        {
            if (max_verbosity < type ||
                std::find(not_active_types.begin(), not_active_types.end(), type) != not_active_types.end())
            {
                return false;
            }
            return true;
        }
    };

    /* static */ uint8_t Console::max_verbosity = Console::DEBUG;
    /* static */ std::vector<Console::Type> Console::not_active_types = std::vector<Console::Type>{};

}// namespace Utils

#endif//LOGGER_LOGGER_H
