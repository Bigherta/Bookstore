#include <cstring>
#include <string>
#include <vector>

class Book
{
private:
    char book_name[60];
    char author[60];
    char keywords[60];
    char isbn[20];
    double price;
    int stock;

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
};
