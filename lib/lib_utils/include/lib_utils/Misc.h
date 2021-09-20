//
// Created by luke on 22-08-21.
//

#ifndef DAY_XX_MISC_H
#define DAY_XX_MISC_H

#include <vector>
#include <string>

namespace Utils
{
    class [[maybe_unused]] Misc
    {
    public:
        [[maybe_unused]] static std::vector<std::string> divide (const std::string& str, char c)
        {
            std::stringstream ss(str);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, c))
                tokens.emplace_back(token);
            return tokens;
        }
    };
}

#endif//DAY_XX_MISC_H
