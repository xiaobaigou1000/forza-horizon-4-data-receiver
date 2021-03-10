#include<nlohmann/json.hpp>
#include<fstream>
#include<vector>
#include<algorithm>

int main()
{
    std::ifstream file("forza-horizon-4-data-format.json");
    std::vector<char> buffer;
    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(buffer));
    file.close();

    nlohmann::json origin = nlohmann::json::parse(buffer);
    for (auto& i : origin)
    {
        i["scaler"] = 1.0f;
    }

    std::ofstream output("config.json");
    output << origin.dump(4);
}