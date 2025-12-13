
#include <string>
#include <unordered_map>
#include <vector>


class user
{
public:
    std::string userID;
    std::string username;
    std::string password;
    std::string selectedBookISBN;
    int privilegeLevel = 0; // 0: visitor, 1: customer, 3: worker, 7: manager

    bool log_status = false;

    user() {}

    user(const std::string &userID_, const std::string &username_, const std::string &password_,
         int privilegeLevel_ = 0) :
        userID(userID_), username(username_), password(password_), privilegeLevel(privilegeLevel_)
    {
    }
};

class UserManager
{
public:
    UserManager();

    bool login(const std::string &userID_, const std::string &password_);

    bool logout();

    bool registerUser(const std::string &userID_, const std::string &password_, const std::string &username_);

    bool passwd(const std::string &userID_, const std::string &cur_Password_, const std::string &new_Password_);

    bool useradd(const std::string &userID_, const std::string &password_, int privilegeLevel_,
                 const std::string &username_);

    bool deleteUser(const std::string &userID_);

    user &getCurrentUser();

private:
    std::unordered_map<std::string, user> userDatabase; // userID -> user

    std::vector<user> logstack;

    user currentUser;
};
