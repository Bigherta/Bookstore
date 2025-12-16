#pragma once
#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "book.hpp"
#include "parser.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


using std::fstream;
using std::string;

class Book;

/**
 * @class MemoryRiver
 * @brief 基于二进制文件的模板存储管理类，用于顺序读写对象和管理少量附加信息。
 *
 * @tparam T 存储的对象类型
 * @tparam info_len 文件开头预留的整型信息数量，默认值为 2
 */
template<class T, int info_len = 2>
class MemoryRiver
{
private:
    fstream file; ///< 文件流对象，用于读写二进制文件
    string file_name; ///< 文件名
    int sizeofT = sizeof(T); ///< 存储对象的字节大小

public:
    /**
     * @brief 默认构造函数
     */
    MemoryRiver() = default;

    /**
     * @brief 带文件名的构造函数
     * @param file_name 要操作的文件名
     */
    MemoryRiver(const string &file_name) : file_name(file_name) {}

    /**
     * @brief 析构函数，关闭文件流
     */
    ~MemoryRiver()
    {
        if (file.is_open())
            file.close();
    }

    /**
     * @brief 初始化文件，如果文件不存在则创建并写入 info_len 个 int 默认值 0
     * @param FN 可选的文件名，若提供则覆盖类内 file_name
     */
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

    /**
     * @brief 读取文件开头第 n 个 int 信息到 tmp，1-based
     * @param tmp 读取的值
     * @param n 第 n 个 int（从 1 开始计数）
     */
    void get_info(int &tmp, int n)
    {
        if (n > info_len)
            return;

        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    /**
     * @brief 将 tmp 写入文件开头第 n 个 int，1-based
     * @param tmp 要写入的值
     * @param n 第 n 个 int（从 1 开始计数）
     */
    void write_info(int tmp, int n)
    {
        if (n > info_len)
            return;

        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    /**
     * @brief 将对象 t 写入文件末尾
     * @param t 要写入的对象
     * @return int 写入位置的偏移（字节数）
     */
    int write(T &t)
    {
        file.seekp(0, std::ios::end);
        int pos = file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        return pos;
    }

    /**
     * @brief 更新指定位置的对象
     * @param t 要写入的新对象
     * @param index 文件内偏移位置（字节数）
     */
    void update(T &t, const int index)
    {
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
    }

    /**
     * @brief 从指定位置读取对象
     * @param t 读取到的对象
     * @param index 文件内偏移位置（字节数）
     * @return true 读取成功
     * @return false 读取失败
     */
    bool read(T &t, const int index)
    {
        file.seekg(index);
        if (file.read(reinterpret_cast<char *>(&t), sizeofT))
        {
            return true;
        }
        return false;
    }

    /**
     * @brief 获取文件末尾偏移量（字节数），即文件大小
     * @return int 文件末尾位置（字节数）
     */
    int end()
    {
        file.seekg(0, std::ios::end);
        return file.tellg();
    }
};


struct index_to_head
{
    char name[61]{};
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
    MemoryRiver<index_to_head> file; // 记录的是索引到写入头位置的映射
    MemoryRiver<Block> book; // 记录的是书的value
public:
    storage() { init(); }

    storage(std::string s) : index_name(s) { init(); }

    /**
     * @brief 初始化索引和书籍存储，从文件中加载现有索引
     */
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

    /**
     * @brief 插入书籍到存储，维护块链和索引
     * @param value 要插入的书籍对象
     */
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

        // 没找到，新建相关信息
        t = index_to_head(index_name);
        Block new_block;
        new_block.size = 1;
        new_block.val[0] = value;
        t.head = book.write(new_block);
        int pos = file.end();
        index_pos_pair_.push_back(std::make_pair(index_name, pos));
        file.write(t);
    }

    /**
     * @brief 查找书籍是否存在
     * @param isbn 书籍 ISBN
     * @return true 如果书籍存在
     * @return false 如果书籍不存在
     */
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

        if (book_pos == -1)
        {
            return false;
        }

        index_to_head t;
        if (!file.read(t, book_pos))
        {
            return false;
        }

        Block temp;
        book.read(temp, t.head);

        while (true)
        {
            // 使用 std::lower_bound 查找 ISBN
            Book *pos = std::lower_bound(temp.val, temp.val + temp.size, Book(isbn));
            if (pos != temp.val + temp.size && *pos == Book(isbn))
            {
                return true;
            }

            if (temp.next_block == -1) // 已经是最后一个 block
                break;

            book.read(temp, temp.next_block); // 继续读取下一个 block
        }

        // 遍历完 block 都没找到
        return false;
    }


    /**
     * @brief 根据 ISBN 返回书籍副本
     * @param isbn 书籍 ISBN
     * @return Book 返回书籍对象，如果不存在返回默认 Book
     */
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

    /**
     * @brief 输出当前索引下的所有书籍信息
     */
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

    /**
     * @brief 输出指定 ISBN 的书籍信息
     * @param isbn 书籍 ISBN
     */
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

    /**
     * @brief 删除指定书籍，处理块合并
     * @param value 要删除的书籍对象
     */
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


    /**
     * @brief 分裂满块，将新书插入块中并更新块链
     * @param block 当前块
     * @param val 要插入的书籍
     * @param pos 插入位置索引
     * @param offset 当前块在文件中的偏移
     */
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

    /**
     * @brief 合并当前块和下一个块
     * @param block 当前块
     * @param offset 当前块在文件中的偏移
     */
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

    /**
     * @brief 在块中插入书籍，处理溢出和排序
     * @param temp 当前块
     * @param value 要插入的书籍
     * @param block_index 块在文件中的偏移
     * @return true 插入成功（包括已存在的情况）
     * @return false 插入失败
     */
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


    /**
     * @brief 在块中删除书籍
     * @param temp 当前块
     * @param value 要删除的书籍
     * @param block_index 块在文件中的偏移
     * @return true 删除成功
     * @return false 未找到书籍
     */
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


    /**
     * @brief 修改指定书籍的信息（ISBN、书名、作者、关键词、价格）
     *
     * @param isbn_ 新的 ISBN，如果为空则不修改
     * @param name_ 新书名，如果为空则不修改
     * @param author_ 新作者，如果为空则不修改
     * @param keywords_ 新关键词，如果为空则不修改
     * @param price_ 新价格，如果为空则不修改
     * @param selected_book 当前选中的书籍 ISBN
     * @return true 修改成功
     * @return false 修改失败（如参数超长、非法字符或 ISBN 冲突）
     */
    static bool modify_book(std::string isbn_, std::string name_, std::string author_, std::string keywords_,
                            std::string price_, std::string selected_book)
    {
        // 初始化 ISBN 存储
        storage<IsbnTag> isbn_storage;

        // 修改标志位
        bool is_change_isbn = false, is_change_name = false, is_change_author = false, is_change_keyword = false,
             is_change_price = false;

        // 验证并标记 ISBN 是否需要修改
        if (!isbn_.empty())
        {
            if (isbn_.size() > 20)
                return false; // 超出长度限制
            for (int i = 0; i < isbn_.size(); i++)
            {
                if (isbn_[i] < 33 || isbn_[i] > 126)
                    return false; // 包含非法字符
            }
            if (isbn_ == selected_book || isbn_storage.Find(isbn_))
            {
                return false; // 新 ISBN 已存在
            }
            is_change_isbn = true;
        }

        // 验证书名和作者是否需要修改
        if (!name_.empty() || !author_.empty())
        {
            if (name_.size() > 60 || author_.size() > 60)
                return false; // 超出长度限制
            for (int i = 0; i < name_.size(); i++)
            {
                if (name_[i] < 33 || name_[i] > 126 || name_[i] == '"')
                    return false; // 非法字符
            }
            for (int i = 0; i < author_.size(); i++)
            {
                if (author_[i] < 33 || author_[i] > 126 || author_[i] == '"')
                    return false; // 非法字符
            }
            if (!name_.empty())
                is_change_name = true;
            if (!author_.empty())
                is_change_author = true;
        }

        // 验证价格是否合法
        if (!price_.empty())
        {
            if (price_.size() > 13)
                return false; // 超出长度限制
            if (!Parser::isD(price_))
                return false; // 不是小数
            is_change_price = true;
        }

        // 验证关键词是否合法
        if (!keywords_.empty())
        {
            if (Book::is_keyword_invalid(keywords_))
                return false; // 关键词合法
            is_change_keyword = true;
        }

        // 复制当前书籍对象
        Book copied_book = isbn_storage.Copy(selected_book);
        std::string original_isbn = selected_book;
        std::string original_name = copied_book.get_book_name();
        std::string original_author = copied_book.get_author();
        std::vector<std::string> original_keyword = copied_book.get_keyword();

        Book NewBook = copied_book;

        // 从原索引中删除书籍
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

        // 更新书籍信息
        if (!isbn_.empty())
            NewBook.set_isbn(isbn_);
        if (!name_.empty())
            NewBook.set_book_name(name_);
        if (!author_.empty())
            NewBook.set_author(author_);
        if (!keywords_.empty())
            NewBook.set_keywords(keywords_);
        if (!price_.empty())
            NewBook.set_price(price_);

        // 更新索引：书名索引
        if (is_change_name)
        {
            storage<NameTag> new_name_storage(name_);
            new_name_storage.Insert(NewBook);
        }
        else
        {
            ori_name_storage.Insert(NewBook);
        }

        // 更新索引：作者索引
        if (is_change_author)
        {
            storage<AuthorTag> new_author_storage(author_);
            new_author_storage.Insert(NewBook);
        }
        else
        {
            ori_author_storage.Insert(NewBook);
        }

        // 更新索引：关键词索引
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

        // 更新 ISBN 索引
        isbn_storage.Insert(NewBook);

        return true; // 修改成功
    }

    /**
     * @brief 购买书籍，更新库存并返回总价
     * @param book_isbn 书籍 ISBN
     * @param num 购买数量
     * @param total_cost 输出参数，总价
     * @return true 购买成功
     * @return false 库存不足
     */
    bool buy_book(const std::string &book_isbn, int num, double &total_cost)
    {
        Book copied_book = Copy(book_isbn);
        int stock = copied_book.get_stock();
        double price = stod(copied_book.get_price());
        if (stock < num)
            return false;
        total_cost = price * num;
        std::cout << std::fixed << std::setprecision(2) << total_cost << '\n';
        change_stock(book_isbn, stock - num);
        return true;
    }

    /**
     * @brief 增加书籍库存
     * @param book_isbn 书籍 ISBN
     * @param num 增加数量
     */
    void import_book(const std::string &book_isbn, int num)
    {
        Book copied_book = Copy(book_isbn);
        int stock = copied_book.get_stock();
        change_stock(book_isbn, stock + num);
    }

    /**
     * @brief 修改书籍库存数量
     * @param book_isbn 书籍 ISBN
     * @param num 新库存数量
     */
    void change_stock(const std::string &book_isbn, int num)
    {
        Book copied_book = Copy(book_isbn);
        int stock = copied_book.get_stock();

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
