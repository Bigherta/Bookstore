#pragma once
#ifndef USER_HPP
#define USER_HPP

#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include "storage.hpp"


class user
{
public:
    char userID[31]{};
    char username[31]{};
    char password[31]{};
    int privilegeLevel = 0; // 0: visitor, 1: customer, 3: worker, 7: manager
    bool is_valid = true;

    user() {}

    user(const std::string &userID_, const std::string &username_, const std::string &password_,
         int privilegeLevel_ = 0) : privilegeLevel(privilegeLevel_)
    {
        std::snprintf(userID, sizeof(userID), "%s", userID_.c_str());
        std::snprintf(username, sizeof(username), "%s", username_.c_str());
        std::snprintf(password, sizeof(password), "%s", password_.c_str());
    }
};

class UserManager
{
public:
    /**
     * @brief 构造函数，初始化 UserManager 对象
     */
    UserManager();

    /**
     * @brief 获取登录/操作记录栈
     * @return 引用，指向 logstack 向量，记录用户ID和操作描述
     */
    auto &get_stack() { return logstack; }

    /**
     * @brief 统计指定用户在数据库中出现的次数
     * @param userID_ 要查询的用户ID
     * @return int 返回出现次数，0 表示用户不存在
     */
    int count(const std::string &userID_);

    /**
     * @brief 检查指定用户是否已登录
     * @param userID_ 要检查的用户ID
     * @return true 如果用户已登录
     * @return false 如果用户未登录
     */
    bool is_log(const std::string &userID_);

    /**
     * @brief 用户登录操作
     * @param userID_ 用户ID
     * @param password_ 用户密码
     * @return true 登录成功
     * @return false 登录失败（用户不存在或密码错误）
     */
    bool login(const std::string &userID_, const std::string &password_);

    /**
     * @brief 用户登出操作
     * @return true 登出成功
     * @return false 当前没有用户登录
     */
    bool logout();

    /**
     * @brief 用户注册
     * @param userID_ 用户ID
     * @param password_ 用户密码
     * @param username_ 用户姓名
     * @return true 注册成功
     * @return false 注册失败（用户ID已存在或参数非法）
     */
    bool registerUser(const std::string &userID_, const std::string &password_, const std::string &username_);

    /**
     * @brief 修改用户密码
     * @param userID_ 用户ID
     * @param cur_Password_ 当前密码
     * @param new_Password_ 新密码
     * @return true 修改成功
     * @return false 当前密码错误或用户不存在
     */
    bool passwd(const std::string &userID_, const std::string &cur_Password_, const std::string &new_Password_);

    /**
     * @brief 管理员添加新用户
     * @param userID_ 用户ID
     * @param password_ 用户密码
     * @param privilegeLevel_ 权限等级（0: visitor, 1: customer, 3: worker, 7: manager）
     * @param username_ 用户姓名
     * @return true 添加成功
     * @return false 用户ID已存在或权限不足
     */
    bool useradd(const std::string &userID_, const std::string &password_, int privilegeLevel_,
                 const std::string &username_);

    /**
     * @brief 管理员删除用户
     * @param userID_ 要删除的用户ID
     * @return true 删除成功
     * @return false 用户不存在或权限不足
     */
    bool deleteUser(const std::string &userID_);

    /**
     * @brief 获取当前登录用户对象
     * @return user& 当前用户的引用
     */
    user &getCurrentUser();

    /**
     * @brief 获取当前选中的书籍
     * @return std::string& 当前选中的书籍 ISBN 或标识符
     */
    std::string &getSelectedbook();

    bool is_valid_to_getSelectedbook();

    void exit ();

private:
    /// 用户数据库，使用 MemoryRiver 存储 user 对象
    MemoryRiver<user> userDatabase;

    /// 用户操作记录栈，每条记录为 <userID, 操作描述>
    std::vector<std::pair<std::string, std::string>> logstack;

    /// 当前登录用户
    user currentUser;
};

#endif
