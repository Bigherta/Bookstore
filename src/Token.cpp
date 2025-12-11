#include "../include/Token.hpp"
#include <memory>

TokenStream::TokenStream(std::vector<Token> &&tokens) : tokens_(std::move(tokens)), cursor_(0) {}

const std::shared_ptr<Token> TokenStream::peek() const
{
    if (cursor_ >= tokens_.size())
    {
        return nullptr;
    }
    std::shared_ptr<Token> temp = std::make_shared<Token>(tokens_[cursor_]);
    return temp;
} // 查看当前token并返回指针

const std::shared_ptr<Token> TokenStream::get()
{
    const std::shared_ptr<Token> current = peek();
    if (current != nullptr)
    {
        ++cursor_;
    }
    return current;
} // 取出当前token并前进

int TokenStream::size() const { return tokens_.size(); } // 总数

void TokenStream::push(Token &&token) { tokens_.push_back(std::move(token)); } // 输入token
