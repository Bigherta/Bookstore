
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using std::fstream;
using std::string;

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
    int head = 0;
    book() {}
    book(std::string s)
    {
        std::memset(name, 0, sizeof(name));
        std::strncpy(name, s.c_str(), sizeof(name) - 1);
    }
};

template<class T>
class storage
{
public:
    struct Block
    {
        int next_block; // 下一个块的索引，若不存在，则为-1
        int size; // 当前块存储的数据量
        T val[200]{};
        Block() : next_block(-1), size(0) {}
    };

    MemoryRiver<book> file; // 记录的是书名到写入头位置的映射
    MemoryRiver<Block> info; // 记录的是书的value
    
    std::vector<std::pair<std::string, int>> name_index_pair;
    void init()
    {
        file.initialise("index");
        info.initialise("information");
        book t;
        int start_index = 0;
        int file_end = file.end();
        while (start_index + sizeof(t) <= file_end)
        {
            file.read(t, start_index);
            name_index_pair.push_back(std::make_pair(t.name, start_index));
            start_index += sizeof(t);
        }
    }

    void Insert();

    void Find();

    void Delete();

    void split(Block &block, int val, int pos, int offset);

    void merge(Block &block, int offset);

    bool insert_val(Block &temp, int value, int block_index);

    bool delete_val(Block &temp, int value, int block_index);
};
