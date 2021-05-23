#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include "Hash.h"
#include "HashTable.h"
#include "TreeAVL.h"

static const int IDENTIFICATOR_COUNT = 100;
static const int IDENTIFICATOR_SIZE = 20;
static const char* DATA_FILENAME = "data.txt";

char getRandomChar()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(33, 126); // Все видимые символы из таблицы ASCII

    return static_cast<char>(distrib(gen));
}

std::string GetRandomIdentificator(int size)
{
    std::string str;
    str.reserve(size);
    for(int i = 0; i < size; i++)
    {
        str.push_back(getRandomChar());
    }

    return str;
}

void GenerateDataFile(std::string_view filename, int identificatorCount, int identificatorSize)
{
    std::ofstream outfile;
    outfile.open(filename.data(), std::ostream::binary);

    for(int i = 0; i < identificatorCount; i++) {
        outfile << GetRandomIdentificator(identificatorSize) << std::endl;
    }
    outfile.close();
}

int main() {
    std::ifstream file;
    file.open(DATA_FILENAME);

    if(!file.is_open())
    {
        GenerateDataFile(DATA_FILENAME,IDENTIFICATOR_COUNT, IDENTIFICATOR_SIZE);
        file.close();
        file.open(DATA_FILENAME);
    }

    HashTable<std::string> table;
    std::string str;

    while (std::getline(file, str))
    {
        table.Add(str);
    }

    std::cout << table.Find("Kg%ka=y$r7IBRyE(Jx@f");

    TreeAVL testTree;
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");
    testTree.Insert("Kg%ka=y$r7IBRyE(Jx@f");


    return 0;
}
