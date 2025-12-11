#include "../include/storage.hpp"
#include <algorithm>

template<class T>
void storage<T>::init(std::vector<std::pair<std::string, int>> &name_index_pair_)
{
    file.initialise("index");
    book.initialise("book");
    index_to_head t;
    int start_index = 2 * sizeof(int);
    int file_end = file.end();
    while (start_index + sizeof(t) <= file_end)
    {
        file.read(t, start_index);
        name_index_pair_.push_back(std::make_pair(t.name, start_index));
        start_index += sizeof(t);
    }
}

template<class T>
void storage<T>::split(Block &block, T val, int pos, int offset)
{
    int length = block.size + 1;
    std::vector<T> storage;
    storage.resize(length);
    storage[pos] = val;
    for (int i = 0; i < pos; i++)
        storage[i] = block.val[i];
    for (int i = pos + 1; i < length; i++)
        storage[i] = block.val[i - 1];
    for (int i = 0; i < 200; i++)
        block.val[i] = T();

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
    block.next_block = book.write(new_block);
    book.update(block, offset);
}
// 裂块

template<class T>
bool storage<T>::insert_val(Block &temp, T value, int block_index)
{
    T *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
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
        book.update(temp, block_index);
        return true;
    }
    else
    {
        split(temp, value, pos_index, block_index);
        return true;
    }
}
// 插入值的具体操作
template<class T>
void storage<T>::Insert(T value, std::vector<std::pair<std::string, int>> &name_index_pair_)
{
    index_to_head t;

    for (int i = 0; i < name_index_pair_.size(); i++)
    {
        if (name_index_pair_[i].first == index_name)
        {
            int book_pos = name_index_pair_[i].second;
            if (!file.read(t, book_pos))
                return;
            Block temp;
            if (!book.read(temp, t.head))
                return;
            int block_index = t.head;
            while (temp.next_block != -1)
            {
                if (insert_val(temp, value, block_index))
                {
                    return;
                }
                block_index = temp.next_block;
                book.read(temp, temp.next_block);
            }
            if (insert_val(temp, value, block_index))
                return;
            else
            {
                if (temp.size < 200)
                {
                    temp.val[temp.size] = value;
                    ++temp.size;
                    book.update(temp, block_index);
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
    t = index_to_head(index_name);
    Block new_block;
    new_block.size = 1;
    new_block.val[0] = value;
    t.head = book.write(new_block);
    int pos = file.end();
    name_index_pair_.push_back(std::make_pair(index_name, pos));
    file.write(t);
}
// 插入一个值
template<class T>
void storage<T>::Find(const std::vector<std::pair<std::string, int>> &name_index_pair_)
{
    int book_pos = 0;
    bool is_exist = false;
    for (int i = 0; i < name_index_pair_.size(); i++)
    {
        if (name_index_pair_[i].first == index_name)
        {
            is_exist = true;
            book_pos = name_index_pair_[i].second;
            break;
        }
    }
    if (!is_exist)
    {
        std::cout << "null\n";
        return;
    }

    index_to_head t;
    if (!file.read(t, book_pos))
    {
        std::cout << "null\n";
        return;
    }

    bool is_empty = true;

    Block temp;

    book.read(temp, t.head);

    while (temp.next_block != -1)
    {
        if (temp.size != 0)
            is_empty = false;
        for (int i = 0; i < temp.size; i++)
        {
            std::cout << temp.val[i] << " ";
        }
        book.read(temp, temp.next_block);
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
// 查找索引
template<class T>
bool storage<T>::delete_val(Block &temp, T value, int block_index)
{
    T *pos = std::lower_bound(temp.val, temp.val + temp.size, value);
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
        temp.val[temp.size - 1] = T();
        --temp.size;
        book.update(temp, block_index);
    }
    return true;
}
// 删除值的具体操作
template<class T>
void storage<T>::merge(Block &block, int offset)
{
    Block next_block;
    book.read(next_block, block.next_block);
    int length = block.size + next_block.size;
    std::vector<T> storage;
    storage.resize(length);
    for (int i = 0; i < block.size; i++)
    {
        storage[i] = block.val[i];
    }
    for (int i = block.size; i < length; i++)
    {
        storage[i] = next_block.val[i - block.size];
    }
    for (int i = 0; i < 200; i++)
        block.val[i] = T();

    for (int i = 0; i < length; i++)
    {
        block.val[i] = storage[i];
    }
    block.next_block = next_block.next_block;
    block.size = length;
    book.update(block, offset);
}
// 合并块
template<class T>
void storage<T>::Delete(T value, std::vector<std::pair<std::string, int>> &name_index_pair_)
{
    index_to_head t;
    for (int i = 0; i < name_index_pair_.size(); i++)
    {
        if (name_index_pair_[i].first == index_name)
        {
            int book_pos = name_index_pair_[i].second;
            if (!file.read(t, book_pos))
                return;
            Block temp;

            if (!book.read(temp, t.head))
                return;
            int block_index = t.head;
            while (temp.next_block != -1)
            {
                if (!delete_val(temp, value, block_index))
                {
                    block_index = temp.next_block;
                    book.read(temp, temp.next_block);
                }
                else
                {
                    Block next;
                    while (temp.next_block != -1)
                    {

                        book.read(next, temp.next_block);
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
// 删除对应索引与值
