#include "../include/user.hpp"
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include "../include/validator.hpp"

UserManager::UserManager()
{
    userDatabase.initialise("userData");
    // 初始化时保证存在默认管理员账户 root
    if (count("root") == -1)
    {
        user admin("root", "root", "sjtu", 7);
        userDatabase.write(admin);
    }
}

bool user::is_ID_or_passwd_valid(const std::string &ID_or_passwd)
{
    try
    {
        expect(ID_or_passwd.size()).ge(0).And().le(30);
        expect(ID_or_passwd).toMatch("^[A-Za-z0-9_]+$");
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool user::is_name_valid(const std::string &name)
{
    try
    {
        expect(name.size()).ge(0).And().le(30);
        expect(name).toMatch("^[\x21-\x7E]+$");
    }
    catch (...)
    {
        return false;
    }
    return true;
}


// 检查用户是否存在，返回其在数据库中的位置(不存在返回-1)
int UserManager::count(const std::string &userID_)
{
    int start_index = 2 * sizeof(int);
    user temp{};
    int user_data_end = userDatabase.end();
    while (start_index + sizeof(user) <= user_data_end)
    {
        userDatabase.read(temp, start_index);
        if (std::strcmp(temp.userID, userID_.c_str()) == 0 && temp.is_valid)
            return start_index;
        start_index += sizeof(user);
    }
    return -1;
}

// 检查用户是否已登录
bool UserManager::is_log(const std::string &userID_)
{
    for (auto i = logstack.begin(); i != logstack.end(); i++)
        if (i->first == userID_)
            return true;
    return false;
}

// 用户登录：支持密码登录或权限提升登录
bool UserManager::login(const std::string &userID_, const std::string &password_)
{
    int pos = count(userID_);
    if (pos == -1)
        return false;
    user temp{};
    userDatabase.read(temp, pos);

    // 权限检查和密码匹配
    // 如果密码为空，则检查当前用户权限是否高于目标用户
    if (!password_.empty() && password_ != temp.password)
        return false;

    if (password_.empty() && currentUser.privilegeLevel <= temp.privilegeLevel)
        return false;

    logstack.push_back(make_pair(temp.userID, std::string()));
    currentUser = temp;
    return true;
}

// 用户登出：弹出登录栈顶用户
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
        currentUser = user(); // 重置为默认用户
    }
    return true;
}

// 注册新用户：检查用户名唯一性，设置默认权限，写入数据库
bool UserManager::registerUser(const std::string &userID_, const std::string &password_, const std::string &username_)
{
    if (count(userID_) != -1)
        return false; // 用户已存在
    if (!user::is_ID_or_passwd_valid(userID_) || !user::is_ID_or_passwd_valid(password_) ||
        !user::is_name_valid(username_)) // 验证合法性
        return false;

    user newUser(userID_, username_, password_, 1);
    userDatabase.write(newUser);
    return true;
}

// 修改密码：支持用户自己修改或管理员修改他人密码
bool UserManager::passwd(const std::string &userID_, const std::string &cur_Password_, const std::string &new_Password_)
{

    // 检查密码合法性(如果提供旧密码)

    if (!user::is_ID_or_passwd_valid(new_Password_))
        return false;
    if (!user::is_ID_or_passwd_valid(cur_Password_) && !cur_Password_.empty())
        return false;

    int pos = count(userID_);
    if (pos == -1 || currentUser.privilegeLevel < 1)
        return false;

    user temp{};
    userDatabase.read(temp, pos);

    // 权限检查：管理员可以不提供旧密码
    if (currentUser.privilegeLevel < 7 && cur_Password_.empty())
        return false;

    // 验证旧密码（如果提供）
    if (!cur_Password_.empty())
        if (cur_Password_ != temp.password)
            return false;

    std::snprintf(temp.password, sizeof(temp.password), "%s", new_Password_.c_str());
    userDatabase.update(temp, pos);
    return true;
}

// 添加新用户
bool UserManager::useradd(const std::string &userID_, const std::string &password_, int privilegeLevel_,
                          const std::string &username_)
{
    if (!user::is_ID_or_passwd_valid(userID_) || !user::is_ID_or_passwd_valid(password_) ||
        !user::is_name_valid(username_)) // 验证合法性
        return false;

    // 权限与重复检查
    if (privilegeLevel_ >= currentUser.privilegeLevel || count(userID_) != -1 || currentUser.privilegeLevel < 3)
        return false;

    user newUser(userID_, username_, password_, privilegeLevel_);
    userDatabase.write(newUser);
    return true;
}

// 删除用户
bool UserManager::deleteUser(const std::string &userID_)
{
    int pos = count(userID_);
    if (pos == -1 || is_log(userID_) || currentUser.privilegeLevel < 7)
        return false;
    user temp{};
    userDatabase.read(temp, pos);
    temp.is_valid = false;
    userDatabase.update(temp, pos);
    return true;
}

// 获取当前登录用户
user &UserManager::getCurrentUser() { return currentUser; }

bool UserManager::is_valid_to_getSelectedbook() { return !(logstack.empty()); }

// 获取当前操作的选中书籍 ISBN
std::string &UserManager::getSelectedbook() { return logstack.back().second; }

// 退出时清空登录栈
void UserManager::exit()
{
    logstack.clear();
    currentUser = user();
}
