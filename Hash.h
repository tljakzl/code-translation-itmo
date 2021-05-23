#pragma once

#include <vector>
#include <string>

struct HashOne{
    int operator()(const std::string& str, int tableSize) const;
};

struct HashTwo{
    int operator()(const std::string& str, int tableSize) const;
};

unsigned long Hash_djb2(const std::string& str);
