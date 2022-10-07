#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef std::pair<int, int> Date;

struct Date_Hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

#endif