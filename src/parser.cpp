#include "../include/parser.hpp"
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
TokenStream Parser::tokenize(const std::string &line) const
{
    std::vector<Token> tokens;
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
        else
        {
            int start = column;
            ++column;
            while (column < line.size() && !std::isspace(line[column]))
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
    return std::isalnum(static_cast<unsigned char>(ch)) && !std::isalpha(static_cast<unsigned char>(ch));
}

bool Parser::isN(std::string str) noexcept
{
    for (char c: str)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

bool Parser::isD(std::string str) noexcept
{
    for (char c: str)
    {
        if (!std::isdigit(c) && c != '.')
        {
            return false;
        }
    }
    return true;
}

void Parser::execute(const std::string &line, UserManager &userManager, log &Log)
{
    if (line.empty())
        return;
    TokenStream tokens_ = tokenize(line);
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
                std::cout << "Invalid\n";

            break;
        }
        case LOGOUT: {
            if (tokens_.size() != 1)
            {
                std::cout << "Invalid\n";
                break;
            }
            if (!userManager.logout())
            {
                std::cout << "Invalid\n";
                break;
            }
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
                std::cout << "Invalid\n";

            break;
        }

        case PASSWD: {
            if (tokens_.size() < 3 || tokens_.size() > 4)
            {
                std::cout << "Invalid\n";
                break;
            }

            std::string userID_, cur_Password_, new_Password_;

            userID_ = tokens_.get()->text;

            cur_Password_ = tokens_.get()->text;

            if (tokens_.peek() != nullptr)
                new_Password_ = tokens_.get()->text;

            if (!userManager.passwd(userID_, cur_Password_, new_Password_))
                std::cout << "Invalid\n";

            break;
        }

        case USERADD: {
            if (tokens_.size() != 5)
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
            else if (temp_text[0] != '0' && temp_text[0] != '1' && temp_text[0] != '3' && temp_text[0] != '7')
            {
                std::cout << "Invalid\n";
                break;
            }

            privilegeLevel_ = std::stoi(temp_text);

            username_ = tokens_.get()->text;

            if (!userManager.useradd(userID_, password_, privilegeLevel_, username_))
                std::cout << "Invalid\n";

            break;
        }
        case DELETEUSER: {
            if (tokens_.size() != 2)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string userID_;

            userID_ = tokens_.get()->text;

            if (!userManager.deleteUser(userID_))
                std::cout << "Invalid\n";

            break;
        }

        case SHOW: {
            if (tokens_.size() == 1)
            {
                storage<IsbnTag> storage_;
                storage_.Show();
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
                    if (count_ > 2147483647)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    if (!Log.ShowFinance(count_))
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                }
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
                    storage<IsbnTag> storage_;
                    storage_.SearchIsbn(search_value);
                    break;
                }
                else if (search_param == NAME || search_param == AUTHOR)
                {
                    if (text_[column] != '"' || text_[text_.size() - 1] != '"')
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    search_value = text_.substr(column + 1, text_.size() - column - 2);
                    if (search_value.empty())
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
                    break;
                }
                else if (search_param == KEYWORD)
                {
                    if (text_[column] != '"' || text_[text_.size() - 1] != '"')
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
                    search_value = text_.substr(column + 1, text_.size() - column - 2);
                    bool is_valid = true;
                    for (int i = 0; i < search_value.size(); i++)
                    {
                        if (search_value[i] == '|')
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
                    break;
                }
                else
                {
                    std::cout << "Invalid\n";
                    break;
                }
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
            int num = stoi(quantity);
            if (num <= 0)
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
            break;
        }
        case SELECT: {
            if (userManager.getCurrentUser().privilegeLevel < 3 || tokens_.size() != 2)
            {
                std::cout << "Invalid\n";
                break;
            }
            std::string isbn_ = tokens_.get()->text;
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

            break;
        }
        case MODIFY: {
            if (userManager.getCurrentUser().privilegeLevel < 3 || userManager.getSelectedbook().empty() ||
                tokens_.size() < 2)
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

                        break;
                    }
                    case NAME: {
                        if (text_[column] != '"' || text_[text_.size() - 1] != '"' || !name.empty())
                        {
                            is_valid = false;
                            break;
                        }

                        name = text_.substr(column + 1, text_.size() - column - 2);
                        break;
                    }
                    case AUTHOR: {
                        if (text_[column] != '"' || text_[text_.size() - 1] != '"' || !author.empty())
                        {
                            is_valid = false;
                            break;
                        }
                        author = text_.substr(column + 1, text_.size() - column - 2);
                        break;
                    }
                    case KEYWORD: {
                        if (text_[column] != '"' || text_[text_.size() - 1] != '"' || !keyword.empty())
                        {
                            is_valid = false;
                            break;
                        }
                        keyword = text_.substr(column + 1, text_.size() - column - 2);

                        break;
                    }
                    case PRICE: {
                        if (!price.empty())
                        {
                            is_valid = false;
                            break;
                        }
                        price = text_.substr(column);
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
            int num = stoi(quantity);
            std::string total_cost = tokens_.get()->text;
            if (!isD(total_cost))
            {
                std::cout << "Invalid\n";
                break;
            }
            double total_ = std::stod(total_cost);
            storage<IsbnTag> storage_;
            storage_.import_book(userManager.getSelectedbook(), num);
            Log.add_trading(0, total_);
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
            }
            break;
        }

        case LOG: {
            if (tokens_.size() != 1 || userManager.getCurrentUser().privilegeLevel < 7)
            {
                std::cout << "Invalid\n";
                break;
            }
            Log.Log();
            break;
        }
        case EXIT: {
            if (tokens_.size() != 1)
            {
                std::cout << "Invalid\n";
                break;
            }
            exit(0);
        }
        case TEXT:
            std::cout << "Invalid\n";
            break;
        default:
            break;
    }
}
