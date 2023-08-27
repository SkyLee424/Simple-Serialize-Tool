#include <iostream>
#include <vector>
#include "Serializer.hpp"
#include "Serializable.hpp"
#include "CustomClass.h"

template <typename T>
bool test(T &val)
{
    std::string t0 = Serializer::Serialize(val);
    auto after = Serializer::Deserialize<T>(t0);
    std::string t1 = Serializer::Serialize(after);
    if (t0 == t1)
        return true;
    std::cout << "t0: " << t0 << std::endl;
    std::cout << "t1: " << t1 << std::endl;
    return false;
}

// 特例化无序容器的检测方式
template <typename T>
bool test(std::unordered_set<T> &val)
{
    std::string t0 = Serializer::Serialize(val);
    auto after = Serializer::Deserialize<std::unordered_set<T>>(t0);
    std::string t1 = Serializer::Serialize(after);
    auto end = Serializer::Deserialize<std::unordered_set<T>>(t1);
    return val == end;
}

// 特例化无序容器的检测方式
template <typename K, typename V>
bool test(std::unordered_map<K, V> &val)
{
    std::string t0 = Serializer::Serialize(val);
    auto after = Serializer::Deserialize<std::unordered_map<K, V>>(t0);
    std::string t1 = Serializer::Serialize(after);
    auto end = Serializer::Deserialize<std::unordered_map<K, V>>(t1);
    return val == end;
}

template <typename T>
void judge(T &val)
{
    if (test(val))
        std::cout << "Pass" << std::endl;
    else
        std::cout << "Failed" << std::endl;
}

// 一个帮助插入的函数
template <typename T, typename E>
void helper(T &val, const E &elem)
{
    for (size_t i = 0; i < 4; i++)
    {
        val.insert(elem);
    }
}

int main(void)
{
    std::list<int> nums = {1, 2, 3, 4};
    std::list<std::string> strings = {"1", "2 3", "4 5\n\n", "6 ", " 7"};
    
    std::vector<std::vector<int>> grid = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
    std::vector<std::list<std::string>> grid1 = {{"1", "2 3", "4 5\n\n", "6 ", " 7"}, {"1", "2 3", "4 5\n\n", "6 ", " 7"}, {"1", "2 3", "4 5\n\n", "6 ", " 7"}};

    std::stack<int> s;
    s.push(1);s.push(2);s.push(3);
    std::stack<std::string> s1;
    s1.push("1"); s1.push(" 2 3"); s1.push(" 4 \n\n 5");

    std::queue<int> q;
    s.push(1);s.push(2);s.push(3);
    std::queue<std::string> q1;
    s1.push("1"); s1.push(" 2 3"); s1.push(" 4 \n\n 5");
    
    std::set<int> dic = {1, 2, 3, 4};
    std::set<std::string> dic1 = {"1", "2 3", "4 5\n\n", "6 ", " 7"};
    std::set<std::vector<std::string>> dic2 = {{"1", "2 3", "4 5\n\n", "6 ", " 7"}, {"1", "2 3", "4 5\n\n", "6 ", " 7"}, {"1", "2 3", "4 5\n\n", "6 ", " 7"}};;

    std::unordered_set<int> u_dic = {1, 2, 3, 4};
    std::unordered_set<std::string> u_dic1 = {"1", "2 3", "4 5\n\n", "6 ", " 7"};
    
    std::pair<int, std::string> p = {1, "66 77 \n\n  88 99"};
    std::pair<std::string, std::vector<int>> p1 = {"12\n 34 56", {1, 2, 3, 4}};
    std::pair<std::string, std::vector<std::string>> p2 = {"12\n 34 56", {"1", "2 3", "4 5\n\n", "6 ", " 7"}};
    std::pair<std::string, std::pair<std::string, std::string>> p3 = {"12\n 34 56", {"12\n 34 56", "12\n 34 56"}};
    
    std::map<int, std::string> map;
    std::map<std::string, std::vector<int>> map1;
    std::map<std::string, std::vector<std::string>> map2;
    std::map<int, std::map<int, std::string>> map3;
    helper(map, p);
    helper(map1, p1);
    helper(map2, p2);
    helper(map3, std::make_pair(1, map));

    std::unordered_map<int, std::string> hashMap;
    std::unordered_map<std::string, std::vector<int>> hashMap1;
    std::unordered_map<std::string, std::vector<std::string>> hashMap2;
    std::unordered_map<int, std::unordered_map<int, std::string>> hashMap3;
    helper(hashMap, p);
    helper(hashMap1, p1);
    helper(hashMap2, p2);
    helper(hashMap3, std::make_pair(1, hashMap));

    People HeXin;
    HeXin.name = "HeXin";
    HeXin.age = 19;
    HeXin.BinZhou = "0.618 cm";

    std::vector<People> peoples;
    peoples.push_back(HeXin);
    peoples.push_back(HeXin);
    peoples.push_back(HeXin);

    std::priority_queue<int> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);

    std::priority_queue<People, std::vector<People>> pq1;
    pq1.push(HeXin);
    pq1.push(HeXin);
    pq1.push(HeXin);


/*---------------------------Test--------------------------------*/
    
    judge(nums);
    judge(strings);
    
    judge(grid);
    judge(grid1);

    judge(s);
    judge(s1);

    judge(q);
    judge(q1);
    
    judge(dic);
    judge(dic1);
    judge(dic2);

    judge(u_dic);
    judge(u_dic1);

    judge(p);
    judge(p1);
    judge(p2);
    judge(p3);

    judge(map);
    judge(map1);
    judge(map2);
    judge(map3);

    judge(hashMap);
    judge(hashMap1);
    judge(hashMap2);
    judge(hashMap3);

    judge(HeXin);
    judge(peoples);

    judge(pq);
    judge(pq1);
}
