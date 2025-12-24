#include "../include/book.hpp"
#include "../include/validator.hpp"
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>


int utf8_char_len(unsigned char ch)
{
    if ((ch & 0b10000000) == 0)
        return 1;
    // 0xxxxxxx → ASCII，1 字节

    else if ((ch & 0b11100000) == 0b11000000)
        return 2;
    // 110xxxxx → 两字节字符（特殊字符）

    else if ((ch & 0b11110000) == 0b11100000)
        return 3;
    // 1110xxxx → 三字节字符（常用汉字）

    else if ((ch & 0b11111000) == 0b11110000)
        return 4;
    // 11110xxx → 四字节字符（扩展汉字）

    else
        return -1;
    // 非法 UTF-8 首字节
}
bool is_hanzi(int code)
{
    return (code >= 0x4E00 && code <= 0x9FFF) || (code >= 0x3400 && code <= 0x4DBF) ||
           (code >= 0x20000 && code <= 0x2A6DF) || (code >= 0x2A700 && code <= 0x2B73F) ||
           (code >= 0x2B740 && code <= 0x2B81F) || (code >= 0x2B820 && code <= 0x2CEAF) ||
           (code >= 0x2CEB0 && code <= 0x2EBEF) || (code >= 0x30000 && code <= 0x3134F) ||
           (code >= 0x31350 && code <= 0x323AF);
}
bool is_special(int code_point)
{
    return code_point == 0x00B7 || code_point == 0x2014 || code_point == 0xFF08 || code_point == 0xFF09 ||
           code_point == 0xFF1A;
}
bool is_chinese_valid(std::string str)
{
    int column = 0;
    int count = 0;
    while (column < str.size())
    {
        int char_len = utf8_char_len((unsigned char) str[column]);
        int start = 0;
        int code_point;
        switch (char_len)
        {
            case 1: {
                code_point = str[column];
                if (code_point < 0x0021 || code_point > 0x007E || code_point == 0x0022)
                    return false;
                column++;
                break;
            }
            case 2: {
                if (column + 1 >= str.size())
                    return false;
                unsigned char ch1 = str[column];
                unsigned char ch2 = str[column + 1];
                if (ch1 < 0xC2 || ch1 > 0xDF)
                    return false;
                if ((ch2 & 0b11000000) != 0b10000000)
                    return false;
                int x = ch1 & 0b00011111;
                int y = ch2 & 0b00111111;
                code_point = x * 64 + y;
                if (code_point < 0x80)
                    return false;
                if (!is_special(code_point))
                    return false;
                column += 2;
                break;
            }
            case 3: {
                if (column + 2 >= str.size())
                    return false;
                unsigned char ch1 = str[column];
                if (ch1 < 0xE0 || ch1 > 0xEF)
                    return false;
                unsigned char ch2 = str[column + 1];
                if ((ch2 & 0b11000000) != 0b10000000)
                    return false;
                unsigned char ch3 = str[column + 2];
                if ((ch3 & 0b11000000) != 0b10000000)
                    return false;
                int x = ch1 & 0b00001111;
                int y = ch2 & 0b00111111;
                int z = ch3 & 0b00111111;
                code_point = x * 4096 + y * 64 + z;
                if (code_point < 0x800)
                    return false;
                if (!is_hanzi(code_point) && !is_special(code_point))
                    return false;
                column += 3;
                break;
            }
            case 4: {
                if (column + 3 >= str.size())
                    return false;
                unsigned char ch1 = str[column];
                if (ch1 < 0xF0 || ch1 > 0xF4)
                    return false;
                unsigned char ch2 = str[column + 1];
                if ((ch2 & 0b11000000) != 0b10000000)
                    return false;
                unsigned char ch3 = str[column + 2];
                if ((ch3 & 0b11000000) != 0b10000000)
                    return false;
                unsigned char ch4 = str[column + 3];
                if ((ch4 & 0b11000000) != 0b10000000)
                    return false;
                int x = ch1 & 0b00000111;
                int y = ch2 & 0b00111111;
                int z = ch3 & 0b00111111;
                int w = ch4 & 0b00111111;
                code_point = x * 262144 + y * 4096 + z * 64 + w;
                if (code_point < 0x10000 || code_point > 0x10FFFF)
                    return false;
                if (!is_hanzi(code_point))
                    return false;
                column += 4;
                break;
            }
            default:
                return false;
        }
        count++;
    }
    if (count > 60)
    {
        return false;
    }
    return true;
}
// 判断ISBN是否合法
bool Book::is_ISBN_valid(const std::string &ISBN)
{
    try
    {
        expect(ISBN.size()).le(20).And().ge(1);
        expect(ISBN).toMatch("^[\x21-\x7E]+$");
    }
    catch (...)
    {
        return false;
    }
    return true;
}

// 判断书名或作者名是否合法
bool Book::is_author_or_name_valid(const std::string &author_or_name) { return is_chinese_valid(author_or_name); }

// 判断关键词是否合法（'|' 分隔）
bool Book::is_keyword_invalid(const std::string &keyword)
{
    // 检查总长度与字符合法性
    if (!is_chinese_valid(keyword))
        return true;
    try
    {
        expect(keyword.back()).Not().toBe('|');
        expect(keyword.front()).Not().toBe('|');
    }
    catch (...)
    {
        return true;
    }
    std::unordered_set<std::string> exist_keywords;
    int column = 0, len = keyword.size();
    while (column < len)
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

void Book::set_book_name(const std::string &name) { std::snprintf(book_name, sizeof(book_name), "%s", name.c_str()); }
void Book::set_author(const std::string &auth) { std::snprintf(author, sizeof(author), "%s", auth.c_str()); }
void Book::set_keywords(const std::string &key) { std::snprintf(keywords, sizeof(keywords), "%s", key.c_str()); }
void Book::set_isbn(const std::string &isbn_) { std::snprintf(isbn, sizeof(isbn), "%s", isbn_.c_str()); }
void Book::set_price(const std::string &price_) { std::snprintf(price, sizeof(price), "%s", price_.c_str()); }
void Book::set_stock(int s) { stock = s; }
