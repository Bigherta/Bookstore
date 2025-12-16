#pragma once
#include <iomanip>
#include <ostream>
#ifndef BOOK_HPP
#define BOOK_HPP

#include <cstring>
#include <string>
#include <vector>

/**
 * @class Book
 * @brief 表示书籍的类，包含书名、作者、关键词、ISBN、价格和库存信息。
 */
class Book
{
private:
    char book_name[61]{}; ///< 书名
    char author[61]{}; ///< 作者
    char keywords[61]{}; ///< 关键词，用 '|' 分隔
    char isbn[21]{}; ///< ISBN 编号
    char price[14]{}; ///< 价格
    int stock = 0; ///< 库存数量

public:
    /**
     * @brief 获取书名
     * @return std::string 书名
     */
    std::string get_book_name();

    /**
     * @brief 获取作者
     * @return std::string 作者名
     */
    std::string get_author();

    /**
     * @brief 获取 ISBN
     * @return std::string ISBN 编号
     */
    std::string get_isbn();

    /**
     * @brief 获取关键词列表
     * @return std::vector<std::string> 关键词向量
     */
    std::vector<std::string> get_keyword();

    /**
     * @brief 获取书籍价格
     * @return double 价格
     */
    std::string get_price();

    /**
     * @brief 获取库存数量
     * @return int 库存数量
     */
    int get_stock();

    /**
     * @brief 设置书名
     * @param name 新书名
     */
    void set_book_name(const std::string &name);

    /**
     * @brief 设置作者
     * @param author_ 新作者名
     */
    void set_author(const std::string &author_);

    /**
     * @brief 设置关键词
     * @param keywords_ 新关键词字符串（'|' 分隔）
     */
    void set_keywords(const std::string &keywords_);

    /**
     * @brief 设置 ISBN
     * @param isbn_ 新 ISBN 编号
     */
    void set_isbn(const std::string &isbn_);

    /**
     * @brief 设置价格
     * @param price_ 新价格
     */
    void set_price(const std::string &price_);

    /**
     * @brief 设置库存数量
     * @param stock_ 新库存数量
     */
    void set_stock(int stock_);

    /**
     * @brief 默认构造函数
     */
    Book();

    /**
     * @brief 根据字符串初始化 Book 对象
     * @param identifier 书籍的标识符（如 ISBN 或书名）
     */
    Book(const std::string &identifier);

    /**
     * @brief 拷贝构造函数
     * @param other 另一个 Book 对象
     */
    Book(const Book &other);

    /**
     * @brief 检查关键词是否合法
     * @param keyword 要检查的关键词
     * @return true 如果关键词不合法
     * @return false 如果关键词合法
     */
    static bool is_keyword_invalid(const std::string &keyword);

    /**
     * @brief 重载小于运算符，根据 ISBN 比较
     * @param other 另一本书
     * @return true 当前书的 ISBN 小于 other 的 ISBN
     * @return false 否则
     */
    bool operator<(const Book &other) const { return strcmp(this->isbn, other.isbn) < 0; }

    /**
     * @brief 重载相等运算符，根据 ISBN 判断是否相等
     * @param other 另一本书
     * @return true ISBN 相同
     * @return false ISBN 不同
     */
    bool operator==(const Book &other) const { return strcmp(this->isbn, other.isbn) == 0; }

    /**
     * @brief 输出书籍信息
     * @param os 输出流
     * @param other Book 对象
     * @return std::ostream& 输出流引用
     */
    friend std::ostream &operator<<(std::ostream &os, const Book &other)
    {
        std::string isbn_ = other.isbn;
        std::string name_ = other.book_name;
        std::string author_ = other.author;
        std::string keyword_ = other.keywords;
        os << isbn_ << '\t' << name_ << '\t' << author_ << '\t' << keyword_ << '\t';
        double price_val = std::stod(std::string(other.price));
        os << std::fixed << std::setprecision(2) << price_val << '\t';
        os << other.stock << '\n';
        return os;
    }
};

#endif
