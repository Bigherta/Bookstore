#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>

using std::fstream;
using std::string;

std::unordered_map<std::string, int> name_index_map;

template<class T>
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
        std::ifstream fin(file_name, std::ios::binary);
        bool is_exist = fin.is_open();
        fin.close();
        if (!is_exist)
        {
            file.open(file_name, std::ios::out | std::ios::binary);
        }
        file.close();
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
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

    bool read(T &t, const int index)
    {
        file.seekg(index);
        if (file.read(reinterpret_cast<char *>(&t), sizeofT))
        {
            return true;
        }
        return false;
    }
    int end()
    {
        file.seekg(0, std::ios::end);
        return file.tellg();
    }
};

struct book
{
    char name[65]{};
    int used = 0;
    int index = 0;
    book() {}
    book(std::string s)
    {
        used = 1;
        std::memset(name, 0, sizeof(name));
        std::strncpy(name, s.c_str(), sizeof(name) - 1);
    }
};

MemoryRiver<book> file; // 记录的是书名到写入头位置的映射

MemoryRiver<int[100000]> info; // 记录的是书的value

void Insert();

void Delete();

void Find();

int main()
{
    file.initialise("index");
    info.initialise("information");
    book t;
    int start_index = 0;
    int file_end = file.end();
    while (start_index + sizeof(t) <= file_end)
    {
        file.read(t, start_index);
        name_index_map.emplace(t.name, start_index);
        start_index += sizeof(t);
    }

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::string command;
        std::cin >> command;
        if (command == "insert")
        {
            Insert();
        }
        if (command == "find")
        {
            Find();
        }
        if (command == "delete")
        {
            Delete();
        }
    }
    return 0;
}
void Insert()
{
    std::string index;
    int value;
    std::cin >> index >> value;

    book t;
    if (name_index_map.count(index))
    {
        int book_pos = name_index_map[index];
        if (!file.read(t, book_pos))
            return;

        int temp[100000];
        if (!info.read(temp, t.index))
            return;

        int *pos = std::lower_bound(temp, temp + t.used, value);
        int pos_index = pos - temp;

        if (pos_index < t.used && temp[pos_index] == value)
            return;

        for (int i = t.used; i > pos_index; --i)
        {
            temp[i] = temp[i - 1];
        }
        temp[pos_index] = value;

        info.update(temp, t.index);
        
        ++t.used;
        file.update(t, book_pos);
        return;
    }

    t = book(index);
    int val[100000]{};
    val[0] = value;
    t.index = info.write(val);
    int pos = file.end();
    name_index_map.emplace(index, pos);
    file.write(t);
}

void Delete()
{
    std::string index;
    int value;
    std::cin >> index >> value;

    if (!name_index_map.count(index))
        return;

    int book_pos = name_index_map[index];
    book t;
    if (!file.read(t, book_pos))
        return;

    if (t.used == 0)
        return;

    int temp[100000];
    if (!info.read(temp, t.index))
        return;

    int *pos = std::lower_bound(temp, temp + t.used, value);
    int pos_index = pos - temp;

    if (pos_index >= t.used || temp[pos_index] != value)
        return;

    for (int i = pos_index; i < t.used - 1; ++i)
    {
        temp[i] = temp[i + 1];
    }
    temp[t.used - 1] = 0;
    --t.used;

    info.update(temp, t.index);
    file.update(t, book_pos);
}

void Find()
{
    std::string index;
    std::cin >> index;

    if (!name_index_map.count(index))
    {
        std::cout << "null\n";
        return;
    }

    int book_pos = name_index_map[index];
    book t;
    if (!file.read(t, book_pos))
    {
        std::cout << "null\n";
        return;
    }

    if (t.used == 0)
    {
        std::cout << "null\n";
        return;
    }

    int temp[100000];
    if (!info.read(temp, t.index))
    {
        std::cout << "null\n";
        return;
    }

    for (int i = 0; i < t.used; ++i)
    {
        if (i)
            std::cout << ' ';
        std::cout << temp[i];
    }
    std::cout << '\n';
}
