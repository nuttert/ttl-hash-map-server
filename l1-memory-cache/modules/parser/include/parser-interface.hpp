#pragma once
#include <unordered_map>
#include <vector>

namespace parser
{
    using Map = std::unordered_map<std::string, std::string>;
    using Vector = std::vector<std::string>;

    enum class ECommands{
        kSet,
        kGet,
        kDel,
        kKeys,
        kParseError,
        kComandNotFoundError,
        kKeyError,
        kIsNotKeyValueMapError,
        kIsNotArrayOrStringError,
    };

    struct ParserResponse{
        ECommands command;
        Map map{};
        Vector vector{};
    };

    class ParserInterface
    {
    public:
        virtual ~ParserInterface() = default;
        virtual ParserResponse Parse(const std::string&) = 0;
    };
} // namespace server