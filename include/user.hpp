#pragma once
#ifndef USER_HPP
#define USER_HPP

#include "storage.hpp"
#include <cstring>
#include <string>
#include <utility>
#include <vector>


class user
{
public:
    char userID[31];
    char username[31];
    char password[31];
    int privilegeLevel = 0; // 0: visitor, 1: customer, 3: worker, 7: manager
    bool is_valid = true;

    user() {}

    user(const std::string &userID_, const std::string &username_, const std::string &password_,
         int privilegeLevel_ = 0) : privilegeLevel(privilegeLevel_)
    {
        std::strncpy(userID, userID_.c_str(), userID_.size());
        userID[userID_.size()] = '\0';
        std::strncpy(username, username_.c_str(), username_.size());
        username[username_.size()] = '\0';
        std::strncpy(password, password_.c_str(), password_.size());
        password[password_.size()] = '\0';
    }
};

class UserManager
{
public:
    UserManager();

    auto &get_stack() {return logstack;}

    int count(const std::string &userID_);

    bool is_log(const std::string &);

    bool login(const std::string &userID_, const std::string &password_);

    bool logout();

    bool registerUser(const std::string &userID_, const std::string &password_, const std::string &username_);

    bool passwd(const std::string &userID_, const std::string &cur_Password_, const std::string &new_Password_);

    bool useradd(const std::string &userID_, const std::string &password_, int privilegeLevel_,
                 const std::string &username_);

    bool deleteUser(const std::string &userID_);

    user &getCurrentUser();

    std::string &getSelectedbook();

private:
    MemoryRiver<user> userDatabase;

    std::vector<std::pair<std::string, std::string>> logstack;

    user currentUser;
};
#endif