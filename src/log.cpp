#include "../include/log.hpp"
#include <iomanip>
#include "../include/parser.hpp"

bool log::ShowFinance(int count_ = -1)
{
    // 如果指定查询交易笔数为 0，直接输出空行，表示合法指令
    if (count_ == 0)
    {
        std::cout << '\n';
        return true;
    }

    // 初始化 MemoryRiver 对象，确保可以读取日志文件
    log_record.initialise("log");

    // 获取当前总交易笔数（存储在 info 位置 1）
    int cur_count;
    log_record.get_info(cur_count, 1);

    // 如果请求查询的交易笔数大于总交易笔数，则操作非法
    if (cur_count < count_)
    {
        return false;
    }

    // 获取日志文件的总字节数，用于遍历交易记录
    int log_end = log_record.end();
    record temp; // 用于临时存储读取的记录
    int start_index = 2 * sizeof(int); // 从文件偏移开始读取记录，跳过前两个 int（header 信息）

    double inc = 0; // 累计收入
    double exp = 0; // 累计支出

    // 遍历日志文件中的每一条记录
    while (start_index + sizeof(record) <= log_end)
    {
        // 读取记录到 temp
        log_record.read(temp, start_index);

        // 累加收入和支出
        inc += temp.income;
        exp += temp.expense;

        // 如果当前记录的 count 等于查询的 count，则输出累计金额
        if (temp.count == count_)
        {
            std::cout << "+ " << std::fixed << std::setprecision(2) << inc;
            std::cout << " - " << std::fixed << std::setprecision(2) << exp;
            std::cout << '\n';
            return true;
        }

        // 移动到下一条记录的偏移
        start_index += sizeof(record);
    }

    // 如果 count_ = -1，则输出所有交易的总额
    if (count_ == -1)
    {
        std::cout << "+ " << std::fixed << std::setprecision(2) << inc;
        std::cout << " - " << std::fixed << std::setprecision(2) << exp;
        std::cout << '\n';
        return true;
    }
    else
    {
        // 如果循环结束仍未找到指定 count，则操作非法
        return false;
    }
}

void log::add_trading(double income, double expense)
{
    // 初始化日志存储
    log_record.initialise("log");

    // 获取当前总交易笔数
    int cur_count;
    log_record.get_info(cur_count, 1);

    // 新交易的交易编号 = 当前总交易数 + 1
    ++cur_count;

    // 更新日志文件中的总交易笔数
    log_record.write_info(cur_count, 1);

    // 构造新交易记录
    record new_trade = {cur_count, income, expense};

    // 将新交易记录写入日志
    log_record.write(new_trade);
}

int main()
{
    Parser parser;
    log log_diary;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;
        Command cmd = BLANK;
        int column = 0;
        while (column < line.size())
        {
            char ch = line[column];
            // 如果ch是空格
            if (std::isspace(static_cast<int>(ch)))
            {
                ++column;
                continue;
            }
            // 如果ch是字母
            if (std::isalpha(ch))
            {
                int start = column;
                ++column;
                while (column < line.size() && std::isalpha(line[column]))
                {
                    ++column;
                }
                std::string text = line.substr(start, column - start); // 提取首个单词
                cmd = parser.matchkeyword(text);
                if (cmd == FINANCE)
                {
                    
                }
                break;
            }
        }
        std::string next_text;
        bool is_more = false;
        switch (cmd)
        {
            case SHOW:

                while (column < line.size())
                {
                    char ch = line[column];
                    if (std::isspace(static_cast<int>(ch)))
                    {
                        ++column;
                        continue;
                    }

                    else if (next_text.empty())
                    {
                        int start = column;
                        ++column;
                        while (column < line.size() && !std::isspace(static_cast<int>(line[column])))
                        {
                            ++column;
                        }
                        next_text = line.substr(start, column - start); // 提取第二个单词
                        cmd = parser.matchkeyword(next_text);
                    }
                    else
                    {
                        std::cout << "Invalid\n";
                        is_more = true;
                        break;
                    }
                }
                if (is_more)
                    break;
              

                break;


            case INVALID:
                std::cout << "Invalid\n";
                break;

            case EXIT:
                return 0;

            default:
                break;
        }
    }
    return 0;
}
