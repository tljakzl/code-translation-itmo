#include "Hash.h"

int HashImpl(const std::string& str, int tableSize, int key)
{
    int hash_result = 0;
    for (char s : str)
        hash_result = (hash_result + key + (int)s) % tableSize;

    return hash_result;
}

int HashTwo::operator()(const std::string &str, int tableSize) const {
    int hash_result = 0;
    for (char s : str)
        hash_result = (hash_result + (int)s) % (tableSize - 1) + 1;

    return hash_result;
}

int HashOne::operator()(const std::string &str, int tableSize) const {
    return HashImpl(str, tableSize, tableSize);
}

unsigned long Hash_djb2(const std::string &str) {

    unsigned long hash = 5381;
    for (char c : str)
        hash = ((hash << 5) + hash) + (int) c; /* hash * 33 + c */

    return hash;
}
