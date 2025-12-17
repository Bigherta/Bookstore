#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <unordered_map>
#include "Token.hpp"


class UserManager;
class log;

const std::unordered_map<std::string, TokenType> TABLE = {
        {"su", LOGIN},        {"logout", LOGOUT},     {"register", REGISTER}, {"passwd", PASSWD},
        {"useradd", USERADD}, {"delete", DELETEUSER}, {"quit", EXIT},         {"exit", EXIT},
        {"show", SHOW},       {"report", REPORT},     {"finance", FINANCE},   {"employee", EMPLOYEE},
        {"log", LOG},         {"buy", BUY},           {"select", SELECT},     {"modify", MODIFY},
        {"import", IMPORT},   {"ISBN", ISBN},         {"name", NAME},         {"author", AUTHOR},
        {"keyword", KEYWORD}, {"price", PRICE}}; // 构建从字符串到枚举类的一个映射

class Parser
{
public:
    /**
     * @brief 将一行指令拆分为 TokenStream
     * @param line 输入指令行
     * @return 解析后的 TokenStream
     */
    TokenStream tokenize(const std::string &line, bool &is_valid) const;


    /**
     * @brief 将关键字字符串匹配到 TokenType 枚举
     * @param text 输入的字符串
     * @return 匹配的 TokenType，如果未匹配返回 BLANK
     */
    TokenType matchkeyword(const std::string &text) const;

    /**
     * @brief 检查字符串是否全部为整数
     * @param str 待检测字符串
     * @return true 如果字符串是数字
     */
    static bool isN(std::string) noexcept;


    /**
     * @brief 检查字符串是否为正实数
     * @param str 待检测字符串
     * @return true 如果字符串是数字或包含一个小数点
     */
    static bool isD(std::string) noexcept;


    /**
     * @brief 执行解析和指令处理
     * @param line 输入指令
     * @param userManager 用户管理器对象
     * @param Log 日志对象
     *
     * 根据指令类型调用相应的用户/书籍/日志操作，
     * 并处理输入的合法性和权限验证。
     */
    void execute(const std::string &, UserManager &, log &, bool &is_running);
};
#endif
