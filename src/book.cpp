#include "../include/Book.hpp"
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>

bool Book::is_keyword_repeated(const std::string &keyword)
{
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
        if (exist_keywords.find(sub_str) != exist_keywords.end())
        {
            return true;
        }
        exist_keywords.insert(sub_str);
        ++column;
    }
    return false;
}

Book::Book(const Book &other)
{
    strcpy(this->book_name, other.book_name);
    strcpy(this->author, other.author);
    strcpy(this->keywords, other.keywords);
    strcpy(this->isbn, other.isbn);
    this->price = other.price;
    this->stock = other.stock;
}

Book::Book() = default;

Book::Book(std::string isbn_) { strcpy(isbn, isbn_.c_str()); }

std::string Book::get_book_name() { return std::string(book_name); }
std::string Book::get_author() { return std::string(author); }
std::string Book::get_isbn() { return std::string(isbn); }
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
        std::string sub_str = std::string(keywords).substr(start, column - start);
        result.push_back(sub_str);
        ++column;
    }
    return result;
}
int Book::get_stock() { return stock; }
double Book::get_price() { return price; }

void Book::set_book_name(const std::string &name) { std::strncpy(book_name, name.c_str(), sizeof(book_name) - 1); }
void Book::set_author(const std::string &auth) { std::strncpy(author, auth.c_str(), sizeof(author) - 1); }
void Book::set_keywords(const std::string &key) { std::strncpy(keywords, key.c_str(), sizeof(keywords) - 1); }
void Book::set_isbn(const std::string &isbn_) { std::strncpy(isbn, isbn_.c_str(), sizeof(isbn) - 1); }
void Book::set_price(double p) { price = p; }
void Book::set_stock(int s) { stock = s; }
