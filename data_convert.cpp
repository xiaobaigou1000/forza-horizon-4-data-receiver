#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <fmt/printf.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

int main(int argc, char **argv)
{
    std::string fileName("FH4_packetformat.dat");

    // if (argc != 2)
    // {
    //     fmt::print("Usage: {} <file>", argv[0]);
    //     return -1;
    // }
    std::ifstream file(fileName, std::ios::binary | std::ios::in);
    std::vector<char> buffer;
    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(buffer));
    file.close();

    std::vector<std::string> rows;
    auto lastWordEnd = buffer.begin();
    while (lastWordEnd != buffer.end())
    {
        auto firstLetter = std::find_if(lastWordEnd, buffer.end(), [](auto i) { return i >= 'a' && i <= 'z'; });
        if (firstLetter == buffer.end())
        {
            break;
        }
        auto lastLetter = std::find_if(firstLetter, buffer.end(), [](auto i) { return i == ';'; });
        std::string temp;
        temp.resize(std::distance(firstLetter, lastLetter));
        std::copy(firstLetter, lastLetter, temp.begin());
        rows.emplace_back(std::move(temp));
        lastWordEnd = lastLetter;
    }

    nlohmann::json config;
    for (auto i = rows.begin(); i != rows.end(); i++)
    {
        auto space_char = std::find_if(i->begin(), i->end(), [](auto i) { return i == ' '; });
        std::string type;
        std::string name;
        type.resize(std::distance(i->begin(), space_char));
        name.resize(std::distance(std::next(space_char), i->end()));
        std::copy(i->begin(), space_char, type.begin());
        std::copy(std::next(space_char), i->end(), name.begin());

        nlohmann::json config_item;
        config_item["type"] = type;
        config_item["name"] = name;

        config.push_back(config_item);
    }
    std::string str = config.dump();

    std::ofstream output("forza-horizon-4-data-format.json");
    output << str;
}