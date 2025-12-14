#pragma once
#include <iomanip>
#include <ostream>
#ifndef BOOK_HPP
#define BOOK_HPP

#include <cstring>
#include <string>
#include <vector>

class Book
{
private:
    char book_name[60]{};
    char author[60]{};
    char keywords[60]{};
    char isbn[20]{};
    double price = 0;
    int stock = 0;

public:
    std::string get_book_name();
    std::string get_author();
    std::string get_isbn();
    std::vector<std::string> get_keyword();
    double get_price();
    int get_stock();

    void set_book_name(const std::string &);
    void set_author(const std::string &);
    void set_keywords(const std::string &);
    void set_isbn(const std::string &);
    void set_price(double);
    void set_stock(int);
    Book();
    Book(std::string);
    Book(const Book &other);
    static bool is_keyword_repeated(const std::string &keyword);

    bool operator<(const Book &other) const { return strcmp(this->isbn, other.isbn) < 0; }
    bool operator==(const Book &other) const { return strcmp(this->isbn, other.isbn) == 0; }
    friend std::ostream &operator<<(std::ostream &os, const Book &other)
    {
        std::string isbn_ = other.isbn;
        std::string name_ = other.book_name;
        std::string author_ = other.author;
        std::string keyword_ = other.keywords;
        os << isbn_ << '\t' << name_ << '\t' << author_ << '\t' << keyword_ << '\t';
        os << std::fixed << std::setprecision(2) << other.price << '\t';
        os << other.stock << '\n';
        return os;
    }
};
#endif
