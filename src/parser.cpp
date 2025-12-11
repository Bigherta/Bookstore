#include "../include/parser.hpp"
#include <cctype>


TokenType Parser::matchkeyword(const std::string &text) const
{
    auto it = TABLE.find(text);
    if (it != TABLE.end())
    {
        return it->second;
    }
    return BLANK;
}

TokenStream Parser::tokenize(const std::string &line) const // 解析一行源码
{
    std::vector<Token> tokens;
    int column = 0;
    while (column < line.size())
    {
        char ch = line[column];
        // 如果ch是空格
        if (std::isspace(static_cast<int>(ch)))
        {
            ++column;
            continue;
        }
        else
        {
            int start = column;
            ++column;
            while (column < line.size() && !std::isspace(line[column]))
            {
                ++column;
            }
            std::string text = line.substr(start, column - start); // 提取单词
            TokenType type = matchkeyword(text); // 判断是哪一个枚举类型
            if (type == BLANK)
            {
                type = TEXT;
            }
            tokens.push_back(Token{type, text, column});
            continue;
        }
    }
    return TokenStream(std::move(tokens));
}

bool Parser::isLetterChar(char ch) noexcept { return std::isalpha(static_cast<unsigned char>(ch)); }

bool Parser::isNumberChar(char ch) noexcept
{
    return std::isalnum(static_cast<unsigned char>(ch)) && !std::isalpha(static_cast<unsigned char>(ch));
}
