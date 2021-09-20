//
// Created by luke on 20-09-21.
//

#include "Misc.h"

#include <sstream>

namespace Utils
{
    /*static*/ std::vector<std::string> Misc::divide (const std::string& str, char c)
    {
        std::stringstream ss(str);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, c))
            tokens.emplace_back(token);
        return tokens;
    }
}