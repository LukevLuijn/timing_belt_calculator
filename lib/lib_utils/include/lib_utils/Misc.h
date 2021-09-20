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
        /**
         * divide string by char
         *
         * @param str   string to divide
         * @param c     separator
         * @return      list of separated words
         */
        [[maybe_unused]] static std::vector<std::string> divide (const std::string& str, char c);
    };
}

#endif//DAY_XX_MISC_H
