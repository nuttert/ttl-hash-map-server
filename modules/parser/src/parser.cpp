#include "parser.hpp"
#include <nlohmann/json.hpp>
#include <string_view>
#include <unordered_map>
#include <iostream>

namespace parser
{
    using Json = nlohmann::json;

    ParserResponse Parser::Parse(const std::string &str)
    {
        size_t first_command_index = 0;
        size_t last_command_index = 0;
        ECommands command = ECommands::kParseError;

        for (first_command_index = 0; first_command_index < str.size(); ++first_command_index)
            if (str[first_command_index] != ' ')
                break;

        for (last_command_index = first_command_index; last_command_index < str.size(); ++last_command_index)
            if (str[last_command_index] == ' ')
                break;

        if (first_command_index == str.size())
            --first_command_index;
        if (last_command_index == str.size())
            --last_command_index;

        std::string_view view = str;
        std::string_view command_str = view.substr(first_command_index, last_command_index);
        std::string_view data_str = view.substr(last_command_index < str.size() - 1 ? last_command_index + 1 : last_command_index, str.size());

        if (command_str == "SET")
            return SetDataParse(data_str);
        else if (command_str == "GET")
            return GetDataParse(data_str);
        else if (command_str == "DEL")
            return DelDataParse(data_str);
        else if (command_str == "KEYS")
            return KeysDataParse(data_str);

        return {ECommands::kComandNotFoundError};
    }

    ParserResponse Parser::GetDataParse(std::string_view data_str)
    {
        try
        {
            auto json_obj = Json::parse(data_str);
            if (!json_obj.is_array() && !json_obj.is_string())
                return {ECommands::kIsNotArrayOrStringError};

            if (json_obj.is_array())
            {
                auto vec = json_obj.get<Vector>();
                return {ECommands::kGet, {}, std::move(vec)};
            }
            else
            {
                Vector vec{};
                vec.push_back(json_obj.get<std::string>());
                return {ECommands::kGet, {}, std::move(vec)};
            }
        }
        catch (...)
        {
            return {ECommands::kParseError};
        }
    }
    ParserResponse Parser::DelDataParse(std::string_view data_str)
    {
        try
        {
            auto json_obj = Json::parse(data_str);
            if (!json_obj.is_array() && !json_obj.is_string())
                return {ECommands::kIsNotArrayOrStringError};

            if (json_obj.is_array())
            {
                auto vec = json_obj.get<Vector>();
                return {ECommands::kDel, {}, std::move(vec)};
            }
            else
            {
                Vector vec{};
                vec.push_back(json_obj.get<std::string>());
                return {ECommands::kDel, {}, std::move(vec)};
            }
        }
        catch (...)
        {
            return {ECommands::kParseError};
        }
    }
    ParserResponse Parser::KeysDataParse(std::string_view data_str)
    {
        for (size_t i = 0; i < data_str.size() - 1; ++i)
        {
            const auto &symb = data_str[i];
            if (symb != ' ' ||
                symb != '\n' ||
                symb != '\r' ||
                symb != '\0' ||
                symb != '\a' ||
                symb != '\b' ||
                symb != '\v' ||
                symb != '\f' ||
                symb != '\\' ||
                symb != '\t')
                return {ECommands::kParseError};
        }
        return {ECommands::kKeys};
    }
    ParserResponse Parser::SetDataParse(std::string_view data_str)
    {
        using Map = std::unordered_map<std::string, std::string>;

        try
        {
            auto json_obj = Json::parse(data_str);
            if (!json_obj.is_object())
                return {ECommands::kIsNotKeyValueMapError};
            Map map{};
            for (auto &element : json_obj.items())
                map.insert({element.key(), element.value().dump()});

            return {ECommands::kSet, std::move(map)};
        }
        catch (const std::exception &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
            return {ECommands::kParseError};
        }
    }

} // namespace parser