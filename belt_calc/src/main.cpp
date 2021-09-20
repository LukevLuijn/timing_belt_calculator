
#include "Command.h"
#include "Console.h"
#include "FileIO.h"
#include "Misc.h"
#include <cmath>

typedef std::pair<uint16_t, float> Pulley;

void init(int argc, char** argv);
double calculate(const Pulley& p1, const Pulley& p2, float belt);
void parse(std::vector<Pulley>& pulleys, std::vector<uint16_t>& belts);
std::string get_header(const std::vector<uint16_t>& belts);
void convert();
void create_file(const std::vector<Pulley>& pulleys, const std::vector<uint16_t>& belts,
                 const std::vector<std::vector<std::string>>& tables);

int main(int argc, char** argv)
{
    init(argc, argv);
    convert();
    return 0;
}

double calculate(const Pulley& p1, const Pulley& p2, float belt)
{
    double b = 4 * belt - 6.28 * (p1.second + p2.second);
    double result = (b + std::sqrt(std::pow(b, 2) - 32 * std::pow((p1.second - p2.second), 2))) / 16;

    if (p1.second / 2 + p2.second / 2 > result)
        return -1;

    return result;
}

void parse(std::vector<Pulley>& pulleys, std::vector<uint16_t>& belts)
{
    std::vector<std::string> lines;
    Utils::FileIO::readFile("../assets/pulleys.txt", lines, false);
    for (const std::string& line : lines)
    {
        std::vector<std::string> words = Utils::Misc::divide(line, '=');
        pulleys.emplace_back(std::make_pair(static_cast<uint16_t>(std::stoi(words[0])), std::stof(words[1])));
    }
    lines.clear();
    Utils::FileIO::readFile("../assets/belts.txt", lines, false);
    belts.reserve(lines.size());
    for (const std::string& line : lines)
    {
        belts.emplace_back(static_cast<uint16_t>(std::stoi(line)));
    }
}
std::string get_header(const std::vector<uint16_t>& belts)
{
    std::string line = "|P1|P2|";
    for (uint16_t belt : belts)
        line.append("B=").append(std::to_string(belt)).append("|");
    line.append("\n|---|---|");
    for ([[maybe_unused]] uint16_t belt : belts)
        line.append("---|");
    return line;
}

void create_file(const std::vector<Pulley>& pulleys, const std::vector<uint16_t>& belts,
                 const std::vector<std::vector<std::string>>& tables)
{
    std::string title = "# belt calculator";

    std::vector<std::string> belt_table_lines(2, "|");
    belt_table_lines[0].append("belt circumference|");
    belt_table_lines[1].append("---|");
    for(uint16_t belt : belts)
    {
        belt_table_lines[0].append(std::to_string(belt)).append("|");
        belt_table_lines[1].append("---|");
    }

    std::vector<std::string> pulley_table_lines(3, "|");
    pulley_table_lines[0].append("num. teeth|");
    pulley_table_lines[1].append("---|");
    pulley_table_lines[2].append("diameter|");
    for(const auto& pulley : pulleys)
    {
        pulley_table_lines[0].append(std::to_string(pulley.first)).append("|");
        pulley_table_lines[1].append("---|");
        pulley_table_lines[2].append(Utils::Misc::precision_cast(pulley.second, 3)).append("|");
    }

    std::vector<std::string> first_part = {title};
    first_part.emplace_back("\n### Belts");
    first_part.insert(first_part.end(), belt_table_lines.begin(), belt_table_lines.end());
    first_part.emplace_back("\n### Pulleys");
    first_part.insert(first_part.end(), pulley_table_lines.begin(), pulley_table_lines.end());
    first_part.emplace_back("\n");


    std::string target = "../README.md";
    Utils::FileIO::writeToFile(target, first_part, false, false);
    for(const std::vector<std::string>& table : tables)
        Utils::FileIO::writeToFile(target, table, true, false);
}


void convert()
{
    std::vector<Pulley> pulleys;
    std::vector<uint16_t> belts;
    parse(pulleys, belts);

    std::vector<std::vector<double>> values;

    for (uint16_t belt : belts)
    {
        std::vector<double> belt_values;
        for (std::size_t i = 0; i < pulleys.size(); ++i)
            for (std::size_t j = i; j < pulleys.size(); ++j)
                belt_values.emplace_back(calculate(pulleys[i], pulleys[j], belt));
        values.emplace_back(belt_values);
    }

    std::vector<std::vector<std::string>> lines;
    uint16_t belt_size_counter = 0;
    for (std::size_t i = 0; i < pulleys.size(); ++i)
    {
        std::vector<std::string> section;
        section.emplace_back(std::string("## Pulley - ").append(std::to_string(pulleys[i].first)).append(" teeth"));
        section.emplace_back(get_header(belts));
        for (std::size_t j = i; j < pulleys.size(); ++j)
        {
            std::string entry = std::string("|").append(std::to_string(pulleys[i].first)).append("|");
            entry.append(std::to_string(pulleys[j].first)).append("|");

            for (const std::vector<double>& belt_values : values)
            {
                std::string distance;
                if (belt_values[belt_size_counter] < 0 || std::isnan(belt_values[belt_size_counter]))
                    distance = "n/a";
                else
                    distance = Utils::Misc::precision_cast(belt_values[belt_size_counter], 3);
                entry.append(distance).append("|");
            }
            section.emplace_back(entry);
            ++belt_size_counter;
        }
        section.emplace_back("\n");
        lines.emplace_back(section);
    }
    create_file(pulleys, belts, lines);
}

void init(int argc, char** argv)
{
    Utils::Command::setCommandLineArguments(argc, argv);

    std::vector<std::pair<std::string, std::string>> options{
            std::make_pair("h", "print this help"),
            std::make_pair("c", "convert existing values to document"),
            std::make_pair("a", "add new pulley or belt value"),
    };
    Utils::Command::setCommandLineHelp(options);
}