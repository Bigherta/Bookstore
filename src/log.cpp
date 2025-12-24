#include "../include/Log.hpp"
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>

// 显示财务信息
bool Log::ShowFinance(std::string &result, long long count_)
{
    std::ostringstream oss;

    if (count_ == 0)
    {
        oss << "\n";
        result += oss.str();
        return true;
    }

    purchase_record.initialise("purchase");

    int cur_count;
    purchase_record.get_info(cur_count, 1);

    if (count_ != -1 && cur_count < count_)
        return false;

    record temp;
    int start_index = 2 * sizeof(int);
    int end_index = start_index + (cur_count - 1) * sizeof(record);
    double inc = 0;
    double exp = 0;

    for (int i = 1; i <= cur_count; i++)
    {
        purchase_record.read(temp, end_index);
        inc += temp.income;
        exp += temp.expense;

        if (i == count_)
        {
            oss << "+ " << std::fixed << std::setprecision(2) << inc
                << " - " << std::fixed << std::setprecision(2) << exp << "\n";
            result += oss.str();
            return true;
        }
        end_index -= sizeof(record);
    }

    if (count_ == -1)
    {
        oss << "+ " << std::fixed << std::setprecision(2) << inc
            << " - " << std::fixed << std::setprecision(2) << exp << "\n";
        result += oss.str();
        return true;
    }

    return false;
}

// 报告财务信息
void Log::ReportFinance(std::string &result)
{
    std::ostringstream oss;
    purchase_record.initialise("purchase");

    int cur_count;
    purchase_record.get_info(cur_count, 1);

    if (cur_count == 0)
    {
        oss << "+ 0.00 - 0.00\n";
        result += oss.str();
        return;
    }

    record temp;
    int start_index = 2 * sizeof(int);
    double inc = 0;
    double exp = 0;

    for (int i = 1; i <= cur_count; i++)
    {
        purchase_record.read(temp, start_index);
        inc += temp.income;
        exp += temp.expense;

        oss << "+ " << std::fixed << std::setprecision(2) << temp.income
            << " - " << std::fixed << std::setprecision(2) << temp.expense << "\n";

        start_index += sizeof(record);
    }
    result += oss.str();
}

// 报告员工操作
void Log::ReportEmployee(std::string &result)
{
    std::ostringstream oss;
    operation_record.initialise("operation");
    int start_index = 2 * sizeof(int);
    int end_index = operation_record.end();
    operate opt;

    while (start_index + sizeof(operate) <= end_index)
    {
        operation_record.read(opt, start_index);
        if (opt.privilege == 3)
        {
            oss << opt.operation;
        }
        start_index += sizeof(operate);
    }

    result += oss.str();
}

// 显示所有日志
void Log::Logger(std::string &result)
{
    std::ostringstream oss;
    oss << "System Log:\n";

    operation_record.initialise("operation");
    int start_index = 2 * sizeof(int);
    int end_index = operation_record.end();
    operate opt;

    while (start_index + sizeof(operate) <= end_index)
    {
        operation_record.read(opt, start_index);
        oss << opt.operation;
        start_index += sizeof(operate);
    }

    oss << "Finance Log:\n";
    result += oss.str();

    ReportFinance(result);
}

// 添加交易记录
void Log::add_trading(double income, double expense)
{
    purchase_record.initialise("purchase");

    int cur_count;
    purchase_record.get_info(cur_count, 1);
    ++cur_count;

    purchase_record.write_info(cur_count, 1);

    record new_trade = {cur_count, income, expense};
    purchase_record.write(new_trade);
}

// 更改操作信息
void Log::change_opt(int privilege, std::string name, std::string info, operate &opt)
{
    std::string info_;
    switch (privilege)
    {
        case 0: info_ += "visitor "; break;
        case 1: info_ += "customer "; break;
        case 3: info_ += "worker "; break;
        case 7: info_ += "manager "; break;
    }
    info_ += name + info;
    std::snprintf(opt.operation, sizeof(opt.operation), "%s", info_.c_str());
    opt.privilege = privilege;
}

// 添加操作记录
void Log::add_operation(int privilege, std::string name, TokenType type)
{
    operation_record.initialise("operation");
    operate opt;

    switch (type)
    {
        case LOGIN: change_opt(privilege, name, " log in\n", opt); break;
        case LOGOUT: change_opt(privilege, name, " log out\n", opt); break;
        case REGISTER: change_opt(privilege, name, " register a new account\n", opt); break;
        case PASSWD: change_opt(privilege, name, " change other's password\n", opt); break;
        case USERADD: change_opt(privilege, name, " add a new user\n", opt); break;
        case DELETEUSER: change_opt(privilege, name, " delete a user\n", opt); break;
        case SHOW: change_opt(privilege, name, " show the books\n", opt); break;
        case FINANCE: change_opt(privilege, name, " show the finance\n", opt); break;
        case BUY: change_opt(privilege, name, " buy some books\n", opt); break;
        case SELECT: change_opt(privilege, name, " select a book\n", opt); break;
        case MODIFY: change_opt(privilege, name, " modify a book\n", opt); break;
        case IMPORT: change_opt(privilege, name, " import some books\n", opt); break;
        case REPORT: change_opt(privilege, name, " check the report\n", opt); break;
        case LOG: change_opt(privilege, name, " check the Log\n", opt); break;
        case EXIT: change_opt(privilege, name, " exit\n", opt); break;
        default: change_opt(privilege, name, " invalid operation\n", opt); break;
    }

    operation_record.write(opt);
}
