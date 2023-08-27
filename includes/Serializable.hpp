#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <memory>

class Serializable;

// 辅助模板，用于检查对象是否继承自 Serializable
// 使用到了 SFINAE 技术
template <typename T>
struct is_serializable
{
    static constexpr bool value = std::is_base_of_v<Serializable, T>;
};

class Serializable
{
public:
    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const T &val);
    
    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, T &val);

    static
    std::ostream& Serialize(std::ostream &os, const std::string &val);

    static
    std::istream& DeSerialize(std::istream &is, std::string &val);

    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const std::vector<T> &val);

    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, std::vector<T> &val);

    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const std::list<T> &val);

    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, std::list<T> &val);

    template <typename T, std::size_t N>
    static
    std::ostream& Serialize(std::ostream &os, const std::array<T, N> &val);

    template <typename T, std::size_t N>
    static
    std::istream& DeSerialize(std::istream &is, std::array<T, N> &val);

    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const std::stack<T> &val);

    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, std::stack<T> &val);

    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const std::queue<T> &val);

    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, std::queue<T> &val);

    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const std::set<T> &val);

    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, std::set<T> &val);

    template <typename T>
    static
    std::ostream& Serialize(std::ostream &os, const std::unordered_set<T> &val);

    template <typename T>
    static
    std::istream& DeSerialize(std::istream &is, std::unordered_set<T> &val);

    template <typename K, typename V>
    static
    std::ostream& Serialize(std::ostream &os, const std::pair<K, V> &val);

    template <typename K, typename V>
    static
    std::istream& DeSerialize(std::istream &is, std::pair<K, V> &val);

    template <typename K, typename V>
    static
    std::ostream& Serialize(std::ostream &os, const std::map<K, V> &val);

    template <typename K, typename V>
    static
    std::istream& DeSerialize(std::istream &is, std::map<K, V> &val);

    template <typename K, typename V>
    static
    std::ostream& Serialize(std::ostream &os, const std::unordered_map<K, V> &val);

    template <typename K, typename V>
    static
    std::istream& DeSerialize(std::istream &is, std::unordered_map<K, V> &val);

    template <typename Tp, typename Sequence, typename Compare>
    static
    std::ostream& Serialize(std::ostream &os, const std::priority_queue<Tp, Sequence, Compare> &val);

    template <typename Tp, typename Sequence, typename Compare>
    static
    std::istream& DeSerialize(std::istream &is, std::priority_queue<Tp, Sequence, Compare> &val);
};

// 大部分容器都可以使用该序列化方式
template <typename T>
std::ostream& helper(std::ostream &os, const T &val);

// 基本类型，以及自定义类型
template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const T &val)
{
    if constexpr (is_serializable<T>::value) // 如果对象继承自 Serializable，就使用自己的序列化方法
        return T::Serialize(os, val);
    else os << val << " ";                   // 否则，使用 Serializable 提供的方法
    return os;
}
    
template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, T &val)
{
    if constexpr (is_serializable<T>::value)
        return T::DeSerialize(is, val);
    else 
    {
        is >> val;
        is.seekg(1, std::ios::cur);
    }
    return is;
}

// 字符串
std::ostream& Serializable::Serialize(std::ostream &os, const std::string &val)
{
    os << val.size() << " " << val << " ";
    return os;
}

std::istream& Serializable::DeSerialize(std::istream &is, std::string &val)
{
    size_t len;
    is >> len;
    is.seekg(1, std::ios::cur); // 跳过空格
    char *buffer = new char[len + 1];
    is.read(buffer, len);
    buffer[len] = '\0';
    val = buffer;
    delete []buffer;
    return is;
}

// 容器
template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const std::vector<T> &val)
{
    return helper(os, val);
}

template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, std::vector<T> &val)
{
    size_t size;
    Serializable::DeSerialize(is, size);
    val.resize(size);
    for(size_t i = 0; i < size; ++i)
    {
        Serializable::DeSerialize(is, val[i]);
    }
    return is;
}

template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const std::list<T> &val)
{
    return helper(os, val);
}

template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, std::list<T> &val)
{
    size_t size;
    Serializable::DeSerialize(is, size);
    T temp; // 需要默认构造函数
    for(size_t i = 0; i < size; ++i)
    {
        Serializable::DeSerialize(is, temp);
        val.push_back(temp);
    }
    return is;
}

template <typename T, std::size_t N>
std::ostream& Serializable::Serialize(std::ostream &os, const std::array<T, N> &val)
{
    for(const auto &elem : val)
        Serializable::Serialize(os, elem);
    return os;
}

template <typename T, std::size_t N>
std::istream& Serializable::DeSerialize(std::istream &is, std::array<T, N> &val)
{
    for (size_t i = 0; i < N; i++)
    {
        Serializable::DeSerialize(is, val[i]);
    }
    return is;
}

template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const std::stack<T> &val)
{
    size_t size = val.size();
    Serializable::Serialize(os, size);
    auto copy = val;
    while (!copy.empty())
    {
        Serializable::Serialize(os, copy.top());
        copy.pop();
    }
    return os;
}

template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, std::stack<T> &val)
{
    std::vector<T> temp;
    Serializable::DeSerialize(is, temp);
    for(auto rbeg = temp.rbegin(); rbeg != temp.rend(); ++rbeg)
    {
        val.push(*rbeg);
    }
    return is;
}

template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const std::queue<T> &val)
{
    size_t size = val.size();
    Serializable::Serialize(os, size);
    auto copy = val;
    while (!copy.empty())
    {
        Serializable::Serialize(os, copy.front());
        copy.pop();
    }
    return os;
}

template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, std::queue<T> &val)
{
    size_t size;
    Serializable::DeSerialize(is, size);
    T elem;
    while (size--)
    {
        Serializable::DeSerialize(is, elem);
        val.push(elem);
    }
    
    return is;
}

template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const std::set<T> &val)
{
    return helper(os, val);
}

template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, std::set<T> &val)
{
    size_t size;
    Serializable::DeSerialize(is, size);
    T temp;
    for(size_t i = 0; i < size; ++i)
    {
        Serializable::DeSerialize(is, temp);
        val.insert(temp);
    }
    return is;
}

template <typename T>
std::ostream& Serializable::Serialize(std::ostream &os, const std::unordered_set<T> &val)
{
    return helper(os, val);
}

template <typename T>
std::istream& Serializable::DeSerialize(std::istream &is, std::unordered_set<T> &val)
{
    size_t size;
    Serializable::DeSerialize(is, size);
    T temp;
    for(size_t i = 0; i < size; ++i)
    {
        Serializable::DeSerialize(is, temp);
        val.insert(temp);
    }
    return is;
}

template <typename K, typename V>
std::ostream& Serializable::Serialize(std::ostream &os, const std::pair<K, V> &val)
{
    Serializable::Serialize(os, val.first);
    Serializable::Serialize(os, val.second);
    return os;
}

template <typename K, typename V>
std::istream& Serializable::DeSerialize(std::istream &is, std::pair<K, V> &val)
{
    Serializable::DeSerialize(is, val.first);
    Serializable::DeSerialize(is, val.second);
    return is;
}

template <typename K, typename V>
std::ostream& Serializable::Serialize(std::ostream &os, const std::map<K, V> &val)
{
    return helper(os, val);
}

template <typename K, typename V>
std::istream& Serializable::DeSerialize(std::istream &is, std::map<K, V> &val)
{
    size_t size;
    std::pair<K, V> p;

    Serializable::DeSerialize(is, size);
    for (size_t i = 0; i < size; ++i)
    {
        Serializable::DeSerialize(is, p);
        val.insert(p);
    }

    return is;
}

template <typename K, typename V>
std::ostream& Serializable::Serialize(std::ostream &os, const std::unordered_map<K, V> &val)
{
    return helper(os, val);
}

template <typename K, typename V>
std::istream& Serializable::DeSerialize(std::istream &is, std::unordered_map<K, V> &val)
{
    size_t size;
    std::pair<K, V> p;

    Serializable::DeSerialize(is, size);
    for (size_t i = 0; i < size; ++i)
    {
        Serializable::DeSerialize(is, p);
        val.insert(p);
    }

    return is;
}

template <typename Tp, typename Sequence, typename Compare>
std::ostream& Serializable::Serialize(std::ostream &os, const std::priority_queue<Tp, Sequence, Compare> &val)
{
    size_t size = val.size();
    Serializable::Serialize(os, size);
    auto copy = val;
    while (!copy.empty())
    {
        auto elem = copy.top();
        Serializable::Serialize(os, elem);
        copy.pop();
    }
    return os;
    
}

template <typename Tp, typename Sequence, typename Compare>
std::istream& Serializable::DeSerialize(std::istream &is, std::priority_queue<Tp, Sequence, Compare> &val)
{
    size_t size;
    Serializable::DeSerialize(is, size);
    typename std::priority_queue<Tp, Sequence, Compare>::value_type elem;
    while (size--)
    {
        Serializable::DeSerialize(is, elem);
        val.push(elem);
    }
    return is;
}

template <typename T>
std::ostream& helper(std::ostream &os, const T &val)
{
    size_t size = val.size();
    Serializable::Serialize(os, size);
    for(const auto &elem : val)
    {
        Serializable::Serialize(os, elem);
    }
    return os;
}