#include "../include/log.hpp"
#include <iomanip>

bool log::ShowFinance(int count_ = -1)
{

    log_record.initialise("log");
    int log_end = log_record.end();
    if (log_end == 0)
    {
        if (count_ == 0)
        {
            std::cout << '\n';
            return true;
        }
        std::cout << "+ 0.00 - 0.00\n";
        return true;
    }
    record temp;
    int start_index = 0;
    double inc = 0;
    double exp = 0;
    while (start_index + sizeof(record) <= log_end)
    {
        log_record.read(temp, start_index);
        inc += temp.income;
        exp += temp.expense;
        if (temp.count == count_)
        {
            std::cout << "+ ";
            std::cout << std::fixed << std::setprecision(2) << inc;
            std::cout << " - ";
            std::cout << std::fixed << std::setprecision(2) << exp;
            return true;
        }
        start_index += sizeof(record);
    }
    if (count_ == -1)
    {
        std::cout << "+ ";
        std::cout << std::fixed << std::setprecision(2) << inc;
        std::cout << " - ";
        std::cout << std::fixed << std::setprecision(2) << exp;
        return true;
    }
    else
    {
        return false;
    }
}
