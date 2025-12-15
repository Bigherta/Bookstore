#include "../include/book.hpp"
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>

// 判断关键词是否合法（'|' 分隔）
bool Book::is_keyword_invalid(const std::string &keyword)
{
    // 1. 检查总长度
    if (keyword.size() > 60 || keyword.empty())
    {
        return true;
    }

    // 2. 检查字符合法性
    if (keyword.back() == '|')
    {
        return true;
    }
    for (char ch: keyword)
    {
        if (ch < 33 || ch > 126 || ch == '"')
        {
            return true;
        }
    }
    std::unordered_set<std::string> exist_keywords;
    int column = 0;
    while (column < keyword.size())
    {
        int start = column;
        while (column < keyword.size() && keyword[column] != '|')
        {
            ++column;
        }
        std::string sub_str = keyword.substr(start, column - start);
        if (sub_str.empty())
        {
            return true;
        }
        if (exist_keywords.find(sub_str) != exist_keywords.end())
        {
            return true;
        }
        exist_keywords.insert(sub_str);
        ++column;
    }
    return false;
}

// 复制构造函数
Book::Book(const Book &other)
{
    std::strncpy(book_name, other.book_name, sizeof(book_name));
    std::strncpy(author, other.author, sizeof(author));
    std::strncpy(keywords, other.keywords, sizeof(keywords));
    std::strncpy(isbn, other.isbn, sizeof(isbn));
    std::strncpy(price, other.price, sizeof(price));
    this->stock = other.stock;
}

// 默认构造
Book::Book()
{
    price[0] = '0';
    price[sizeof(price) - 1] = '\0';
}

// 根据 ISBN 构造
Book::Book(const std::string &isbn_)
{
    std::strncpy(isbn, isbn_.c_str(), sizeof(isbn) - 1);
    isbn[sizeof(isbn) - 1] = '\0';
    price[0] = '0';
    price[sizeof(price) - 1] = '\0';
}


// 获取关键词列表（按 '|' 分割）
std::vector<std::string> Book::get_keyword()
{
    std::vector<std::string> result;
    int column = 0;
    while (column < strlen(keywords))
    {
        int start = column;
        while (column < strlen(keywords) && keywords[column] != '|')
        {
            ++column;
        }
        std::string sub_str(keywords + start, column - start);
        result.push_back(sub_str);
        ++column;
    }
    return result;
}


// get/set 简单实现
std::string Book::get_book_name() { return std::string(book_name); }
std::string Book::get_author() { return std::string(author); }
std::string Book::get_isbn() { return std::string(isbn); }
std::string Book::get_price() { return std::string(price); }
int Book::get_stock() { return stock; }

void Book::set_book_name(const std::string &name)
{
    std::snprintf(book_name, sizeof(book_name), "%s", name.c_str());
}
void Book::set_author(const std::string &auth)
{
    std::snprintf(author, sizeof(author), "%s",auth.c_str());
}
void Book::set_keywords(const std::string &key)
{
    std::snprintf(keywords, sizeof(keywords), "%s", key.c_str());
}
void Book::set_isbn(const std::string &isbn_)
{
    std::snprintf(isbn, sizeof(isbn), "%s", isbn_.c_str());
}
void Book::set_price(const std::string &price_)
{
    std::snprintf(price, sizeof(price), "%s", price_.c_str());
}
void Book::set_stock(int s) { stock = s; }
