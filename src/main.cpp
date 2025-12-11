#include "../include/book.hpp"
#include "../include/log.hpp"
#include "../include/parser.hpp"
#include "../include/user.hpp"

int main()
{
    Parser parser;
    UserManager userManager;
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
                break;
            }
        }
        std::string userID_, password_, username_, new_Password_, cur_Password_;
        int privilegeLevel_ = -1;
        bool is_more = false;
        switch (cmd)
        {
            case LOGIN:
                while (column < line.size())
                {
                    char ch = line[column];
                    if (std::isspace(static_cast<int>(ch)))
                    {
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
                        if (userID_.empty())
                        {
                            userID_ = line.substr(start, column - start);
                        }
                        else if (password_.empty())
                        {
                            password_ = line.substr(start, column - start);
                        }
                        else
                        {
                            std::cout << "Invalid\n";
                            is_more = true;
                            break;
                        }
                    }
                }
                if (is_more)
                    break;
                if (userID_.empty())
                {
                    std::cout << "Invalid\n";
                    break;
                }

                if (!userManager.login(userID_, password_))
                    std::cout << "Invalid\n";

                break;

            case LOGOUT:
                if (!userManager.logout())
                    std::cout << "Invalid\n";
                break;

            case REGISTER:
                while (column < line.size())
                {
                    char ch = line[column];
                    if (std::isspace(static_cast<int>(ch)))
                    {
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
                        if (userID_.empty())
                        {
                            userID_ = line.substr(start, column - start);
                        }
                        else if (password_.empty())
                        {
                            password_ = line.substr(start, column - start);
                        }
                        else if (username_.empty())
                        {
                            username_ = line.substr(start, column - start);
                        }
                        else
                        {
                            std::cout << "Invalid\n";
                            is_more = true;
                            break;
                        }
                    }
                }
                if (is_more)
                    break;

                if (userID_.empty() || password_.empty() || username_.empty())
                {
                    std::cout << "Invalid\n";
                    break;
                }
                if (!userManager.registerUser(userID_, password_, username_))
                    std::cout << "Invalid\n";

                break;
            case PASSWD:
                while (column < line.size())
                {
                    char ch = line[column];
                    if (std::isspace(static_cast<int>(ch)))
                    {
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
                        if (userID_.empty())
                        {
                            userID_ = line.substr(start, column - start);
                        }
                        else if (cur_Password_.empty())
                        {
                            cur_Password_ = line.substr(start, column - start);
                        }
                        else if (new_Password_.empty())
                        {
                            new_Password_ = line.substr(start, column - start);
                        }
                        else
                        {
                            std::cout << "Invalid\n";
                            is_more = true;
                            break;
                        }
                    }
                }

                if (is_more)
                    break;

                if (userID_.empty() || cur_Password_.empty())
                {
                    std::cout << "Invalid\n";
                    break;
                }
                if (!userManager.passwd(userID_, cur_Password_, new_Password_))
                    std::cout << "Invalid\n";

                break;
            case USERADD:
                while (column < line.size())
                {
                    char ch = line[column];
                    if (std::isspace(static_cast<int>(ch)))
                    {
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
                        if (userID_.empty())
                        {
                            userID_ = line.substr(start, column - start);
                        }
                        else if (password_.empty())
                        {
                            password_ = line.substr(start, column - start);
                        }
                        else if (privilegeLevel_ == -1)
                        {
                            std::string text = line.substr(start, column - start);
                            if (text.size() > 1 || text.empty())
                            {
                                std::cout << "Invalid\n";
                                break;
                            }
                            else if (text[0] != '0' && text[0] != '1' && text[0] != '3' && text[0] != '7')
                            {
                                std::cout << "Invalid\n";
                                break;
                            }
                            privilegeLevel_ = std::stoi(line.substr(start, column - start));
                        }
                        else if (username_.empty())
                        {
                            username_ = line.substr(start, column - start);
                        }
                        else
                        {
                            std::cout << "Invalid\n";
                            is_more = true;
                            break;
                        }
                    }
                }

                if (is_more)
                    break;

                if (userID_.empty() || password_.empty() || username_.empty() || privilegeLevel_ == -1)
                {
                    std::cout << "Invalid\n";
                    break;
                }

                if (!userManager.useradd(userID_, password_, privilegeLevel_, username_))
                    std::cout << "Invalid\n";

                break;
            case DELETEUSER:
                while (column < line.size())
                {
                    char ch = line[column];
                    if (std::isspace(static_cast<int>(ch)))
                    {
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
                        if (userID_.empty())
                        {
                            userID_ = line.substr(start, column - start);
                        }
                        else
                        {
                            std::cout << "Invalid\n";
                            is_more = true;
                            break;
                        }
                    }
                }

                if (is_more)
                    break;

                if (userID_.empty())
                {
                    std::cout << "Invalid\n";
                    break;
                }
                if (!userManager.deleteUser(userID_))
                    std::cout << "Invalid\n";

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
