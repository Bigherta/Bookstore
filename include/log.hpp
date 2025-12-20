#ifndef LOG_HPP
#define LOG_HPP
#include "storage.hpp"
#include "Token.hpp"
#include <string>

/**
 * @brief 日志管理类
 *
 * 该类负责管理财务记录和操作日志，包括交易记录的存储、查询和报告生成。
 */
class Log
{
private:
    /**
     * @brief 财务记录结构体
     *
     * 存储单笔交易的详细信息，包括交易编号、收入和支出金额。
     */
    struct record
    {
        int count = 0;   /**< 交易编号 */
        double income = 0;   /**< 收入金额 */
        double expense = 0;  /**< 支出金额 */
    };
    record cur_;   /**< 当前交易记录 */

    /**
     * @brief 操作记录结构体
     *
     * 存储用户操作的详细信息，包括权限级别和操作描述。
     */
    struct operate
    {
        int privilege = 0;   /**< 用户权限级别 */
        char operation[128]{};   /**< 操作描述字符串 */
    };
    MemoryRiver<record> purchase_record;   /**< 财务记录存储 */
    MemoryRiver<operate> operation_record;   /**< 操作记录存储 */

public:
    /** @brief 财务记录查询
     * @param count_ 查询的交易笔数，默认为 -1，表示查询所有交易总额
     * @return 若查询合法则返回 true 并输出结果，否则返回 false
     */
    bool ShowFinance(std::string &, long long count_ = -1);


    /** @brief 记录一笔交易
     * @param income 交易的收入金额
     * @param expense 交易的支出金额
     */
    void add_trading(double income, double expense); // 记录交易

    /**
     * @brief 设置操作信息
     * @param privilege 用户权限级别
     * @param name 用户名
     * @param info 操作信息字符串
     * @param opt 操作记录结构体引用
     */
    void change_opt(int privilege, std::string name, std::string info, operate &opt);

    /**
     * @brief 添加操作记录
     * @param privilege 用户权限级别
     * @param name 用户名
     * @param type 操作类型
     */
    void add_operation(int privilege, std::string name, TokenType type); //记录操作

    /**
     * @brief 生成财务报告
     *
     * 显示所有交易的详细信息和总额。
     */
    void ReportFinance(std::string &);

    /**
     * @brief 生成员工操作报告
     *
     * 显示权限级别为3的操作日志。
     */
    void ReportEmployee(std::string &);

    /**
     * @brief 显示所有日志
     *
     * 包括操作日志和财务日志。
     */
    void Logger(std::string &);
};
#endif