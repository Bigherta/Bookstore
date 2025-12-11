#pragma once

#include <memory>
#include <string>
#include <vector>


enum TokenType
{
    LOGIN,
    LOGOUT,
    REGISTER,
    PASSWD,
    USERADD,
    DELETEUSER,
    EXIT,
    BLANK,
    SHOW,
    REPORT,
    LOG,
    FINANCE,
    TEXT,
};

struct Token
{
    TokenType type{TokenType::BLANK}; // 封装类型
    std::string text{}; // 封装原始文本
    int column{0}; // 追踪当前列
};

class TokenStream
{
public:
    TokenStream() = default; // 默认构造
    explicit TokenStream(std::vector<Token> &&tokens);

    const std::shared_ptr<Token> peek() const;
    const std::shared_ptr<Token> get();
    bool empty() const;
    void reset();

    int position() const;
    int size() const;

    void push(Token &&token);
    const std::vector<Token> &data() const;

private:
    std::vector<Token> tokens_{};
    int cursor_{0};
};
