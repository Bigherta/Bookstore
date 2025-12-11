
#include <string>
#include <unordered_map>
#include <vector>


struct user
{
    std::string userID;
    std::string username;
    std::string password;
    int privilegeLevel = 0; // 0: visitor, 1: customer, 3: worker, 7: manager
    bool log_status = false;
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

    
private:
    std::unordered_map<std::string, user> userDatabase; // userID -> user

    std::vector<user> logstack;

    user currentUser;
};
