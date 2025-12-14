#pragma once
#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "book.hpp"

using std::fstream;
using std::string;

class Book;

template<class T, int info_len = 2>
class MemoryRiver
{
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);

public:
    MemoryRiver() = default;

    MemoryRiver(const string &file_name) : file_name(file_name) {}

    ~MemoryRiver()
    {
        if (file.is_open())
            file.close();
    }

    void initialise(string FN = "")
    {
        if (FN != "")
            file_name = FN;
        std::ifstream fin(file_name, std::ios::binary);
        bool is_exist = fin.is_open();
        fin.close();
        if (!is_exist)
        {
            file.open(file_name, std::ios::out | std::ios::binary);
            int tmp = 0;
            for (int i = 0; i < info_len; ++i)
                file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        }
        file.close();
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    }

    // 读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n)
    {
        if (n > info_len)
            return;
        /* your code here */

        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    // 将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n)
    {
        if (n > info_len)
            return;
        /* your code here */

        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    int write(T &t)
    {
        file.seekp(0, std::ios::end);
        int pos = file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeofT);

        return pos;
    }

    void update(T &t, const int index)
    {
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
    }

    bool read(T &t, const int index)
    {
        file.seekg(index);
        if (file.read(reinterpret_cast<char *>(&t), sizeofT))
        {
            return true;
        }
        return false;
    }
    int end()
    {
        file.seekg(0, std::ios::end);
        return file.tellg();
    }
};

struct index_to_head
{
    char name[65]{};
    int head = 0;
    index_to_head() {}
    index_to_head(std::string s)
    {
        std::memset(name, 0, sizeof(name));
        std::strncpy(name, s.c_str(), sizeof(name) - 1);
    }
};

struct IsbnTag
{
};
struct NameTag
{
};
struct AuthorTag
{
};
struct KeywordTag
{
};

template<typename Tag>
struct StorageTraits;

template<>
struct StorageTraits<IsbnTag>
{
    static constexpr const char *index_file = "isbn_index";
    static constexpr const char *book_file = "isbn_book";
};

template<>
struct StorageTraits<NameTag>
{
    static constexpr const char *index_file = "name_index";
    static constexpr const char *book_file = "name_book";
};

template<>
struct StorageTraits<AuthorTag>
{
    static constexpr const char *index_file = "author_index";
    static constexpr const char *book_file = "author_book";
};

template<>
struct StorageTraits<KeywordTag>
{
    static constexpr const char *index_file = "keyword_index";
    static constexpr const char *book_file = "keyword_book";
};


template<typename Tag>
class storage
{
private:
    struct Block
    {
        int next_block; // 下一个块的索引，若不存在，则为-1
        int size; // 当前块存储的数据量
        Book val[256]{};
        Block() : next_block(-1), size(0) {}
    };
    std::string index_name;
    std::vector<std::pair<std::string, int>> index_pos_pair_;
    MemoryRiver<index_to_head> file; // 记录的是书名到写入头位置的映射
    MemoryRiver<Block> book; // 记录的是书的value
public:
    storage() { init(); }

    storage(std::string s) : index_name(s) { init(); }

    void init()
    {
        file.initialise(StorageTraits<Tag>::index_file);
        book.initialise(StorageTraits<Tag>::book_file);
        index_to_head t;
        int start = 2 * sizeof(int);
        int end = file.end();
        while (start + sizeof(t) <= end)
        {
            file.read(t, start);
            index_pos_pair_.emplace_back(t.name, start);
            start += sizeof(t);
        }
    }

    void Insert(Book value)
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
                    if (temp.size < 256)
                    {
                        temp.val[temp.size] = value;
                        ++temp.size;
                        book.update(temp, block_index);
                        return;
                    }
                    else
                    {
                        split(temp, value, 256, block_index);
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

    bool Find(const std::string &isbn)
    {
        int book_pos = -1;
        for (int i = 0; i < index_pos_pair_.size(); i++)
        {
            if (index_pos_pair_[i].first == index_name)
            {
                book_pos = index_pos_pair_[i].second;
                break;
            }
        }

        if (book_pos == -1) // 没有空索引块，说明没有书籍
        {
            return false;
        }

        // 读取索引头
        index_to_head t;
        if (!file.read(t, book_pos))
        {
            return false;
        }

        // 遍历 book block 链表，查找 ISBN
        Block temp;
        book.read(temp, t.head);

        while (true)
        {
            // 使用 std::lower_bound 查找 ISBN
            Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
            if (pos != temp.val + temp.size && *pos == Book(isbn))
            {
                return true; // 找到 ISBN
            }

            if (temp.next_block == -1) // 已经是最后一个 block
                break;

            book.read(temp, temp.next_block); // 继续读取下一个 block
        }

        // 遍历完 block 都没找到
        return false;
    }

    Book Copy(const std::string &isbn)
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

    void Show()
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
            std::cout << "\n";
            return;
        }

        index_to_head t;
        if (!file.read(t, book_pos))
        {
            std::cout << "\n";
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
            std::cout << "\n";
            return;
        }
        else
        {
            for (int i = 0; i < temp.size; i++)
            {
                std::cout << temp.val[i];
            }
            return;
        }
    }

    void SearchIsbn(const std::string &isbn)
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

    void Delete(Book value)
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
                            if (temp.size + next.size <= 256)
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

    void split(Block &block, Book val, int pos, int offset)
    {
        int length = block.size + 1;
        std::vector<Book> storage;
        storage.resize(length);
        storage[pos] = val;
        for (int i = 0; i < pos; i++)
            storage[i] = block.val[i];
        for (int i = pos + 1; i < length; i++)
            storage[i] = block.val[i - 1];
        for (int i = 0; i < 256; i++)
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

    void merge(Block &block, int offset)
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
        for (int i = 0; i < 256; i++)
            block.val[i] = Book();

        for (int i = 0; i < length; i++)
        {
            block.val[i] = storage[i];
        }
        block.next_block = next_block.next_block;
        block.size = length;
        book.update(block, offset);
    }

    bool insert_book(Block &temp, Book value, int block_index)
    {
        Book *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
        int pos_index = pos - temp.val;
        if (pos_index < temp.size && *pos == value)
            return true;
        if (pos_index == temp.size)
            return false;
        if (temp.size < 256)
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

    bool delete_book(Block &temp, Book value, int block_index)
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

    static bool modify_book(std::string isbn_, std::string name_, std::string author_, std::string keywords_,
                            std::string price_, std::string selected_book)
    {
        // Implementation for modifying a book based on the type and modifier
        storage<IsbnTag> isbn_storage;

        bool is_change_isbn = false, is_change_name = false, is_change_author = false, is_change_keyword = false,
             is_change_price = false;

        if (!isbn_.empty())
        {
            if (isbn_.size() > 20)
            {
                return false; // exceed length limit
            }
            for (int i = 0; i < isbn_.size(); i++)
            {
                if (!std::isprint(isbn_[i]))
                    return false; // contain invalid char
            }
            if (isbn_ == selected_book || isbn_storage.Find(isbn_))
            {
                return false; // New ISBN already exists
            }
            is_change_isbn = true;
        }
        if (!name_.empty() || !author_.empty())
        {
            if (name_.size() > 60 || author_.size() > 60)
            {
                return false; // exceed length limit
            }
            for (int i = 0; i < name_.size(); i++)
            {
                if (!std::isprint(name_[i]) || name_[i] == '"')
                    return false; // contain invalid char
            }
            for (int i = 0; i < author_.size(); i++)
            {
                if (!std::isprint(author_[i]) || author_[i] == '"')
                    return false; // contain invalid char
            }
            if (!name_.empty())
                is_change_name = true;
            if (!author_.empty())
                is_change_author = true;
        }
        if (!price_.empty())
        {
            if (price_.size() > 13)
            {
                return false;
            }
            for (int i = 0; i < price_.size(); i++)
            {
                if (!std::isdigit(price_[i]) && price_[i] != '.')
                    return false; // contain invalid char
            }
            is_change_price = true;
        }


        if (!keywords_.empty())
        {
            if (Book::is_keyword_repeated(keywords_))
            {
                return false; // Keywords are repeated
            }
            is_change_keyword = true;
        }

        Book copied_book = isbn_storage.Copy(selected_book);
        std::string original_isbn = selected_book;
        std::string original_name = copied_book.get_book_name();
        std::string original_author = copied_book.get_author();
        std::vector<std::string> original_keyword = copied_book.get_keyword();

        Book NewBook = copied_book;

        isbn_storage.Delete(copied_book);

        storage<NameTag> ori_name_storage(original_name);
        ori_name_storage.Delete(copied_book);


        storage<AuthorTag> ori_author_storage(original_author);
        ori_author_storage.Delete(copied_book);


        for (const auto &kw: original_keyword)
        {
            storage<KeywordTag> kw_storage(kw);
            kw_storage.Delete(copied_book);
        }

        if (!isbn_.empty())
            NewBook.set_isbn(isbn_);
        if (!name_.empty())
            NewBook.set_book_name(name_);
        if (!author_.empty())
            NewBook.set_author(author_);
        if (!keywords_.empty())
            NewBook.set_keywords(keywords_);
        if (!price_.empty())
            NewBook.set_price(std::stod(price_));

        if (is_change_name)
        {
            storage<NameTag> new_name_storage(name_);
            new_name_storage.Insert(NewBook);
        }
        else
        {
            ori_name_storage.Insert(NewBook);
        }

        if (is_change_author)
        {
            storage<AuthorTag> new_author_storage(author_);
            new_author_storage.Insert(NewBook);
        }
        else
        {
            ori_author_storage.Insert(NewBook);
        }

        if (is_change_keyword)
        {
            std::vector<std::string> new_keywords = NewBook.get_keyword();
            for (auto &kw: new_keywords)
            {
                storage<KeywordTag> kw_storage(kw);
                kw_storage.Insert(NewBook);
            }
        }
        else
        {

            for (auto &kw: original_keyword)
            {
                storage<KeywordTag> kw_storage(kw);
                kw_storage.Insert(NewBook);
            }
        }

        isbn_storage.Insert(NewBook);
        return true;
    }

    bool buy_book(const std::string &book_isbn, int num, double &total_cost)
    {
        Book copied_book = Copy(book_isbn);
        int stock = copied_book.get_stock();
        double price = copied_book.get_price();
        if (stock < num)
            return false;
        total_cost = price * num;
        std::cout << std::fixed << std::setprecision(2) << total_cost << '\n';
        change_stock(book_isbn, stock - num);
        return true;
    }

    bool select_book(const std::string &book_isbn);

    void import_book(const std::string &book_isbn, int num)
    {
        Book copied_book = Copy(book_isbn);
        int stock = copied_book.get_stock();
        change_stock(book_isbn, stock + num);
    }

    void change_stock(const std::string &book_isbn, int num)
    {
        Book copied_book = Copy(book_isbn);
        int stock = copied_book.get_stock();
        std::vector<std::pair<std::string, int>> index_pos_pair_;

        std::string original_isbn = book_isbn;
        std::string original_name = copied_book.get_book_name();
        std::string original_author = copied_book.get_author();
        std::vector<std::string> original_keyword = copied_book.get_keyword();

        Book NewBook = copied_book;
        NewBook.set_stock(num);

        storage<IsbnTag> isbn_storage;
        isbn_storage.Delete(copied_book);

        storage<NameTag> ori_name_storage(original_name);
        ori_name_storage.Delete(copied_book);


        storage<AuthorTag> ori_author_storage(original_author);
        ori_author_storage.Delete(copied_book);


        for (const auto &kw: original_keyword)
        {
            storage<KeywordTag> kw_storage(kw);
            kw_storage.Delete(copied_book);
        }

        ori_name_storage.Insert(NewBook);

        ori_author_storage.Insert(NewBook);

        for (auto &kw: original_keyword)
        {
            storage<KeywordTag> kw_storage(kw);
            kw_storage.Insert(NewBook);
        }

        isbn_storage.Insert(NewBook);
    }
};

#endif
