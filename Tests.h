#pragma once

#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include "HashTable.h"
#include "TreeAVL.h"

using Identifiers = std::vector<std::string>;

template <typename T>
using TestResult = std::tuple<T, T, T>;

template <typename T>
using TestFunction = std::function<TestResult<T>(const Identifiers& data, std::vector<std::string>& mass, TreeAVL& testTree, HashTable<std::string>& table)>;

template<typename T>
void RunTest(const std::string& logName, TestFunction<T> fun, int identificatorSize = 8, int step = 500, int testCount = 70, int testDataSize = 1'000) {
    std::ofstream outfile;
    outfile.open(logName, std::ostream::binary);

    std::vector<std::string> mass;
    TreeAVL testTree;
    HashTable<std::string> table;

    char sp = ';';

    for (int k = 1; k < testCount; ++k) {

        Identifiers newData;
        GenerateData(newData, step, identificatorSize);

        for (auto &key : newData) {
            mass.push_back(key);
            testTree.Insert(key);
            table.Add(key);
        }

        Identifiers testData;
        GenerateData(testData, testDataSize, identificatorSize);

        auto[timeH, timeT, timeM] = fun(testData, mass, testTree, table);

        outfile << step*k << sp;
        outfile << timeH << sp;
        outfile << timeT << sp;
        outfile << timeM << sp;
        outfile << std::endl;
    }
    outfile.close();
}

char GetRandomChar();
std::string GetRandomIdentificator(int size);
TestResult<double> TestFind(const Identifiers& data);
TestResult<double> TestInsert(const Identifiers& data, std::vector<std::string>& mass, TreeAVL& testTree, HashTable<std::string>& table);
TestResult<int> TestMemory(const Identifiers& data);
void GenerateData(Identifiers& data, int count, int size);
void GenerateDataFile(std::string_view filename, int count, int size);
Identifiers LoadFromFile(const std::string& fileName);