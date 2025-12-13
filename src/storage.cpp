#include "../include/storage.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>
#include <vector>

void storage::init(std::vector<std::pair<std::string, int>> &index_pos_pair_)
{
    file.initialise("index");
    book.initialise("book");
    index_to_head t;
    int start_index = 2 * sizeof(int);
    int file_end = file.end();
    while (start_index + sizeof(t) <= file_end)
    {
        file.read(t, start_index);
        index_pos_pair_.push_back(std::make_pair(t.name, start_index));
        start_index += sizeof(t);
    }
}


void storage::split(Block &block, Book val, int pos, int offset)
{
    int length = block.size + 1;
    std::vector<Book> storage;
    storage.resize(length);
    storage[pos] = val;
    for (int i = 0; i < pos; i++)
        storage[i] = block.val[i];
    for (int i = pos + 1; i < length; i++)
        storage[i] = block.val[i - 1];
    for (int i = 0; i < 200; i++)
        block.val[i] = Book();

    int left = length / 2;
    int right = length - left;
    for (int i = 0; i < left; i++)
    {
        block.val[i] = storage[i];
    }
    block.size = left;
    Block new_block;
    new_block.size = right;
    for (int i = left; i < length; i++)
    {
        new_block.val[i - left] = storage[i];
    }
    int next_point = block.next_block;
    new_block.next_block = next_point;
    block.next_block = book.write(new_block);
    book.update(block, offset);
}
// 裂块

bool storage::insert_book(Block &temp, Book value, int block_index)
{
    Book *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
    int pos_index = pos - temp.val;
    if (pos_index < temp.size && *pos == value)
        return true;
    if (pos_index == temp.size)
        return false;
    if (temp.size < 200)
    {
        for (int i = temp.size; i > pos_index; --i)
        {
            temp.val[i] = temp.val[i - 1];
        }
        temp.val[pos_index] = value;
        ++temp.size;
        book.update(temp, block_index);
        return true;
    }
    else
    {
        split(temp, value, pos_index, block_index);
        return true;
    }
}
// 插入值的具体操作
void storage::Insert(Book value, std::vector<std::pair<std::string, int>> &index_pos_pair_)
{
    index_to_head t;

    for (int i = 0; i < index_pos_pair_.size(); i++)
    {
        if (index_pos_pair_[i].first == index_name)
        {
            int book_pos = index_pos_pair_[i].second;
            if (!file.read(t, book_pos))
                return;
            Block temp;
            if (!book.read(temp, t.head))
                return;
            int block_index = t.head;
            while (temp.next_block != -1)
            {
                if (insert_book(temp, value, block_index))
                {
                    return;
                }
                block_index = temp.next_block;
                book.read(temp, temp.next_block);
            }
            if (insert_book(temp, value, block_index))
                return;
            else
            {
                if (temp.size < 200)
                {
                    temp.val[temp.size] = value;
                    ++temp.size;
                    book.update(temp, block_index);
                    return;
                }
                else
                {
                    split(temp, value, 200, block_index);
                }
            }
            return;
        }
    }
    t = index_to_head(index_name);
    Block new_block;
    new_block.size = 1;
    new_block.val[0] = value;
    t.head = book.write(new_block);
    int pos = file.end();
    index_pos_pair_.push_back(std::make_pair(index_name, pos));
    file.write(t);
}
// 插入一个值
void storage::Show(const std::vector<std::pair<std::string, int>> &index_pos_pair_)
{
    int book_pos = 0;
    bool is_exist = false;
    for (int i = 0; i < index_pos_pair_.size(); i++)
    {
        if (index_pos_pair_[i].first == index_name)
        {
            is_exist = true;
            book_pos = index_pos_pair_[i].second;
            break;
        }
    }
    if (!is_exist)
    {
        std::cout << '\n';
        return;
    }

    index_to_head t;
    if (!file.read(t, book_pos))
    {
        std::cout << '\n';
        return;
    }

    bool is_empty = true;

    Block temp;

    book.read(temp, t.head);

    while (temp.next_block != -1)
    {
        if (temp.size != 0)
            is_empty = false;
        for (int i = 0; i < temp.size; i++)
        {
            std::cout << temp.val[i];
        }
        book.read(temp, temp.next_block);
    }

    if (temp.size != 0)
        is_empty = false;
    if (is_empty)
    {
        std::cout << '\n';
        return;
    }
    else
    {
        for (int i = 0; i < temp.size; i++)
        {
            std::cout << temp.val[i];
        }
        std::cout << '\n';
        return;
    }
}
// 显示索引对应的所有图书

void storage::SearchIsbn(const std::string &isbn)
{
    storage isbn_storage;
    std::vector<std::pair<std::string, int>> index_pos_pair_;
    isbn_storage.init(index_pos_pair_);
    int book_pos = 0;
    bool is_exist = false;
    for (int i = 0; i < index_pos_pair_.size(); i++)
    {
        if (index_pos_pair_[i].first.empty())
        {
            is_exist = true;
            book_pos = index_pos_pair_[i].second;
            break;
        }
    }
    if (!is_exist)
    {
        return;
    }

    index_to_head t;
    if (!file.read(t, book_pos))
    {
        return;
    }

    bool is_empty = true;

    Block temp;

    book.read(temp, t.head);

    while (temp.next_block != -1)
    {
        if (temp.size != 0)
            is_empty = false;
        Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
        if (pos == temp.val + temp.size || !(*pos == Book(isbn)))
        {
            book.read(temp, temp.next_block);
        }
        else
        {
            std::cout << *pos;
            return;
        }
    }

    if (temp.size != 0)
        is_empty = false;
    if (is_empty)
    {
        std::cout << '\n';
        return;
    }
    else
    {
        Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
        if (pos == temp.val + temp.size || !(*pos == Book(isbn)))
        {
            std::cout << '\n';
            return;
        }
        else
        {
            std::cout << *pos;
            return;
        }
    }
}

bool storage::Find(const std::string &isbn)
{
    storage isbn_storage;
    std::vector<std::pair<std::string, int>> index_pos_pair_;
    isbn_storage.init(index_pos_pair_);
    int book_pos = 0;
    bool is_exist = false;
    for (int i = 0; i < index_pos_pair_.size(); i++)
    {
        if (index_pos_pair_[i].first.empty())
        {
            is_exist = true;
            book_pos = index_pos_pair_[i].second;
            break;
        }
    }
    if (!is_exist)
    {
        return false;
    }

    index_to_head t;
    if (!file.read(t, book_pos))
    {
        return false;
    }

    bool is_empty = true;

    Block temp;

    book.read(temp, t.head);

    while (temp.next_block != -1)
    {
        if (temp.size != 0)
            is_empty = false;
        Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
        if (pos == temp.val + temp.size || !(*pos == Book(isbn)))
        {
            book.read(temp, temp.next_block);
        }
        else
        {
            return true;
        }
    }

    if (temp.size != 0)
        is_empty = false;
    if (is_empty)
    {
        return false;
    }
    else
    {
        Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
        if (pos == temp.val + temp.size || !(*pos == Book(isbn)))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}


bool storage::delete_book(Block &temp, Book value, int block_index)
{
    Book *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
    if (pos == temp.val + temp.size || !(*pos == value))
    {
        return false;
    }
    else
    {
        int pos_index = pos - temp.val;
        for (int i = pos_index; i < temp.size - 1; i++)
        {
            temp.val[i] = temp.val[i + 1];
        }
        temp.val[temp.size - 1] = Book();
        --temp.size;
        book.update(temp, block_index);
    }
    return true;
}
// 删除值的具体操作

void storage::merge(Block &block, int offset)
{
    Block next_block;
    book.read(next_block, block.next_block);
    int length = block.size + next_block.size;
    std::vector<Book> storage;
    storage.resize(length);
    for (int i = 0; i < block.size; i++)
    {
        storage[i] = block.val[i];
    }
    for (int i = block.size; i < length; i++)
    {
        storage[i] = next_block.val[i - block.size];
    }
    for (int i = 0; i < 200; i++)
        block.val[i] = Book();

    for (int i = 0; i < length; i++)
    {
        block.val[i] = storage[i];
    }
    block.next_block = next_block.next_block;
    block.size = length;
    book.update(block, offset);
}
// 合并块

void storage::Delete(Book value, std::vector<std::pair<std::string, int>> &index_pos_pair_)
{
    index_to_head t;
    for (int i = 0; i < index_pos_pair_.size(); i++)
    {
        if (index_pos_pair_[i].first == index_name)
        {
            int book_pos = index_pos_pair_[i].second;
            if (!file.read(t, book_pos))
                return;
            Block temp;

            if (!book.read(temp, t.head))
                return;
            int block_index = t.head;
            while (temp.next_block != -1)
            {
                if (!delete_book(temp, value, block_index))
                {
                    block_index = temp.next_block;
                    book.read(temp, temp.next_block);
                }
                else
                {
                    Block next;
                    while (temp.next_block != -1)
                    {

                        book.read(next, temp.next_block);
                        if (temp.size + next.size <= 200)
                            merge(temp, block_index);
                        else
                            break;
                    }
                    return;
                }
            }
            if (!delete_book(temp, value, block_index))
            {
                return;
            }
        }
    }
}
// 删除对应索引与值

Book storage::Copy(const std::string &isbn)
{
    storage isbn_storage;
    std::vector<std::pair<std::string, int>> index_pos_pair_;
    isbn_storage.init(index_pos_pair_);
    int book_pos = 0;
    bool is_exist = false;
    for (int i = 0; i < index_pos_pair_.size(); i++)
    {
        if (index_pos_pair_[i].first.empty())
        {
            is_exist = true;
            book_pos = index_pos_pair_[i].second;
            break;
        }
    }
    if (!is_exist)
    {
        return Book();
    }

    index_to_head t;
    if (!file.read(t, book_pos))
    {
        return Book();
    }

    Block temp;

    book.read(temp, t.head);

    while (temp.next_block != -1)
    {
        Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
        if (pos == temp.val + temp.size || !(*pos == Book(isbn)))
        {
            book.read(temp, temp.next_block);
        }
        else
        {
            return *pos;
        }
    }

    Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
    if (pos == temp.val + temp.size || !(*pos == Book(isbn)))
    {
        return Book();
    }
    else
    {
        return *pos;
    }
}

bool storage::modify_book(TokenType type, std::string modifier, std::string isbn)
{
    // Implementation for modifying a book based on the type and modifier
    storage isbn_storage;
    std::vector<std::pair<std::string, int>> index_pos_pair_;
    isbn_storage.init(index_pos_pair_);
    switch (type)
    {
        case ISBN: {
            if (modifier.size() > 20)
            {
                return false; // exceed length limit
            }
            for (int i = 0; i < modifier.size(); i++)
            {
                if (!std::isprint(modifier[i]))
                    return false; // contain invalid char
            }
            if (isbn_storage.Find(modifier))
            {
                return false; // New ISBN already exists
            }
            break;
        }
        case NAME:
        case AUTHOR: {
            if (modifier.size() > 60)
            {
                return false; // exceed length limit
            }
            for (int i = 0; i < modifier.size(); i++)
            {
                if (!std::isprint(modifier[i]) || modifier[i] == '"')
                    return false; // contain invalid char
            }
            break;
        }
        case PRICE: {
            if (modifier.size() > 13)
            {
                return false;
            }
            for (int i = 0; i < modifier.size(); i++)
            {
                if (!std::isdigit(modifier[i]) && modifier[i] != '.')
                    return false; // contain invalid char
            }
            break;
        }
        case KEYWORD: {
            if (Book::is_keyword_repeated(modifier))
            {
                return false; // Keywords are repeated
            }
        }
        default:
            return false;
    }

    Book copied_book = isbn_storage.Copy(isbn);
    std::string original_isbn = isbn;
    std::string original_name = copied_book.get_book_name();
    std::string original_author = copied_book.get_author();
    std::vector<std::string> original_keyword = copied_book.get_keyword();
    Book NewBook = copied_book;

    isbn_storage.Delete(copied_book, index_pos_pair_);
    storage ori_name_storage = storage(original_name);
    ori_name_storage.Delete(copied_book, index_pos_pair_);
    storage ori_author_storage = storage(original_author);
    ori_author_storage.Delete(copied_book, index_pos_pair_);
    for (const auto &kw: original_keyword)
    {
        storage ori_keyword_storage = storage(kw);
        ori_keyword_storage.Delete(copied_book, index_pos_pair_);
    }

    switch (type)
    {
        case TokenType::NAME:
            // Modify title logic
            {
                NewBook.set_book_name(modifier);
                storage new_name_storage = storage(modifier);
                isbn_storage.Insert(NewBook, index_pos_pair_);
                new_name_storage.Insert(NewBook, index_pos_pair_);
                ori_author_storage.Insert(NewBook, index_pos_pair_);
                for (const auto &kw: original_keyword)
                {
                    storage ori_keyword_storage = storage(kw);
                    ori_keyword_storage.Insert(NewBook, index_pos_pair_);
                }
                break;
            }
        case TokenType::AUTHOR:

            // Modify author logic
            {
                NewBook.set_author(modifier);
                storage new_author_storage = storage(modifier);
                isbn_storage.Insert(NewBook, index_pos_pair_);
                new_author_storage.Insert(NewBook, index_pos_pair_);
                ori_name_storage.Insert(NewBook, index_pos_pair_);
                for (const auto &kw: original_keyword)
                {
                    storage ori_keyword_storage = storage(kw);
                    ori_keyword_storage.Insert(NewBook, index_pos_pair_);
                }
                break;
            }
        case TokenType::ISBN:
            // Modify ISBN logic
            {
                NewBook.set_isbn(modifier);
                isbn_storage.Insert(NewBook, index_pos_pair_);
                ori_name_storage.Insert(NewBook, index_pos_pair_);
                ori_author_storage.Insert(NewBook, index_pos_pair_);
                for (const auto &kw: original_keyword)
                {
                    storage ori_keyword_storage = storage(kw);
                    ori_keyword_storage.Insert(NewBook, index_pos_pair_);
                }
                break;
            }
        case TokenType::PRICE:
            // Modify price logic
            {
                NewBook.set_price(std::stod(modifier));
                isbn_storage.Insert(NewBook, index_pos_pair_);
                ori_name_storage.Insert(NewBook, index_pos_pair_);
                ori_author_storage.Insert(NewBook, index_pos_pair_);
                for (const auto &kw: original_keyword)
                {
                    storage ori_keyword_storage = storage(kw);
                    ori_keyword_storage.Insert(NewBook, index_pos_pair_);
                }
                break;
            }
            break;
        case TokenType::KEYWORD:
            // Modify keyword logic
            {
                NewBook.set_keywords(modifier);
                isbn_storage.Insert(NewBook, index_pos_pair_);
                ori_name_storage.Insert(NewBook, index_pos_pair_);
                ori_author_storage.Insert(NewBook, index_pos_pair_);
                int column = 0;
                while (column < modifier.size())
                {
                    int start = column;
                    while (column < modifier.size() && modifier[column] != '|')
                    {
                        ++column;
                    }
                    std::string sub_str = modifier.substr(start, column - start);
                    storage new_keyword_storage = storage(sub_str);
                    new_keyword_storage.Insert(NewBook, index_pos_pair_);
                    ++column;
                }
                break;
            }
        case TokenType::STOCK:
            // Modify stock logic
            {
                NewBook.set_stock(std::stoi(modifier));
                isbn_storage.Insert(NewBook, index_pos_pair_);
                ori_name_storage.Insert(NewBook, index_pos_pair_);
                ori_author_storage.Insert(NewBook, index_pos_pair_);
                for (const auto &kw: original_keyword)
                {
                    storage ori_keyword_storage = storage(kw);
                    ori_keyword_storage.Insert(NewBook, index_pos_pair_);
                }
                break;
            }
        default:
            return false;
    }
    return true;
}

bool storage::buy_book(const std::string &book_isbn, int num, double &total_cost)
{
    Book copied_book = Copy(book_isbn);
    int stock = copied_book.get_stock();
    double price = copied_book.get_price();
    if (stock < num)
        return false;
    total_cost = price * num;
    std::cout << std::fixed << std::setprecision(2) << total_cost << '\n';
    std::string outcome = std::to_string(stock - num);
    modify_book(TokenType::STOCK, outcome, book_isbn);
    return true;
}

void storage::import_book(const std::string &book_isbn, int num)
{
    Book copied_book = Copy(book_isbn);
    int stock = copied_book.get_stock();

    std::string outcome = std::to_string(stock + num);
    modify_book(TokenType::STOCK, outcome, book_isbn);
}
