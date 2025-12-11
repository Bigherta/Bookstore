#include <iostream>
#include "storage.hpp"

class log
{
private:
    struct record
    {
        int count;
        double income = 0;
        double expense = 0;
    };
    record cur_;

    MemoryRiver<record> log_record;

public:
    bool ShowFinance(int count_);

    void ReportFinance() { std::cout << "财务报表\n"; }

    void ReportEmployee() { std::cout << "员工工作情况表\n"; }

    void Log() { std::cout << "日志记录\n"; }
};
