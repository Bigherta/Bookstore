#include "../include/log.hpp"
#include "../include/parser.hpp"
#include "../include/user.hpp"

std::vector<std::pair<std::string, int>> name_index_pair;

int main()
{
    Parser parser;
    UserManager userManager;
    log Log;
    std::string line;
    while (std::getline(std::cin, line))
    {
        parser.execute(line, userManager, Log);
    }
    return 0;
}
