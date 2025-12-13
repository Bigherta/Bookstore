#pragma once
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <memory>
#include <string>
#include <vector>


enum TokenType {
    LOGIN,
    LOGOUT,
    REGISTER,
    PASSWD,
    USERADD,
    DELETEUSER,
    ISBN,
    NAME,
    AUTHOR,
    KEYWORD,
    PRICE,
    STOCK,
    SHOW,
    BUY,
    SELECT,
    MODIFY,
    IMPORT,
    REPORT,
    LOG,
    FINANCE,
    EMPLOYEE,
    TEXT,
    EXIT,
    BLANK,
};

struct Token {
    TokenType type{TokenType::BLANK}; // 封装类型
    std::string text{}; // 封装原始文本
    int column{0}; // 追踪当前列
};

class TokenStream {
public:
    TokenStream() = default; // 默认构造
    explicit TokenStream(std::vector<Token> &&tokens);

    const std::shared_ptr<Token> peek() const;

    const std::shared_ptr<Token> get();

    int size() const;

    void push(Token &&token);

private:
    std::vector<Token> tokens_{};
    int cursor_{0};
};
#endif
