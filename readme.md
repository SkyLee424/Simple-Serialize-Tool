# 简单的序列化工具

该序列化工具使用方便，支持基本数据类型、常用 STL 容器、自定义类型

## 基本组件

序列化工具由两大组件组成：

- **Serializer.hpp**：序列化工具类，提供两个方法： `Serialize` 和 `Deserialize`
- **Serializable.hpp**：接口类，为基本数据类型和常用 STL 容器的序列化提供支持，自定义类型也可以重写 `Serialize` 和 `DeSerialize` 方法，以实现自己的序列化

## 使用到的技术

- 模版元编程
- SFINAE

## 基本使用

```cpp
template <typename T>
T example(T &object)
{
    std::string s = Serializer::Serialize(object); // 将 object 序列化为字符串
    T after = Serializer::Deserialize<T>(s);       // 将 s 反序列化成一个 int 型的数据，注意：需要指定反序列化后的类型

    return after;
}
```

- 通过调用 `Serializer::Serialize` 静态方法，将任意 object 序列化为字符串
- 通过调用 `Serializer::Deserialize` 静态方法，将字符串反序列化为对应的 object

序列化得到的字符串可以方便的传输

## 注意事项

- 自定义数据类型需要继承 Serializable 类，并重写基类的两个方法
- 不支持字符串常量，如果要序列化字符串常量，请使用 `std::string`

    例如：

    ```cpp
    std::string temp = Serializer::Serialize<std::string>("114514"); // 建议使用 string
    ```

- 不支持内置数组类型，建议使用 `std::vector` 或者 `std::array`
- 不支持指针（包括智能指针）