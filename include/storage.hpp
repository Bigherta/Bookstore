
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

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
        std::ifstream fin(file_name, std::ios::binary);
        bool is_exist = fin.is_open();
        fin.close();
        if (!is_exist)
        {
            file.open(file_name, std::ios::out | std::ios::binary);
            int tmp = 0;
            for (int i = 0; i < info_len; ++i)
                file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        }
        file.close();
        file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    }

    // 读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n)
    {
        if (n > info_len)
            return;
        /* your code here */

        file.seekg((n - 1) * sizeof(int));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    }

    // 将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n)
    {
        if (n > info_len)
            return;
        /* your code here */

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

struct index_to_head
{
    char name[65]{};
    int head = 0;
    index_to_head() {}
    index_to_head(std::string s)
    {
        std::memset(name, 0, sizeof(name));
        std::strncpy(name, s.c_str(), sizeof(name) - 1);
    }
};

template<class T>
class storage
{
private: 
    std::string index_name;
public:
    storage(std::string s) : index_name(s) {}

    struct Block
    {
        int next_block; // 下一个块的索引，若不存在，则为-1
        int size; // 当前块存储的数据量
        T val[200]{};
        Block() : next_block(-1), size(0) {}
    };

    MemoryRiver<index_to_head> file; // 记录的是书名到写入头位置的映射
    MemoryRiver<Block> book; // 记录的是书的value
    
    void init(std::vector<std::pair<std::string, int>> &);

    void Insert(T, std::vector<std::pair<std::string, int>> &);

    void Find(const std::vector<std::pair<std::string, int>> &);

    void Delete(T, std::vector<std::pair<std::string, int>> &);

    void split(Block &block, T val, int pos, int offset);

    void merge(Block &block, int offset);

    bool insert_val(Block &temp, T value, int block_index);

    bool delete_val(Block &temp, T value, int block_index);
};
