#include "../include/parser.hpp"
#include <cctype>
#include <iostream>
#include "../include/log.hpp"
#include "../include/user.hpp"

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

// 解析一行源码
TokenStream Parser::tokenize(const std::string &line, bool &is_valid) const
{
    std::vector<Token> tokens;
    int column = 0;
    while (column < line.size())
    {
        char ch = line[column];
        if (static_cast<unsigned char>(ch) > 127)
        {
            is_valid = false;
        }
        // 如果ch是空格
        if (std::isspace(static_cast<int>(ch)))
        {
            if (ch != ' ')
            {
                is_valid = false;
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
                type = TEXT;
            }
            tokens.push_back(Token{type, text, column});
            continue;
        }
    }
    return TokenStream(std::move(tokens));
}

bool Parser::isLetterChar(char ch) noexcept { return std::isalpha(static_cast<unsigned char>(ch)); }

bool Parser::isNumberChar(char ch) noexcept
{
    return (std::isalnum(static_cast<unsigned char>(ch)) && !std::isalpha(static_cast<unsigned char>(ch)));
}

bool Parser::isN(std::string str) noexcept
{
    if (str.empty() || str.size() > 10)
        return false;
    if (str == "0")
        return true;
    if (str[0] < '1' || str[0] > '9')
        return false;
    for (char c: str)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    if (str.size() == 10 && str > "2147483647")
        return false;
    return true;
}

bool Parser::isD(std::string str) noexcept
{
    if (str.empty() || str.size() > 13)
        return false;
    if (str == "0")
        return true;
    if (str[0] == '0')
    {
        if (str.size() == 1)
            return false;
        if (str[1] != '.')
            return false;
    }
    int dot_pos = -1;
    for (int i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(static_cast<unsigned char>(str[i])) && str[i] != '.')
            return false;
        if (str[i] == '.')
        {
            if (i == 0 || i == str.size() - 1)
                return false;
            if (dot_pos != -1)
                return false;
            dot_pos = i;
        }
    }
    return true;
}

void Parser::execute(const std::string &line_raw, UserManager &userManager, log &Log, bool &is_running)
{
    std::string line = line_raw;
    if (line.empty())
        return;
    while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
        line.pop_back();

    bool is_valid = true;
    TokenStream tokens_ = tokenize(line, is_valid);
    if (!is_valid)
    {
        std::cout << "Invalid\n";
        return;
    }
    if (tokens_.size() == 0)
        return;
    int privilegeLevel_ = -1;
    const TokenType cmd = tokens_.get()->type;
    switch (cmd)
    {
        case LOGIN: {

            if (tokens_.size() > 3 || tokens_.size() < 2)
            {
                std::cout << "Invalid\n";
                break;
            }

            std::string userID_, password_;

            userID_ = tokens_.get()->text;

            if (tokens_.peek() != nullptr)
                password_ = tokens_.get()->text;

            if (!userManager.login(userID_, password_))
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case LOGOUT: {

            if (tokens_.size() != 1 || userManager.getCurrentUser().privilegeLevel < 1)
            {
                std::cout << "Invalid\n";
                break;
            }
            int cur_privilege = userManager.getCurrentUser().privilegeLevel;
            std::string cur_name = userManager.getCurrentUser().username;
            if (!userManager.logout())
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.add_operation(cur_privilege, cur_name, cmd);
            break;
        }

        case REGISTER: {

            if (tokens_.size() != 4)
            {
                std::cout << "Invalid\n";
                break;
            }

            std::string userID_, password_, username_;

            userID_ = tokens_.get()->text;

            password_ = tokens_.get()->text;

            username_ = tokens_.get()->text;

            if (!userManager.registerUser(userID_, password_, username_))
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case PASSWD: {


            if (tokens_.size() < 3 || tokens_.size() > 4 || userManager.getCurrentUser().privilegeLevel < 1)
            {
                std::cout << "Invalid\n";
                break;
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
                    std::cout << "Invalid\n";
                    break;
                }
                new_Password_ = tokens_.get()->text;
            }

            if (tokens_.peek() != nullptr)
                new_Password_ = tokens_.get()->text;

            if (!userManager.passwd(userID_, cur_Password_, new_Password_))
            {
                std::cout << "Invalid\n";
                break;
            }

            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case USERADD: {

            if (tokens_.size() != 5 || userManager.getCurrentUser().privilegeLevel < 3)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string userID_, password_, username_;

            userID_ = tokens_.get()->text;

            password_ = tokens_.get()->text;

            std::string temp_text = tokens_.get()->text;

            if (temp_text.size() != 1)
            {
                std::cout << "Invalid\n";
                break;
            }
            else if (temp_text[0] != '1' && temp_text[0] != '3')
            {
                std::cout << "Invalid\n";
                break;
            }

            privilegeLevel_ = std::stoi(temp_text);

            username_ = tokens_.get()->text;

            if (!userManager.useradd(userID_, password_, privilegeLevel_, username_))
            {
                std::cout << "Invalid\n";
                break;
            }

            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case DELETEUSER: {


            if (tokens_.size() != 2 || userManager.getCurrentUser().privilegeLevel < 7)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string userID_;

            userID_ = tokens_.get()->text;

            if (!userManager.deleteUser(userID_))
            {
                std::cout << "Invalid\n";
                break;
            }

            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case SHOW: {

            if (tokens_.size() == 1)
            {

                if (userManager.getCurrentUser().privilegeLevel < 1)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                storage<IsbnTag> storage_;
                storage_.Show();
                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  cmd);
                break;
            }
            if (tokens_.peek() == nullptr)
            {
                std::cout << "Invalid\n";
                break;
            }
            const TokenType showType = tokens_.peek()->type;
            if (showType == FINANCE)
            {

                if (tokens_.size() < 2 || tokens_.size() > 3 || userManager.getCurrentUser().privilegeLevel < 7)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                tokens_.get();
                if (tokens_.peek() == nullptr)
                {
                    Log.ShowFinance();
                }
                else
                {
                    std::string count_str = tokens_.get()->text;
                    if (count_str.size() > 10)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    if (!Parser::isN(count_str))
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    long long count_ = std::stoll(count_str);
                    if (!Log.ShowFinance(count_))
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                }
                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  showType);
            }
            else
            {

                if (tokens_.size() != 2 || userManager.getCurrentUser().privilegeLevel < 1)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                std::string text_ = tokens_.get()->text;
                int column = 0;
                if (text_[column] != '-')
                {
                    std::cout << "Invalid\n";
                    break;
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
                    if (search_value.empty() || search_value.size() > 20)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    bool is_valid = true;

                    for (char ch: search_value)
                    {
                        if (!std::isprint(static_cast<int>(ch)))
                        {
                            is_valid = false;
                            break;
                        }
                    }
                    if (!is_valid)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    storage<IsbnTag> storage_;
                    storage_.SearchIsbn(search_value);
                }
                else if (search_param == NAME || search_param == AUTHOR)
                {
                    if (text_[column] != '"' || text_[text_.size() - 1] != '"')
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    search_value = text_.substr(column + 1, text_.size() - column - 2);

                    if (search_value.empty() || search_value.size() > 60)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    bool is_valid = true;

                    for (char ch: search_value)
                    {
                        if (!std::isprint(static_cast<int>(ch)) || ch == '"')
                        {
                            is_valid = false;
                            break;
                        }
                    }
                    if (!is_valid)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    if (search_param == NAME)
                    {
                        storage<NameTag> storage_(search_value);
                        storage_.Show();
                    }
                    if (search_param == AUTHOR)
                    {
                        storage<AuthorTag> storage_(search_value);
                        storage_.Show();
                    }
                }
                else if (search_param == KEYWORD)
                {
                    if (text_[column] != '"' || text_[text_.size() - 1] != '"')
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    search_value = text_.substr(column + 1, text_.size() - column - 2);

                    if (search_value.empty() || search_value.size() > 60)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    bool is_valid = true;

                    for (char ch: search_value)
                    {
                        if (!std::isprint(static_cast<int>(ch)) || ch == '|' || ch == '"')
                        {
                            is_valid = false;
                            break;
                        }
                    }
                    if (!is_valid)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    storage<KeywordTag> storage_(search_value);
                    storage_.Show();
                }
                else
                {
                    std::cout << "Invalid\n";
                    break;
                }

                Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username,
                                  cmd);
            }
            break;
        }
        case BUY: {


            if (tokens_.size() != 3 || userManager.getCurrentUser().privilegeLevel < 1)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string isbn = tokens_.get()->text;
            storage<IsbnTag> storage_;
            if (!storage_.Find(isbn))
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string quantity = tokens_.get()->text;
            if (!isN(quantity))
            {
                std::cout << "Invalid\n";
                break;
            }
            long long num = std::stoll(quantity);
            if (num <= 0 || num > 2147483647)
            {
                std::cout << "Invalid\n";
                break;
            }
            double total_cost;
            if (!storage_.buy_book(isbn, num, total_cost))
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.add_trading(total_cost, 0);
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case SELECT: {
            if (userManager.getCurrentUser().privilegeLevel < 3 || tokens_.size() != 2)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string isbn_ = tokens_.get()->text;
            bool is_valid = true;
            if (isbn_.size() > 20)
                is_valid = false; // 超出长度限制

            for (int i = 0; i < isbn_.size(); i++)
            {
                if (isbn_[i] < 33 || isbn_[i] > 126)
                {
                    is_valid = false; // 包含非法字符
                    break;
                }
            }
            if (!is_valid)
            {
                std::cout << "Invalid\n";
                break;
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


            if (userManager.getCurrentUser().privilegeLevel < 3 || userManager.getSelectedbook().empty() ||
                tokens_.size() < 2 || tokens_.size() > 6)
            {
                std::cout << "Invalid\n";
                break;
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
                std::cout << "Invalid\n";
                break;
            }
            else
            {
                std::string ori_isbn = userManager.getSelectedbook();
                if (!storage<IsbnTag>::modify_book(isbn, name, author, keyword, price, userManager.getSelectedbook()))
                {
                    std::cout << "Invalid\n";
                    break;
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

            if (tokens_.size() != 3 || userManager.getSelectedbook().empty() ||
                userManager.getCurrentUser().privilegeLevel < 3)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string quantity = tokens_.get()->text;
            if (!isN(quantity))
            {
                std::cout << "Invalid\n";
                break;
            }
            long long num = stoll(quantity);
            if (num <= 0 || num > 2147483647)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string total_cost = tokens_.get()->text;
            if (!isD(total_cost))
            {
                std::cout << "Invalid\n";
                break;
            }
            double total_ = std::stod(total_cost);
            if (total_ <= 0.00)
            {
                std::cout << "Invalid\n";
                break;
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
                std::cout << "Invalid\n";
                break;
            }
            const TokenType reportType = tokens_.get()->type;
            if (reportType == FINANCE)
            {
                Log.ReportFinance();
            }
            else if (reportType == EMPLOYEE)
            {
                Log.ReportEmployee();
            }
            else
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }

        case LOG: {
            if (tokens_.size() != 1 || userManager.getCurrentUser().privilegeLevel < 7)
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.Log();
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            break;
        }
        case EXIT: {

            if (tokens_.size() != 1)
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.add_operation(userManager.getCurrentUser().privilegeLevel, userManager.getCurrentUser().username, cmd);
            userManager.exit();
            is_running = false;
            return;
        }
        case TEXT:
            std::cout << "Invalid\n";
            break;
        default:
            break;
    }
}
