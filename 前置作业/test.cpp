#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using std::fstream;
using std::string;

std::vector<std::pair<std::string, int>> name_index_pair;

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
    int head = 0; // 头块的索引
    book() {}
    book(std::string s)
    {
        std::memset(name, 0, sizeof(name));
        std::strncpy(name, s.c_str(), sizeof(name) - 1);
    }
};

MemoryRiver<book> file; // 记录的是书名到写入头位置的映射

struct Block
{
    int next_block; // 下一个块的索引，若不存在，则为-1
    int size; // 当前块存储的数据量
    int val[200]{};
    Block() : next_block(-1), size(0) {}
};

MemoryRiver<Block> info; // 记录的是书的value

void Insert();


void Find();

void Delete();

void split(Block &block, int val, int pos, int offset);

bool insert_val(Block &temp, int value, int block_index);

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
        name_index_pair.push_back(std::make_pair(t.name, start_index));
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

void split(Block &block, int val, int pos, int offset)
{
    int length = block.size + 1;
    std::vector<int> storage;
    storage.resize(length);
    storage[pos] = val;
    for (int i = 0; i < pos; i++)
        storage[i] = block.val[i];
    for (int i = pos + 1; i < length; i++)
        storage[i] = block.val[i - 1];
    std::memset(block.val, 0, sizeof(block.val));
    int left = length / 2;
    int right = length - left;
    for (int i = 0; i < left; i++)
    {
        block.val[i] = storage[i];
    }
    block.size = left;
    Block new_block;
    new_block.size = right;
    for (int i = left; i < length; i++)
    {
        new_block.val[i - left] = storage[i];
    }
    int next_point = block.next_block;
    new_block.next_block = next_point;
    block.next_block = info.write(new_block);
    info.update(block, offset);
}

bool insert_val(Block &temp, int value, int block_index)
{
    int *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
    int pos_index = pos - temp.val;
    if (pos_index < temp.size && *pos == value)
        return true;
    if (pos_index == temp.size)
        return false;
    if (temp.size < 200)
    {
        for (int i = temp.size; i > pos_index; --i)
        {
            temp.val[i] = temp.val[i - 1];
        }
        temp.val[pos_index] = value;
        ++temp.size;
        info.update(temp, block_index);
        return true;
    }
    else
    {
        split(temp, value, pos_index, block_index);
        return true;
    }
}

void Insert()
{
    std::string index;
    int value;
    std::cin >> index >> value;

    book t;

    for (int i = 0; i < name_index_pair.size(); i++)
    {
        if (name_index_pair[i].first == index)
        {
            int book_pos = name_index_pair[i].second;
            if (!file.read(t, book_pos))
                return;
            Block temp;
            if (!info.read(temp, t.head))
                return;
            int block_index = t.head;
            while (temp.next_block != -1)
            {
                if (insert_val(temp, value, block_index))
                {
                    return;
                }
                block_index = temp.next_block;
                info.read(temp, temp.next_block);
            }
            if (insert_val(temp, value, block_index))
                return;
            else
            {
                if (temp.size < 200)
                {
                    temp.val[temp.size] = value;
                    ++temp.size;
                    info.update(temp, block_index);
                    return;
                }
                else
                {
                    split(temp, value, 200, block_index);
                }
            }
            return;
        }
    }
    t = book(index);
    Block new_block;
    new_block.size = 1;
    new_block.val[0] = value;
    t.head = info.write(new_block);
    int pos = file.end();
    name_index_pair.push_back(std::make_pair(index, pos));
    file.write(t);
}

void Find()
{
    std::string index;
    std::cin >> index;

    int book_pos = 0;
    bool is_exist = false;
    for (int i = 0; i < name_index_pair.size(); i++)
    {
        if (name_index_pair[i].first == index)
        {
            is_exist = true;
            book_pos = name_index_pair[i].second;
            break;
        }
    }
    if (!is_exist)
    {
        std::cout << "null\n";
        return;
    }

    book t;
    if (!file.read(t, book_pos))
    {
        std::cout << "null\n";
        return;
    }

    bool is_empty = true;

    Block temp;

    info.read(temp, t.head);

    while (temp.next_block != -1)
    {
        if (temp.size != 0)
            is_empty = false;
        for (int i = 0; i < temp.size; i++)
        {
            std::cout << temp.val[i] << " ";
        }
        info.read(temp, temp.next_block);
    }

    if (temp.size != 0)
        is_empty = false;
    if (is_empty)
    {
        std::cout << "null\n";
    }
    else
    {
        for (int i = 0; i < temp.size; i++)
        {
            std::cout << temp.val[i] << " ";
        }
        std::cout << '\n';
    }
}

bool delete_val(Block &temp, int value, int block_index)
{
    int *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
    if (pos == temp.val + temp.size || *pos != value)
    {
        return false;
    }
    else
    {
        int pos_index = pos - temp.val;
        for (int i = pos_index; i < temp.size - 1; i++)
        {
            temp.val[i] = temp.val[i + 1];
        }
        temp.val[temp.size - 1] = 0;
        --temp.size;
        info.update(temp, block_index);
    }
    return true;
}

void merge(Block &block, int offset)
{
    Block next_block;
    info.read(next_block, block.next_block);
    int length = block.size + next_block.size;
    std::vector<int> storage;
    storage.resize(length);
    for (int i = 0; i < block.size; i++)
    {
        storage[i] = block.val[i];
    }
    for (int i = block.size; i < length; i++)
    {
        storage[i] = next_block.val[i - block.size];
    }
    std::memset(block.val, 0, sizeof(block.val));
    for (int i = 0; i < length; i++)
    {
        block.val[i] = storage[i];
    }
    block.next_block = next_block.next_block;
    block.size = length;
    info.update(block, offset);
}

void Delete()
{
    std::string index;
    int value;
    std::cin >> index >> value;

    book t;
    for (int i = 0; i < name_index_pair.size(); i++)
    {
        if (name_index_pair[i].first == index)
        {
            int book_pos = name_index_pair[i].second;
            if (!file.read(t, book_pos))
                return;
            Block temp;

            if (!info.read(temp, t.head))
                return;
            int block_index = t.head;
            while (temp.next_block != -1)
            {
                if (!delete_val(temp, value, block_index))
                {
                    block_index = temp.next_block;
                    info.read(temp, temp.next_block);
                }
                else
                {
                    Block next;
                    while (temp.next_block != -1)
                    {

                        info.read(next, temp.next_block);
                        if (temp.size + next.size <= 200)
                            merge(temp, block_index);
                        else
                            break;
                    }
                    return;
                }
            }
            if (!delete_val(temp, value, block_index))
            {
                return;
            }
        }
    }
}
