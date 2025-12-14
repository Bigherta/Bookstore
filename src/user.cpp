#include "../include/user.hpp"
#include <cctype>
#include <cstring>
#include <string>

UserManager::UserManager()
{
    // Initialize with a default manager account
    if (count("root") == -1)
    {
        user admin("root", "root", "sjtu", 7);
        userDatabase.initialise("userData");
        userDatabase.write(admin);
    }
}

int UserManager::count(const std::string &userID_)
{
    userDatabase.initialise("userData");
    int start_index = 2 * sizeof(int);
    user temp;
    int user_data_end = userDatabase.end();
    while (start_index + sizeof(user) <= user_data_end)
    {
        userDatabase.read(temp, start_index);
        if (std::strcmp(temp.userID, userID_.c_str()) == 0 && temp.is_valid)
        {
            return start_index;
        }
        start_index += sizeof(user);
    }
    return -1;
}

bool UserManager::is_log(const std::string &userID_)
{
    for (auto i = logstack.begin(); i != logstack.end(); i++)
    {
        std::string id = i->first;
        if (id == userID_)
            return true;
    }
    return false;
}

bool UserManager::login(const std::string &userID_, const std::string &password_)
{
    int pos = count(userID_);
    if (pos == -1)
        return false;
    user temp;
    userDatabase.read(temp, pos);
    if (password_.empty() && currentUser.privilegeLevel <= temp.privilegeLevel)
        return false;
    if (!password_.empty() && password_ != temp.password)
        return false;
    logstack.push_back(make_pair(temp.userID, std::string()));
    currentUser = temp;
    return true;
}

bool UserManager::logout()
{
    if (logstack.size() == 0 || currentUser.privilegeLevel < 1)
        return false;
    logstack.pop_back();
    if (!logstack.empty())
    {
        int pos = count(logstack.back().first);
        userDatabase.read(currentUser, pos);
    }
    else
    {
        currentUser = user();
    }
    return true;
}

bool UserManager::registerUser(const std::string &userID_, const std::string &password_, const std::string &username_)
{
    if (count(userID_) != -1)
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

    user newUser(userID_, username_, password_, 1);
    userDatabase.write(newUser);
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
    int pos = count(userID_);
    if (pos == -1 || currentUser.privilegeLevel < 1)
        return false;

    user temp;

    userDatabase.read(temp, pos);

    if (currentUser.privilegeLevel < 7 && new_Password_.empty())
        return false;
    if (!new_Password_.empty())
    {
        if (cur_Password_ != temp.password)
            return false;
        std::strncpy(temp.password, new_Password_.c_str(), new_Password_.size());
        temp.password[new_Password_.size()] = '\0';
        userDatabase.update(temp, pos);
    }
    else
    {
        std::strncpy(temp.password, cur_Password_.c_str(), cur_Password_.size());
        temp.password[cur_Password_.size()] = '\0';
        userDatabase.update(temp, pos);
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

    if (privilegeLevel_ >= currentUser.privilegeLevel || count(userID_) != -1 || currentUser.privilegeLevel < 3)
        return false;
    user newUser(userID_, username_, password_, privilegeLevel_);
    userDatabase.write(newUser);
    return true;
}

bool UserManager::deleteUser(const std::string &userID_)
{
    int pos = count(userID_);
    if (pos == -1 || is_log(userID_) || currentUser.privilegeLevel < 7)
        return false;
    user temp;
    userDatabase.read(temp, pos);
    temp.is_valid = false;
    userDatabase.update(temp, pos);
    return true;
}

user &UserManager::getCurrentUser() { return currentUser; }

std::string &UserManager::getSelectedbook() { return logstack.back().second; }
