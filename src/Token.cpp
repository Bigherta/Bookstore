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

bool TokenStream::empty() const { return cursor_ >= tokens_.size(); } // 是否为空

void TokenStream::reset() { cursor_ = 0; } // 游标回到起点

int TokenStream::position() const { return cursor_; } // 返回当前游标

int TokenStream::size() const { return tokens_.size(); } // 总数

void TokenStream::push(Token &&token) { tokens_.push_back(std::move(token)); } // 输入token

const std::vector<Token> &TokenStream::data() const { return tokens_; } // 返回token的所有信息
