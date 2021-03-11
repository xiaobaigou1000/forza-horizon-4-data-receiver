#include<nlohmann/json.hpp>
#include<fmt/format.h>
#include<fmt/printf.h>
#include<fmt/ranges.h>
#include<fstream>
#include<vector>
#include<sstream>
#include<regex>

int main()
{
    std::vector<char> buffer;
    try {
        std::ifstream config_file("config.json");
        std::copy(std::istreambuf_iterator<char>(config_file), std::istreambuf_iterator<char>(), std::back_inserter(buffer));
        config_file.close();
    }
    catch (const std::exception& e)
    {
        fmt::print("load config file error: {}", e.what());
        return -1;
    }

    auto config = nlohmann::json::parse(buffer);

    std::ostringstream fields;
    std::ostringstream fieldConvertionFunctions;
    std::ostringstream format_string;
    std::ostringstream format_field;

    for (auto& i : config)
    {
        const std::string name = i["name"];

        const std::string type = i["type"];

        if (type=="f32")
        {
            fields << fmt::format("float {};\n", name);
            fieldConvertionFunctions << "float ";
        }
        if (type == "s32")
        {
            fields << fmt::format("int32_t {};\n", name);
            fieldConvertionFunctions << "int32_t ";
        }
        if (type == "u32")
        {
            fields << fmt::format("uint32_t {};\n", name);
            fieldConvertionFunctions << "uint32_t ";
        }
        if (type == "u16")
        {
            fields << fmt::format("uint16_t {};\n", name);
            fieldConvertionFunctions << "uint16_t ";
        }

        if (type == "u8")
        {
            fields << fmt::format("uint8_t {};\n", name);
            fieldConvertionFunctions << "uint8_t ";
        }

        if (type == "s8")
        {
            fields << fmt::format("int8_t {};\n", name);
            fieldConvertionFunctions << "int8_t ";
        }

        if (type == "hzn")
        {
            fields << fmt::format("int8_t {}[12];\n", name);
            continue;
        }


        format_string << "{}, ";
        format_field << fmt::format("data.convert{}(),\n", name);

        float scale = i["scaler"];
        fieldConvertionFunctions << fmt::format("convert{}()", name) << " {\n";
        fieldConvertionFunctions << fmt::format("return {:.16f}f * {};\n", scale, name);
        fieldConvertionFunctions << "}\n";
    }

    fmt::print("{}", fields.str());
    fmt::print("{}", format_string.str());
    fmt::print("{}", format_field.str());
    fmt::print("{}", fieldConvertionFunctions.str());

    std::vector<char> code_template_buffer;
    try {
        std::ifstream code_template_file("forza_horizon4_structure.tmp");
        std::copy(std::istreambuf_iterator<char>(code_template_file), std::istreambuf_iterator<char>(), std::back_inserter(code_template_buffer));
        code_template_file.close();
    }
    catch (const std::exception& e)
    {
        fmt::print("read template file failed: {}", e.what());
        return -1;
    }

    std::regex fieldCodeRegex("//<field_code_here>");
    std::regex formatStringRegex("<format_string_here>");
    std::regex formatFieldRegex("<format_field_here>");

    std::vector<char> tmp1;
    std::regex_replace(std::back_inserter(tmp1), code_template_buffer.begin(), code_template_buffer.end(), fieldCodeRegex, fields.str() + fieldConvertionFunctions.str());
    std::vector<char> tmp2;
    std::regex_replace(std::back_inserter(tmp2), tmp1.begin(), tmp1.end(), formatStringRegex, format_string.str());
    std::vector<char> outputCodes;
    std::regex_replace(std::back_inserter(outputCodes), tmp2.begin(), tmp2.end(), formatFieldRegex, format_field.str());

    std::ofstream code_output("forza_horizon4_structure.h");
    std::copy(outputCodes.begin(), outputCodes.end(), std::ostreambuf_iterator<char>(code_output));
}
