#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <functional>

#include "parser-interface.hpp"

namespace parser
{
    class Parser : public ParserInterface
    {
        public:
            ParserResponse Parse(const std::string&) override;
        private:
            ParserResponse GetDataParse(std::string_view);
            ParserResponse SetDataParse(std::string_view);
            ParserResponse DelDataParse(std::string_view);
            ParserResponse KeysDataParse(std::string_view);

    };
} // namespace server