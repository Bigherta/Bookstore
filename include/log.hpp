#include "storage.hpp"
#include "Token.hpp"


class log
{
private:
    struct record
    {
        int count = 0;
        double income = 0;
        double expense = 0;
    };
    record cur_;

    struct operate
    {
        int privilege = 0;
        char operation[128]{};
    };
    MemoryRiver<record> purchase_record;
    MemoryRiver<operate> operation_record;

public:
    /** 财务记录查询
     * @param count_ 查询的交易笔数，默认为 -1，表示查询所有交易总额
     * @return 若查询合法则返回 true 并输出结果，否则返回 false
     */
    bool ShowFinance(long long count_ = -1);


    /** 记录一笔交易
     * @param income 交易的收入金额
     * @param expense 交易的支出金额
     */
    void add_trading(double income, double expense); // 记录交易

    void change_opt(int, std::string, std::string,  operate &);

    void add_operation(int, std::string, TokenType); //记录操作

    void ReportFinance();

    void ReportEmployee();

    void Log();
};
