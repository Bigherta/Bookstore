#include "../include/log.hpp"
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>


bool log::ShowFinance(long long count_)
{
    // 如果指定查询交易笔数为 0，直接输出空行，表示合法指令
    if (count_ == 0)
    {
        std::cout << '\n';
        return true;
    }

    // 初始化 MemoryRiver 对象，确保可以读取日志文件
    purchase_record.initialise("purchase");

    // 获取当前总交易笔数（存储在 info 位置 1）
    int cur_count;
    purchase_record.get_info(cur_count, 1);

    // 如果请求查询的交易笔数大于总交易笔数，则操作非法
    if (cur_count < count_)
    {
        return false;
    }

    // 获取日志文件的总字节数，用于遍历交易记录

    record temp; // 用于临时存储读取的记录
    int start_index = 2 * sizeof(int);
    int end_index = start_index + (cur_count - 1) * sizeof(record);
    double inc = 0; // 累计收入
    double exp = 0; // 累计支出

    // 遍历日志文件中的每一条记录
    for (int i = 1; i <= cur_count; i++)
    {
        // 读取记录到 temp
        purchase_record.read(temp, end_index);

        // 累加收入和支出
        inc += temp.income;
        exp += temp.expense;

        // 如果当前记录的 count 等于查询的 count，则输出累计金额
        if (i == count_)
        {
            std::cout << "+ " << std::fixed << std::setprecision(2) << inc;
            std::cout << " - " << std::fixed << std::setprecision(2) << exp;
            std::cout << '\n';
            return true;
        }
        end_index -= sizeof(record);
    }

    // 如果 count_ = -1，则输出所有交易的总额
    if (count_ == -1)
    {
        std::cout << "+ " << std::fixed << std::setprecision(2) << inc;
        std::cout << " - " << std::fixed << std::setprecision(2) << exp;
        std::cout << '\n';
        return true;
    }
    return false;
}

void log::ReportFinance()
{

    // 初始化 MemoryRiver 对象，确保可以读取日志文件
    purchase_record.initialise("purchase");

    // 获取当前总交易笔数（存储在 info 位置 1）
    int cur_count;
    purchase_record.get_info(cur_count, 1);

    // 获取日志文件的总字节数，用于遍历交易记录
    if (cur_count == 0)
    {
        std::cout << "所有交易总额为：\n";
        std::cout << "+ 0.00 - 0.00\n";
        return;
    }

    record temp; // 用于临时存储读取的记录
    int start_index = 2 * sizeof(int);
    int end_index = start_index + (cur_count - 1) * sizeof(record);
    double inc = 0; // 累计收入
    double exp = 0; // 累计支出

    // 遍历日志文件中的每一条记录
    for (int i = 1; i <= cur_count; i++)
    {
        // 读取记录到 temp
        purchase_record.read(temp, start_index);

        // 累加收入和支出
        inc += temp.income;
        exp += temp.expense;

        std::cout << "+ " << std::fixed << std::setprecision(2) << temp.income;
        std::cout << " - " << std::fixed << std::setprecision(2) << temp.expense;
        std::cout << '\n';

        start_index += sizeof(record);
    }

    // 最后输出所有交易的总额
    std::cout << "所有交易总额为：\n";
    std::cout << "+ " << std::fixed << std::setprecision(2) << inc;
    std::cout << " - " << std::fixed << std::setprecision(2) << exp;
    std::cout << '\n';
}

void log::add_trading(double income, double expense)
{
    // 初始化日志存储
    purchase_record.initialise("purchase");

    // 获取当前总交易笔数
    int cur_count;
    purchase_record.get_info(cur_count, 1);

    // 新交易的交易编号 = 当前总交易数 + 1
    ++cur_count;

    // 更新日志文件中的总交易笔数
    purchase_record.write_info(cur_count, 1);

    // 构造新交易记录
    record new_trade = {cur_count, income, expense};

    // 将新交易记录写入日志
    purchase_record.write(new_trade);
}

void log::change_opt(int privilege, std::string name, std::string info, operate &opt)
{
    std::string info_;
    switch (privilege)
    {
        case 0: {
            info_ += "visitor ";
            break;
        }
        case 1: {
            info_ += "customer ";
            break;
        }
        case 3: {
            info_ += "worker ";
            break;
        }
        case 7: {
            info_ += "manager ";
            break;
        }
    }
    info_ += name;
    info_ += info;
    std::snprintf(opt.operation, sizeof(opt.operation), "%s", info_.c_str());
    opt.privilege = privilege;
}

void log::add_operation(int privilege, std::string name, TokenType type)
{
    // 初始化日志存储
    operation_record.initialise("operation");
    operate opt;
    switch (type)
    {

        case LOGIN: {
            change_opt(privilege, name, " log in\n", opt);
            break;
        }
        case LOGOUT: {
            change_opt(privilege, name, " log out\n", opt);
            break;
        }
        case REGISTER: {
            change_opt(privilege, name, " register a new account\n", opt);
            break;
        }
        case PASSWD: {
            change_opt(privilege, name, " change other's password\n", opt);
            break;
        }
        case USERADD: {
            change_opt(privilege, name, " add a new user\n", opt);
            break;
        }
        case DELETEUSER: {
            change_opt(privilege, name, " delete a user\n", opt);
            break;
        }

        case SHOW: {
            change_opt(privilege, name, " show the books\n", opt);
            break;
        }

        case FINANCE: {
            change_opt(privilege, name, " show the finance\n", opt);
            break;
        }

        case BUY: {
            change_opt(privilege, name, " buy some books\n", opt);
            break;
        }
        case SELECT: {
            change_opt(privilege, name, " select a book\n", opt);
            break;
        }
        case MODIFY: {
            change_opt(privilege, name, " modify a book\n", opt);
            break;
        }
        case IMPORT: {
            change_opt(privilege, name, " import some books\n", opt);
            break;
        }
        case REPORT: {
            change_opt(privilege, name, " check the report\n", opt);
            break;
        }
        case LOG: {
            change_opt(privilege, name, " check the log\n", opt);
            break;
        }
        case EXIT: {
            change_opt(privilege, name, " exit\n", opt);
            break;
        }
        default: {
            change_opt(privilege, name, " invalid operation\n", opt);
            break;
        }
    }
    // 将新操作记录写入日志
    operation_record.write(opt);
}

void log::ReportEmployee()
{
    operation_record.initialise("operation");
    int start_index = 2 * sizeof(int);
    int end_index = operation_record.end();
    operate opt;
    while (start_index + sizeof(operate) <= end_index)
    {
        operation_record.read(opt, start_index);
        if (opt.privilege == 3)
        {
            std::cout << opt.operation;
        }
        start_index += sizeof(operate);
    }
}

void log::Log()
{
    std::cout << "以下是操作系统日志\n";
    operation_record.initialise("operation");
    int start_index = 2 * sizeof(int);
    int end_index = operation_record.end();
    operate opt;
    while (start_index + sizeof(operate) <= end_index)
    {
        operation_record.read(opt, start_index);

        std::cout << opt.operation;

        start_index += sizeof(operate);
    }
    std::cout << "以下是财务交易情况\n";
    ReportFinance();
}
