#include "../include/user.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include "../include/parser.hpp"
#include "../include/Token.hpp"

UserManager::UserManager() {
    // Initialize with a default manager account
    user admin = {"root", "root", "sjtu", 7, false};
    userDatabase.emplace("root", admin);
}

bool UserManager::login(const std::string &userID_, const std::string &password_) {
    if (!userDatabase.count(userID_))
        return false;
    if (password_.empty() && currentUser.privilegeLevel <= userDatabase[userID_].privilegeLevel)
        return false;
    if (!password_.empty() && password_ != userDatabase[userID_].password)
        return false;
    userDatabase[userID_].log_status = true;
    logstack.push_back(userDatabase[userID_]);
    currentUser = userDatabase[userID_];
    return true;
}

bool UserManager::logout() {
    if (logstack.size() == 0 || currentUser.privilegeLevel < 1)
        return false;
    userDatabase[currentUser.userID].log_status = false;
    std::cout << "Goodbye, " << currentUser.userID << "\n";
    logstack.pop_back();
    if (!logstack.empty())
        currentUser = logstack.back();
    return true;
}

bool UserManager::registerUser(const std::string &userID_, const std::string &password_, const std::string &username_) {
    if (userDatabase.count(userID_))
        return false;
    if (userID_.size() > 30 || password_.size() > 30 || username_.size() > 30)
        return false;
    for (char ch: userID_) {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }
    for (char ch: password_) {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }

    user newUser = {userID_, username_, password_, 1};
    userDatabase.emplace(userID_, newUser);
    return true;
}

bool UserManager::passwd(const std::string &userID_, const std::string &cur_Password_,
                         const std::string &new_Password_) {
    if (new_Password_.size() > 30)
        return false;

    for (char ch: new_Password_) {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }
    if (!userDatabase.count(userID_) || currentUser.privilegeLevel < 1)
        return false;
    if (currentUser.privilegeLevel < 7 && new_Password_.empty())
        return false;
    if (!new_Password_.empty()) {
        if (cur_Password_ != userDatabase[userID_].password)
            return false;
        userDatabase[userID_].password = new_Password_;
    } else {
        userDatabase[userID_].password = cur_Password_;
    }
    return true;
}

bool UserManager::useradd(const std::string &userID_, const std::string &password_, int privilegeLevel_,
                          const std::string &username_) {
    if (userID_.size() > 30 || password_.size() > 30 || username_.size() > 30)
        return false;
    for (char ch: userID_) {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }
    for (char ch: password_) {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }

    if (privilegeLevel_ >= currentUser.privilegeLevel || userDatabase.count(userID_) || currentUser.privilegeLevel < 3)
        return false;
    user newUser = {userID_, username_, password_, privilegeLevel_};
    userDatabase.emplace(userID_, newUser);
    return true;
}

bool UserManager::deleteUser(const std::string &userID_) {
    if (!userDatabase.count(userID_) || userDatabase[userID_].log_status || currentUser.privilegeLevel < 7)
        return false;
    userDatabase.erase(userID_);
    return true;
}


int main() {
    TokenStream tokens_;
    Parser parser;
    UserManager userManager;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;
        tokens_ = parser.tokenize(line);
        std::string userID_, password_, username_, new_Password_, cur_Password_;
        int privilegeLevel_ = -1;
        const TokenType cmd = tokens_.get()->type;
        switch (cmd) {
            case LOGIN: {
                if (tokens_.size() > 3 || tokens_.size() < 2) {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                if (tokens_.peek() != nullptr)
                    password_ = tokens_.get()->text;

                if (!userManager.login(userID_, password_))
                    std::cout << "Invalid\n";

                else {
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
                if (tokens_.size() != 4) {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                password_ = tokens_.get()->text;

                username_ = tokens_.get()->text;

                if (!userManager.registerUser(userID_, password_, username_))
                    std::cout << "Invalid\n";
                else {
                    std::cout << "Register" << userID_ << " successfully\n";
                }
                break;
            }

            case PASSWD: {
                if (tokens_.size() < 3 || tokens_.size() > 4) {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                cur_Password_ = tokens_.get()->text;

                if (tokens_.peek() != nullptr)
                    new_Password_ = tokens_.get()->text;

                if (!userManager.passwd(userID_, cur_Password_, new_Password_))
                    std::cout << "Invalid\n";
                else {
                    std::cout << "Change password of " << userID_ << " successfully\n";
                }
                break;
            }

            case USERADD: {
                if (tokens_.size() != 5) {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                password_ = tokens_.get()->text;

                std::string temp_text = tokens_.get()->text;

                if (temp_text.size() != 1) {
                    std::cout << "Invalid\n";
                    break;
                } else if (temp_text[0] != '0' && temp_text[0] != '1' && temp_text[0] != '3' && temp_text[0] != '7') {
                    std::cout << "Invalid\n";
                    break;
                }

                privilegeLevel_ = std::stoi(temp_text);

                username_ = tokens_.get()->text;

                if (!userManager.useradd(userID_, password_, privilegeLevel_, username_))
                    std::cout << "Invalid\n";
                else {
                    std::cout << "Add user " << userID_ << " successfully\n";
                }
                break;
            }
            case DELETEUSER: {
                if (tokens_.size() != 2) {
                    std::cout << "Invalid\n";
                    break;
                }
                userID_ = tokens_.get()->text;

                if (!userManager.deleteUser(userID_))
                    std::cout << "Invalid\n";
                else {
                    std::cout << "Delete user " << userID_ << " successfully\n";
                }
                break;
            }
            case TEXT:
                std::cout << "Invalid\n";
                break;

            case EXIT:
                std::cout << "Goodbye\n";
                return 0;

            default:
                break;
        }
    }
    return 0;
}
