#include <iostream>
#include <memory>
#include "Serializer.hpp"
#include "Serializable.hpp"
#include "CustomClass.h"

template <typename T>
T example(T &object)
{
    std::string s = Serializer::Serialize(object); // 将 object 序列化为字符串
    T after = Serializer::Deserialize<T>(s);       // 将 s 反序列化成一个 int 型的数据，注意：需要指定反序列化后的类型

    return after;
}

int main(void)
{
    // example 0: 基本数据类型
    int i = 114514;
    int after = example(i);
    std::cout << after << std::endl;

    // example 1: 字符串
    std::string s = "114514";
    std::string after1 = example(s);
    std::cout << after1 << std::endl;

    // example 2: 容器
    std::vector<std::string> vec = {"114 ", " 514"};
    auto after2 = example(vec);
    for (const auto &elem : after2)
        std::cout << elem << " ";
    std::cout << std::endl;

    // example 3: 自定义类型
    // 需要继承 Serializable 类，实现基类的 Serialize 和 DeSerialize 方法
    People people("He Xin", 19, "0.618 cm");
    auto after3 = example(people);
    std::cout << "name: " << after3.name << ", age: " << after3.age << ", BinZhou: " << after3.BinZhou << std::endl;

    /*-------------------------------------------------错误示例-------------------------------------------------------------*/

    auto temp = Serializer::Serialize("114514");         // 错误，不支持 const char*
    temp = Serializer::Serialize<std::string>("114514"); // 建议使用 string

    int arr[] = {1, 2, 3, 4};
    temp = Serializer::Serialize(arr);                            // 错误，不支持数组
    temp = Serializer::Serialize<std::vector<int>>({1, 2, 3, 4}); // 建议使用 vector 或者 std::array

    std::array<int, 4> arr1 = {1, 2, 3, 4};
    auto after4 = example(arr1); // 正确，使用 std::array<int, 4>
    for (const auto &elem : after4)
        std::cout << elem << " ";
    std::cout << std::endl;

    int *p = new int(114514);
    temp = Serializer::Serialize(p); // 错误，不支持指针类型
}