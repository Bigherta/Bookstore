#pragma once
#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <memory>
#include <string>
#include <vector>

/**
 * @enum TokenType
 * @brief 枚举指令或关键字类型，用于解析用户输入
 */
enum TokenType {
    LOGIN,       ///< 登录指令
    LOGOUT,      ///< 登出指令
    REGISTER,    ///< 注册指令
    PASSWD,      ///< 修改密码指令
    USERADD,     ///< 添加用户指令
    DELETEUSER,  ///< 删除用户指令
    ISBN,        ///< ISBN 类型
    NAME,        ///< 书名类型
    AUTHOR,      ///< 作者类型
    KEYWORD,     ///< 关键词类型
    PRICE,       ///< 价格类型
    STOCK,       ///< 库存类型
    SHOW,        ///< 显示指令
    BUY,         ///< 购买指令
    SELECT,      ///< 选中书籍指令
    MODIFY,      ///< 修改指令
    IMPORT,      ///< 进货指令
    REPORT,      ///< 报表指令
    LOG,         ///< 日志指令
    FINANCE,     ///< 财务指令
    EMPLOYEE,    ///< 员工管理指令
    TEXT,        ///< 文本类型
    EXIT,        ///< 退出指令
    BLANK,       ///< 空白类型
};

/**
 * @struct Token
 * @brief 封装词法分析得到的基本单元
 */
struct Token {
    TokenType type{TokenType::BLANK}; ///< Token 类型
    std::string text{};                ///< 原始文本内容
    int column{0};                     ///< 在输入行中的列位置
};

/**
 * @class TokenStream
 * @brief 封装 Token 流，用于指令解析
 */
class TokenStream {
public:
    /**
     * @brief 默认构造函数
     */
    TokenStream() = default;

    /**
     * @brief 构造函数，使用移动语义初始化 Token 流
     * @param tokens 需要初始化的 Token 向量
     */
    explicit TokenStream(std::vector<Token> &&tokens);

    /**
     * @brief 查看当前 Token，不移动游标
     * @return std::shared_ptr<Token> 当前 Token 指针
     */
    const std::shared_ptr<Token> peek() const;

    /**
     * @brief 获取当前 Token，并移动游标到下一个
     * @return std::shared_ptr<Token> 当前 Token 指针
     */
    const std::shared_ptr<Token> get();

    /**
     * @brief 获取 Token 流的大小
     * @return int Token 数量
     */
    int size() const;

    /**
     * @brief 向 Token 流中推入新的 Token
     * @param token 要添加的 Token
     */
    void push(Token &&token);

private:
    std::vector<Token> tokens_{}; ///< 存储 Token 的向量
    int cursor_{0};                ///< 当前游标位置
};

#endif // TOKEN_HPP
