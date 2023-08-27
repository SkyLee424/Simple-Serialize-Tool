#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include "Serializable.hpp"

/**
 * @brief 简单的序列化与反序列化工具，可以实现任意对象的序列化和反序列化过程，但该对象必须重载 << 和 >> 运算符
 *
 */
class Serializer
{
public:
    template <typename T>
    static std::string Serialize(T &&object)
    {
        std::ostringstream os;
        Serializable::Serialize(os, object);
        return os.str();
    }

    template <typename T>
    static T
    Deserialize(const std::string &serializedData)
    {
        std::istringstream is(serializedData);
        T object;
        Serializable::DeSerialize(is, object);
        return object;
    }
};

