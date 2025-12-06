#include <fstream>
#include <iostream>

using std::fstream;
using std::string;

template<class T, int info_len = 2>
class MemoryRiver
{
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);

public:
    MemoryRiver() = default;

    MemoryRiver(const string &file_name) : file_name(file_name) {}

    ~MemoryRiver()
    {
        if (file.is_open())
            file.close();
    }
    void initialise(string FN = "")
    {
        if (FN != "")
            file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    }

    void get_info(int &tmp, int n)
    {
        if (n > info_len)
            return;
        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    void write_info(int tmp, int n)
    {
        if (n > info_len)
            return;

        file.seekp((n - 1) * sizeof(int));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    int write(T &t)
    {
        file.seekp(0, std::ios::end);
        int pos = file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeofT);

        return pos;
    }

    void update(T &t, const int index)
    {
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
    }

    void read(T &t, const int index)
    {
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&t), sizeofT);
    }
    void Delete(int index) { return; }
};

void Insert();

void Delete();

void Find();

int main()
{
    MemoryRiver<std::string> file;
    file.initialise("bookstore");
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::string command;
        std::cin >> command;
        if (command == "insdert")
        {
            Insert();
        }
    }
    return 0;
}

void insert()
{
    std::string index;
    int value;
    std::cin >> index >> value;
    
}

