//
// Created by luke on 10-08-21.
//

#ifndef FILEIO_FILEIO_H
#define FILEIO_FILEIO_H

#include <string>
#include <vector>

namespace Utils
{
    class FileIO
    {
    private:
        typedef const std::string& Path;
        typedef const std::string& Name;
        typedef std::vector<std::string>& Buffer;
        typedef const std::vector<std::string>& Lines;

    public:
        [[maybe_unused]] static bool readFile(Path path, Buffer buffer, bool fromRoot = true, int16_t index = -1);
        [[maybe_unused]] static bool createFile(Path path, Name name, bool fromRoot = true);
        [[maybe_unused]] static bool removeFile(Path path, bool fromRoot = true);
        [[maybe_unused]] static bool readDirectory(Path path, Buffer buffer, bool fromRoot = true);
        [[maybe_unused]] static bool createDirectory(Path path, Name name, bool fromRoot = true);
        [[maybe_unused]] static bool removeDirectory(Path path, bool fromRoot = true);
        [[maybe_unused]] static bool writeToFile(Path path, Lines lines, bool append = true, bool fromRoot = true);
        [[maybe_unused]] static bool elementExist(Path path, bool fromRoot = true);

    private:
        [[maybe_unused]] static std::string getFileName(Path path);
    };
}// namespace utils

#endif// FILEIO_FILEIO_H
