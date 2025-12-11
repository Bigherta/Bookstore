#include <string>
#include <unordered_map>

enum Command
{
    LOGIN,
    LOGOUT,
    REGISTER,
    PASSWD,
    USERADD,
    DELETEUSER,
    INVALID,
    EXIT,
    BLANK
};

const std::unordered_map<std::string, Command> TABLE = {
        {"su", LOGIN},        {"logout", LOGOUT},     {"register", REGISTER}, {"passwd", PASSWD},
        {"useradd", USERADD}, {"delete", DELETEUSER}, {"exit", EXIT}}; // 构建从字符串到枚举类的一个映射

class Parser
{
public:
    Command matchkeyword(const std::string &text);
};
