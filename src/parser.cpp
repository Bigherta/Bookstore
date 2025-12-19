#include "../include/parser.hpp"
#include <cctype>
#include "../include/Log.hpp"
#include "../include/book.hpp"
#include "../include/user.hpp"
#include "../include/validator.hpp"


// 将字符串匹配成对应的枚举类
TokenType Parser::matchkeyword(const std::string &text) const
{
    auto it = TABLE.find(text);
    if (it != TABLE.end())
    {
        return it->second;
    }
    return BLANK;
}

// 解析一行源码，将输入行分割成tokens
TokenStream Parser::tokenize(const std::string &line, bool &is_valid) const
{
    std::vector<Token> tokens;
    int column = 0;
    while (column < line.size())
    {
        char ch = line[column];

        // 如果ch是空格
        if (std::isspace(static_cast<int>(ch)))
        {
            if (ch != ' ')
            {
                is_valid = false; // 只允许空格，不允许制表符等
            }
            ++column;
            continue;
        }
        else
        {
            int start = column;
            ++column;
            while (column < line.size() && !std::isspace(static_cast<int>(line[column])))
            {
                ++column;
            }
            std::string text = line.substr(start, column - start); // 提取单词
            TokenType type = matchkeyword(text); // 判断是哪一个枚举类型
            if (type == BLANK)
            {
                type = TEXT; // 非关键词设为TEXT
            }
            tokens.push_back(Token{type, text, column});
            continue;
        }
    }
    return TokenStream(std::move(tokens));
}

// 检查字符串是否为有效的整数（不超过int范围）
bool Parser::isN(std::string str) noexcept
{
    try
    {
        expect(str.size()).ge(1).And().le(10);
        expect(str).toMatch("^(0|[1-9][0-9]*)$");
        expect(std::stoll(str)).le(2147483647);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

// 检查字符串是否为有效的浮点数
bool Parser::isD(std::string str) noexcept
{
    try
    {
        expect(str.size()).ge(1).And().le(13);
        expect(str).toMatch("^(0(\\.[0-9]+)?|[1-9][0-9]*(\\.[0-9]+)?)$");
    }
    catch (...)
    {
        return false;
    }
    return true;
}

// 执行指令的主函数
std::string Parser::execute(const std::string &line_raw, UserManager &userManager, Log &Log, bool &is_running)
{
    std::string result;
    std::string line = line_raw;
    if (line.empty())
        return result;
    while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
        line.pop_back();

    bool is_valid = true;
    TokenStream tokens_ = tokenize(line, is_valid);
    if (!is_valid)
    {
        return "Invalid\n";
    }
    if (tokens_.size() == 0)
        return string();
    int privilegeLevel_ = -1;
    const TokenType cmd = tokens_.get()->type;
    switch (cmd)
    {
        case LOGIN: {
            // 登录命令：login [User-ID] [Password]
            // 权限：无
            // 参数：User-ID, Password (可选，如果当前用户权限更高)

            if (tokens_.size() > 3 || tokens_.size() < 2)
            {
                return "Invalid\n";
            }

            std::string userID_, password_;

            userID_ = tokens_.get()->text;

            if (tokens_.peek() != nullptr)
                password_ = tokens_.get()->text;

            if (!userManager.login(userID_, password_))
            {
                return "Invalid\n";
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case LOGOUT: {
            // 登出命令：logout
            // 权限：1+
            // 参数：无

            if (tokens_.size() != 1 || userManager.getCurrentUser().privilegeLevel < 1)
            {
                return "Invalid\n";
            }
            int cur_privilege = userManager.getCurrentUser().privilegeLevel;
            std::string cur_name = userManager.getCurrentUser().username;
            if (!userManager.logout())
            {
                return "Invalid\n";
            }
            Log.add_operation(cur_privilege, cur_name, cmd);
            break;
        }

        case REGISTER: {
            // 注册命令：register [User-ID] [Password] [Username]
            // 权限：无
            // 参数：User-ID, Password, Username

            if (tokens_.size() != 4)
            {
                return "Invalid\n";
            }

            std::string userID_, password_, username_;

            userID_ = tokens_.get()->text;

            password_ = tokens_.get()->text;

            username_ = tokens_.get()->text;

            if (!userManager.registerUser(userID_, password_, username_))
            {
                return "Invalid\n";
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case PASSWD: {
            // 修改密码命令：passwd [User-ID] [Current-Password] [New-Password] 或 passwd [User-ID] [New-Password]
            // (管理员) 权限：1+ 或管理员修改他人 参数：User-ID, Current-Password (可选), New-Password

            if (tokens_.size() < 3 || tokens_.size() > 4 || userManager.getCurrentUser().privilegeLevel < 1)
            {
                return "Invalid\n";
            }

            std::string userID_, cur_Password_, new_Password_;

            userID_ = tokens_.get()->text;

            if (tokens_.size() == 4)
            {
                cur_Password_ = tokens_.get()->text;
            }
            else
            {
                if (userManager.getCurrentUser().privilegeLevel < 7)
                {
                    return "Invalid\n";
                }
                new_Password_ = tokens_.get()->text;
            }

            if (tokens_.peek() != nullptr)
                new_Password_ = tokens_.get()->text;

            if (!userManager.passwd(userID_, cur_Password_, new_Password_))
            {
                return "Invalid\n";
            }

            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case USERADD: {
            // 添加用户命令：useradd [User-ID] [Password] [Privilege] [Username]
            // 权限：3+
            // 参数：User-ID, Password, Privilege (1或3), Username

            if (tokens_.size() != 5 || userManager.getCurrentUser().privilegeLevel < 3)
            {
                return "Invalid\n";
            }
            std::string userID_, password_, username_;

            userID_ = tokens_.get()->text;

            password_ = tokens_.get()->text;

            std::string temp_text = tokens_.get()->text;

            if (temp_text.size() != 1)
            {
                return "Invalid\n";
            }
            else if (temp_text[0] != '1' && temp_text[0] != '3')
            {
                return "Invalid\n";
            }

            privilegeLevel_ = std::stoi(temp_text);

            username_ = tokens_.get()->text;

            if (!userManager.useradd(userID_, password_, privilegeLevel_, username_))
            {
                return "Invalid\n";
            }

            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case DELETEUSER: {
            // 删除用户命令：delete [User-ID]
            // 权限：7
            // 参数：User-ID

            if (tokens_.size() != 2 || userManager.getCurrentUser().privilegeLevel < 7)
            {
                return "Invalid\n";
            }
            std::string userID_;

            userID_ = tokens_.get()->text;

            if (!userManager.deleteUser(userID_))
            {
                return "Invalid\n";
            }

            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case SHOW: {
            // 显示命令：show 或 show finance [count] 或 show -ISBN=... 等
            // 权限：1+ for show, 7 for finance
            // 参数：无 或 finance [count] 或 -param=value

            if (tokens_.size() == 1)
            {
                // show：显示所有图书

                if (userManager.getCurrentUser().privilegeLevel < 1)
                {
                    return "Invalid\n";
                }
                storage<IsbnTag> storage_;
                storage_.Show(result);
                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  cmd);
                break;
            }
            if (tokens_.peek() == nullptr)
            {
                return "Invalid\n";
            }
            const TokenType showType = tokens_.peek()->type;
            if (showType == FINANCE)
            {
                // show finance [count]：显示财务信息

                if (tokens_.size() < 2 || tokens_.size() > 3 || userManager.getCurrentUser().privilegeLevel < 7)
                {
                    return "Invalid\n";
                }
                tokens_.get();
                if (tokens_.peek() == nullptr)
                {
                    Log.ShowFinance(result);
                }
                else
                {
                    std::string count_str = tokens_.get()->text;
                    if (count_str.size() > 10)
                    {
                        return "Invalid\n";
                    }
                    if (!Parser::isN(count_str))
                    {
                        return "Invalid\n";
                    }
                    long long count_ = std::stoll(count_str);
                    if (!Log.ShowFinance(result, count_))
                    {
                        return "Invalid\n";
                    }
                }
                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  showType);
            }
            else
            {
                // show -param=value：按参数搜索图书

                if (tokens_.size() != 2 || userManager.getCurrentUser().privilegeLevel < 1)
                {
                    return "Invalid\n";
                }
                std::string text_ = tokens_.get()->text;
                int column = 0;
                if (text_[column] != '-')
                {
                    return "Invalid\n";
                }
                column++;
                int start = column;
                while (column < text_.size() && text_[column] != '=')
                {
                    column++;
                }
                const TokenType search_param = matchkeyword(text_.substr(start, column - start));
                column++;
                std::string search_value;
                if (search_param == ISBN)
                {
                    search_value = text_.substr(column, text_.size() - column);
                    if (!Book::is_ISBN_valid(search_value))
                    {
                        return "Invalid\n";
                    }
                    storage<IsbnTag> storage_;
                    storage_.SearchIsbn(search_value, result);
                }
                else if (search_param == NAME || search_param == AUTHOR)
                {
                    if (text_[column] != '"' || text_[text_.size() - 1] != '"')
                    {
                        return "Invalid\n";
                    }
                    search_value = text_.substr(column + 1, text_.size() - column - 2);

                    if (!Book::is_author_or_name_valid(search_value))
                    {
                        return "Invalid\n";
                    }
                    if (search_param == NAME)
                    {
                        storage<NameTag> storage_(search_value);
                        storage_.Show(result);
                    }
                    if (search_param == AUTHOR)
                    {
                        storage<AuthorTag> storage_(search_value);
                        storage_.Show(result);
                    }
                }
                else if (search_param == KEYWORD)
                {
                    if (text_[column] != '"' || text_[text_.size() - 1] != '"')
                    {
                        return "Invalid\n";
                    }
                    search_value = text_.substr(column + 1, text_.size() - column - 2);

                    if (search_value.empty() || search_value.size() > 60)
                    {
                        return "Invalid\n";
                    }
                    bool is_valid = true;

                    for (char ch: search_value)
                    {
                        if (ch == '|' || ch == '"')
                        {
                            is_valid = false;
                            break;
                        }
                    }
                    if (Book::is_keyword_invalid(search_value))
                    {
                        is_valid = false;
                    }
                    if (!is_valid)
                    {
                        return "Invalid\n";
                    }
                    storage<KeywordTag> storage_(search_value);
                    storage_.Show(result);
                }
                else
                {
                    return "Invalid\n";
                }

                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  cmd);
            }
            break;
        }
        case BUY: {


            if (tokens_.size() != 3 || userManager.getCurrentUser().privilegeLevel < 1)
            {
                return "Invalid\n";
            }
            std::string isbn = tokens_.get()->text;

            if (!Book::is_ISBN_valid(isbn))
            {
                return "Invalid\n";
            }
            storage<IsbnTag> storage_;
            if (!storage_.Find(isbn))
            {
                return "Invalid\n";
            }
            std::string quantity = tokens_.get()->text;
            if (!isN(quantity))
            {
                return "Invalid\n";
            }
            long long num = std::stoll(quantity);
            if (num <= 0 || num > 2147483647)
            {
                return "Invalid\n";
            }
            double total_cost;
            if (!storage_.buy_book(isbn, num, total_cost, result))
            {
                return "Invalid\n";
            }
            Log.add_trading(total_cost, 0);
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case SELECT: {
            if (userManager.getCurrentUser().privilegeLevel < 3 || tokens_.size() != 2)
            {
                return "Invalid\n";
            }
            std::string isbn_ = tokens_.get()->text;

            if (!Book::is_ISBN_valid(isbn_))
            {
                return "Invalid\n";
            }
            storage<IsbnTag> storage_;
            if (!storage_.Find(isbn_))
            {
                storage_.Insert(isbn_);
                userManager.getSelectedbook() = isbn_;
            }
            else
            {
                userManager.getSelectedbook() = isbn_;
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case MODIFY: {
            if (!userManager.is_valid_to_getSelectedbook())
            {
                return "Invalid\n";
            }

            if (userManager.getCurrentUser().privilegeLevel < 3 || userManager.getSelectedbook().empty() ||
                tokens_.size() < 2 || tokens_.size() > 6)
            {
                return "Invalid\n";
            }
            std::string isbn, name, author, keyword, price;
            bool is_valid = true;
            while (tokens_.peek() != nullptr)
            {
                std::string text_ = tokens_.get()->text;
                int column = 0;
                if (text_[column] != '-')
                {
                    is_valid = false;
                    break;
                }
                column++;
                int start = column;
                while (column < text_.size() && text_[column] != '=')
                {
                    column++;
                }
                const TokenType change_param = matchkeyword(text_.substr(start, column - start));
                column++;
                switch (change_param)
                {
                    case ISBN: {
                        if (!isbn.empty())
                            is_valid = false;

                        isbn = text_.substr(column);

                        if (isbn.empty())
                            is_valid = false;
                        break;
                    }
                    case NAME: {
                        if (text_[column] != '"' || text_[text_.size() - 1] != '"' || !name.empty())
                        {
                            is_valid = false;
                            break;
                        }

                        name = text_.substr(column + 1, text_.size() - column - 2);
                        if (name.empty())
                            is_valid = false;
                        break;
                    }
                    case AUTHOR: {
                        if (text_[column] != '"' || text_[text_.size() - 1] != '"' || !author.empty())
                        {
                            is_valid = false;
                            break;
                        }
                        author = text_.substr(column + 1, text_.size() - column - 2);
                        if (author.empty())
                            is_valid = false;
                        break;
                    }
                    case KEYWORD: {
                        if (text_[column] != '"' || text_[text_.size() - 1] != '"' || !keyword.empty())
                        {
                            is_valid = false;
                            break;
                        }
                        keyword = text_.substr(column + 1, text_.size() - column - 2);
                        if (keyword.empty())
                            is_valid = false;
                        break;
                    }
                    case PRICE: {
                        if (!price.empty())
                        {
                            is_valid = false;
                            break;
                        }
                        price = text_.substr(column);
                        if (price.empty())
                            is_valid = false;
                        if (!Parser::isD(price))
                        {
                            is_valid = false;
                            break;
                        }
                        break;
                    }
                    default:
                        is_valid = false;
                        break;
                }
            }
            if (!is_valid)
            {
                return "Invalid\n";
            }
            else
            {
                std::string ori_isbn = userManager.getSelectedbook();
                if (!storage<IsbnTag>::modify_book(isbn, name, author, keyword, price, userManager.getSelectedbook()))
                {
                    return "Invalid\n";
                }
                if (!isbn.empty())
                {
                    auto &log_stack = userManager.get_stack();
                    for (int i = 0; i < log_stack.size(); i++)
                    {
                        if (log_stack[i].second == ori_isbn)
                        {
                            log_stack[i].second = isbn;
                        }
                    }
                }
                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  cmd);
            }
            break;
        }
        case IMPORT: {
            if (!userManager.is_valid_to_getSelectedbook())
            {
                return "Invalid\n";
            }

            if (tokens_.size() != 3 || userManager.getSelectedbook().empty() ||
                userManager.getCurrentUser().privilegeLevel < 3)
            {
                return "Invalid\n";
            }
            std::string quantity = tokens_.get()->text;
            if (!isN(quantity))
            {
                return "Invalid\n";
            }
            long long num = stoll(quantity);
            if (num <= 0)
            {
                return "Invalid\n";
            }
            std::string total_cost = tokens_.get()->text;
            if (!isD(total_cost))
            {
                return "Invalid\n";
            }
            double total_ = std::stod(total_cost);
            if (total_ <= 0.00)
            {
                return "Invalid\n";
            }
            storage<IsbnTag> storage_;
            storage_.import_book(userManager.getSelectedbook(), num);
            Log.add_trading(0, total_);
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case REPORT: {
            if (tokens_.size() != 2 || userManager.getCurrentUser().privilegeLevel < 7)
            {
                return "Invalid\n";
            }
            const TokenType reportType = tokens_.get()->type;
            if (reportType == FINANCE)
            {
                Log.ReportFinance(result);
            }
            else if (reportType == EMPLOYEE)
            {
                Log.ReportEmployee(result);
            }
            else
            {
                return "Invalid\n";
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case LOG: {
            if (tokens_.size() != 1 || userManager.getCurrentUser().privilegeLevel < 7)
            {
                return "Invalid\n";
            }
            Log.Logger(result);
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case EXIT: {

            if (tokens_.size() != 1)
            {
                return "Invalid\n";
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            userManager.exit();
            is_running = false;
        }
        case TEXT:
            return "Invalid\n";
        default:
            break;
    }
    return result;
}
