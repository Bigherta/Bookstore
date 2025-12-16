#include "../include/log.hpp"
#include "../include/parser.hpp"
#include "../include/user.hpp"

/**
 * @brief 程序入口
 * 
 * 初始化解析器、用户管理器和日志模块
 * 逐行读取输入指令，并交给 Parser 执行
 */
int main()
{
    Parser parser;           // 指令解析器
    UserManager userManager; // 用户管理器
    log Log;                 // 日志记录器
    std::string line;        // 存储用户输入的一行指令

    // 循环读取标准输入的每一行
    while (std::getline(std::cin, line))
    {
        bool is_running = true;

        parser.execute(line, userManager, Log, is_running); // 执行输入指令

        if (!is_running || std::cin.eof())
        {
             return 0;
        }
    }
    return 0;
}
