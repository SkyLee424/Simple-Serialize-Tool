/**
 * @file CustomClass.h
 * @brief 用于演示自定义类型应该如何操作才能正确序列化
 * @date 2023-08-27
 *
 */

#pragma once

#include <string>
#include "Serializable.hpp"

class People : public Serializable // 继承 Serializable 类
{
public:
    std::string name;
    int age;
    std::string BinZhou;

    People() = default; // 注意：自定义类型必须要有默认构造函数

    People(const std::string &name, int age, const std::string &BinZhou)
        : name(name), age(age), BinZhou(BinZhou) {}

    bool operator<(const People &p) const
    {
        return this->age < p.age;
    }

    static std::ostream &Serialize(std::ostream &os, const People &people) // 重写基类的 Serialize 方法
    {
        Serializable::Serialize(os, people.name); // 直接使用 Serializable::Serialize 方法即可
        Serializable::Serialize(os, people.age);
        Serializable::Serialize(os, people.BinZhou);
        return os;
    }

    static std::istream &DeSerialize(std::istream &is, People &people) // 重写基类的 DeSerialize 方法
    {
        Serializable::DeSerialize(is, people.name); // 注意反序列化的顺序
        Serializable::DeSerialize(is, people.age);
        Serializable::DeSerialize(is, people.BinZhou);
        return is;
    }
};