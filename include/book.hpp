#include <cstring>

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
    bool operator<(const Book &other) const { return strcmp(this->isbn, other.isbn) < 0; }
    bool operator==(const Book &other) const { return strcmp(this->isbn, other.isbn) == 0; }
};
