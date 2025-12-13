#include <string>
#include <unordered_map>
#include "./Token.hpp"



class UserManager;
class log;

const std::unordered_map<std::string, TokenType> TABLE = {
        {"su", LOGIN},          {"logout", LOGOUT}, {"register", REGISTER}, {"passwd", PASSWD}, {"useradd", USERADD},
        {"delete", DELETEUSER}, {"exit", EXIT},     {"show", SHOW},         {"report", REPORT}, {"finance", FINANCE},
        {"employee", EMPLOYEE}, {"log", LOG},       {"buy", BUY},           {"select", SELECT}, {"modify", MODIFY},
        {"import", IMPORT},     {"ISBN", ISBN},     {"name", NAME},         {"author", AUTHOR}, {"keyword", KEYWORD},
        {"price", PRICE}}; // 构建从字符串到枚举类的一个映射

class Parser
{
public:
    TokenStream tokenize(const std::string &line) const; // 将一行源码进行语义分解
    TokenType matchkeyword(const std::string &text) const; // 将字符串匹配成对应的枚举类
    static bool isLetterChar(char ch) noexcept; // 判断是否是字母
    static bool isNumberChar(char ch) noexcept; // 判断是否是数字
    static bool isN(std::string) noexcept; // 判断是否是整数
    static bool isD(std::string) noexcept; // 判断是否是小数
    void execute(const std::string&, UserManager &, log &); // 执行语义分析
};
