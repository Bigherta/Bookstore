#include "../include/user.hpp"
#include <cctype>
#include <string>

UserManager::UserManager()
{
    // Initialize with a default manager account
    user admin = {"root", "root", "sjtu", 7, false};
    userDatabase.emplace("root", admin);
}

bool UserManager::login(const std::string &userID_, const std::string &password_)
{
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

bool UserManager::logout()
{
    if (logstack.size() == 0 || currentUser.privilegeLevel < 1)
        return false;
    userDatabase[currentUser.userID].log_status = false;
    logstack.pop_back();
    currentUser = logstack.back();
    return true;
}

bool UserManager::registerUser(const std::string &userID_, const std::string &password_, const std::string &username_)
{
    if (userDatabase.count(userID_))
        return false;
    if (userID_.size() > 30 || password_.size() > 30 || username_.size() > 30)
        return false;
    for (char ch: userID_)
    {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }
    for (char ch: password_)
    {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }

    user newUser = {userID_, username_, password_, 1};
    userDatabase.emplace(userID_, newUser);
    return true;
}

bool UserManager::passwd(const std::string &userID_, const std::string &cur_Password_, const std::string &new_Password_)
{
    if (new_Password_.size() > 30)
        return false;

    for (char ch: new_Password_)
    {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }
    if (!userDatabase.count(userID_) || currentUser.privilegeLevel < 1)
        return false;
    if (currentUser.privilegeLevel < 7 && new_Password_.empty())
        return false;
    if (!new_Password_.empty())
    {
        if (cur_Password_ != userDatabase[userID_].password)
            return false;
        userDatabase[userID_].password = new_Password_;
    }
    else
    {
        userDatabase[userID_].password = cur_Password_;
    }
    return true;
}

bool UserManager::useradd(const std::string &userID_, const std::string &password_, int privilegeLevel_,
                          const std::string &username_)
{
    if (userID_.size() > 30 || password_.size() > 30 || username_.size() > 30)
        return false;
    for (char ch: userID_)
    {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }
    for (char ch: password_)
    {
        if (!std::isalnum(ch) && ch != '_')
            return false;
    }

    if (privilegeLevel_ >= currentUser.privilegeLevel || userDatabase.count(userID_) || currentUser.privilegeLevel < 3)
        return false;
    user newUser = {userID_, username_, password_, privilegeLevel_};
    userDatabase.emplace(userID_, newUser);
    return true;
}

bool UserManager::deleteUser(const std::string &userID_)
{
    if (!userDatabase.count(userID_) || userDatabase[userID_].log_status || currentUser.privilegeLevel < 7)
        return false;
    userDatabase.erase(userID_);
    return true;
}
