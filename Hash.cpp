#include "Hash.h"

int HashImpl(const std::string& str, int tableSize, const int key)
{
    int hash_result = 0;
    for (auto s : str)
    {
        hash_result = (key * hash_result + static_cast<int>(s)) % tableSize;
    }
    hash_result = (hash_result * 2 + 1) % tableSize;
    return hash_result;
}

int HashTwo::operator()(const std::string &str, int tableSize) const {
    return HashImpl(str, tableSize, tableSize + 1);
}

int HashOne::operator()(const std::string &str, int tableSize) const {
    return HashImpl(str, tableSize, tableSize - 1);
}

unsigned long Hash_djb2(const std::string &str) {

    unsigned long hash = 5381;
    for (char c : str)
        hash = ((hash << 5) + hash) + (int) c; /* hash * 33 + c */

    return hash;
}
