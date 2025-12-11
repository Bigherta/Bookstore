#include "../include/book.hpp"
#include "../include/log.hpp"
#include "../include/parser.hpp"
#include "../include/user.hpp"

std::vector<std::pair<std::string, int>> name_index_pair;

int main()
{

    TokenStream tokens_;
    Parser parser;
    UserManager userManager;
    log Log;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;
        tokens_ = parser.tokenize(line);
        int privilegeLevel_ = -1;
        const TokenType cmd = tokens_.get()->type;
        switch (cmd)
        {
            case LOGIN: {
                std::string userID_, password_;
                if (tokens_.size() > 3 || tokens_.size() < 2)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                if (tokens_.peek() != nullptr)
                    password_ = tokens_.get()->text;

                if (!userManager.login(userID_, password_))
                    std::cout << "Invalid\n";

                else
                {
                    std::cout << "Welcome, " << userID_ << "\n";
                }
                break;
            }
            case LOGOUT: {
                if (!userManager.logout())
                    std::cout << "Invalid\n";

                break;
            }

            case REGISTER: {
                std::string userID_, password_, username_;
                if (tokens_.size() != 4)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                password_ = tokens_.get()->text;

                username_ = tokens_.get()->text;

                if (!userManager.registerUser(userID_, password_, username_))
                    std::cout << "Invalid\n";
                else
                {
                    std::cout << "Register" << userID_ << " successfully\n";
                }
                break;
            }

            case PASSWD: {
                std::string userID_, cur_Password_, new_Password_;

                if (tokens_.size() < 3 || tokens_.size() > 4)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                cur_Password_ = tokens_.get()->text;

                if (tokens_.peek() != nullptr)
                    new_Password_ = tokens_.get()->text;

                if (!userManager.passwd(userID_, cur_Password_, new_Password_))
                    std::cout << "Invalid\n";
                else
                {
                    std::cout << "Change password of " << userID_ << " successfully\n";
                }
                break;
            }

            case USERADD: {
                std::string userID_, password_, username_;

                if (tokens_.size() != 5)
                {
                    std::cout << "Invalid\n";
                    break;
                }
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
                else
                {
                    std::cout << "Add user " << userID_ << " successfully\n";
                }
                break;
            }
            case DELETEUSER: {
                std::string userID_;

                if (tokens_.size() != 2)
                {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                if (!userManager.deleteUser(userID_))
                    std::cout << "Invalid\n";
                else
                {
                    std::cout << "Delete user " << userID_ << " successfully\n";
                }
                break;
            }

            case SHOW: {

                const TokenType showType = tokens_.get()->type;
                if (showType == FINANCE)
                {
                    if (tokens_.size() < 2 || tokens_.size() > 3 || userManager.getPrivilegeLevel() < 7)
                    {
                        std::cout << "Invalid\n";
                        break;
                    }
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
                        bool isNumber = true;
                        for (char c: count_str)
                        {
                            if (!std::isdigit(c))
                            {
                                std::cout << "Invalid\n";
                                isNumber = false;
                                break;
                            }
                        }
                        if (!isNumber)
                            break;
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
                break;
            }

            case REPORT: {
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

            case LOG:
                Log.Log();
                break;
                
            case TEXT:
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
