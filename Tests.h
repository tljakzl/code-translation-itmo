#pragma once

#include <string>
#include <vector>
#include <functional>
#include <fstream>

using Identifiers = std::vector<std::string>;

template <typename T>
using TestResult = std::tuple<T, T, T>;

template <typename T>
using TestFunction = std::function<TestResult<T>(const Identifiers& data)>;

template<typename T>
void RunTest(const std::string& logName, TestFunction<T> fun, int identificatorSize = 8, int step = 500, int testCount = 70) {
    std::ofstream outfile;
    outfile.open(logName, std::ostream::binary);

    char sp = ';';

    for (int k = 1; k < testCount; ++k) {
        auto dataSize = step * k;
        Identifiers data;
        GenerateData(data, dataSize, identificatorSize);

        auto[timeH, timeT, timeM] = fun(data);

        outfile << dataSize << sp;
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
TestResult<double> TestInsert(const Identifiers& data);
TestResult<int> TestMemory(const Identifiers& data);
void GenerateData(Identifiers& data, int count, int size);
void GenerateDataFile(std::string_view filename, int count, int size);
Identifiers LoadFromFile(const std::string& fileName);