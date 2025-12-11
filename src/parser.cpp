#include "../include/parser.hpp"


Command matchkeyword(const std::string &text)
{
    auto it = TABLE.find(text);
    if (it != TABLE.end())
    {
        return it->second;
    }
    return INVALID;
}
