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
    /** 财务记录查询
     * @param count_ 查询的交易笔数，默认为 -1，表示查询所有交易总额
     * @return 若查询合法则返回 true 并输出结果，否则返回 false
     */
    bool ShowFinance(int count_);


    /** 记录一笔交易
     * @param income 交易的收入金额
     * @param expense 交易的支出金额
     */
    void add_trading(double income, double expense); // 记录交易


    void ReportFinance() { std::cout << "财务报表\n"; }

    void ReportEmployee() { std::cout << "员工工作情况表\n"; }

    void Log() { std::cout << "日志记录\n"; }
};
