//
// Created by kozlov-an on 03.06.2021.
//

#include "Tests.h"
#include <random>
#include <string>
#include "Timer.h"

static int TEST_COUNT = 10;
static std::random_device rd;
static std::mt19937 gen(rd());

char GetRandomChar(){
    static std::uniform_int_distribution<> distrib(33, 126); // Все видимые символы из таблицы ASCII
    return static_cast<char>(distrib(gen));
}

std::string GetRandomIdentificator(int size){
    std::string str;
    str.reserve(size);
    for(int i = 0; i < size; i++)
    {
        str.push_back(GetRandomChar());
    }

    return str;
}

void GenerateDataFile(std::string_view filename, int count, int size)
{
    std::ofstream outfile;
    outfile.open(filename.data(), std::ostream::binary);

    for(int i = 0; i < count; i++) {
        outfile << GetRandomIdentificator(size) << std::endl;
    }
    outfile.close();
}

void GenerateData(Identifiers& data, int count, int size)
{
    for(int i = 0; i < count; i++)
        data.push_back(GetRandomIdentificator(size));
}

TestResult<double> TestInsert(const Identifiers& testData, std::vector<std::string>& mass, TreeAVL& testTree, HashTable<std::string>& table) {
    Timer timer;
    double timeM = 0.0;
    double timeT = 0.0;
    double timeH = 0.0;
    int count = 0;

    for (auto& key : testData) {
        {
            timer.Start();
            mass.push_back(key);
            timer.End();
            timeM += timer.GetDuration();
            mass.pop_back();
        }

        {
            timer.Start();
            testTree.Insert(key);
            timer.End();
            timeT += timer.GetDuration();
            testTree.Remove(key);
        }

        {
            timer.Start();
            table.Add(key);
            timer.End();
            timeH += timer.GetDuration();
            table.Remove(key);
        }
        ++count;
    }

    timeH /= count;
    timeT /= count;
    timeM /= count;

    return std::make_tuple(timeH, timeT, timeM);
}

TestResult<double> TestFind(const Identifiers& data) {
    std::vector<std::string> mass;
    HashTable<std::string> table;
    TreeAVL testTree;
    Timer timer;

    for (auto &key : data) {
        mass.push_back(key);
        testTree.Insert(key);
        table.Add(key);
    }

    double timeM = 0.0;
    double timeT = 0.0;
    double timeH = 0.0;

    // Замер скорости поиска
    std::uniform_int_distribution<size_t> distrib(0, data.size());
    for (int k = 0; k < TEST_COUNT; ++k) {
        auto randNum = distrib(gen);
        std::string key = (data.size() <= randNum) ? GetRandomIdentificator(randNum) : data[randNum];
        {
            timer.Start();
            for (auto &str : mass) {
                if (str == key)
                    break;
            }
            timer.End();
            timeM += timer.GetDuration();
        }

        {
            timer.Start();
            testTree.Find(key);
            timer.End();
            timeT += timer.GetDuration();
        }

        {
            timer.Start();
            table.Find(key);
            timer.End();
            timeH += timer.GetDuration();
        }
    }

    timeH /= TEST_COUNT;
    timeT /= TEST_COUNT;
    timeM /= TEST_COUNT;

    return std::make_tuple(timeH, timeT, timeM);
}

TestResult<int> TestMemory(const Identifiers& data){
    int sizeH = 0;
    int sizeT = 0;
    int sizeM = 0;

    std::vector<std::string> mass;
    HashTable<std::string> table;
    TreeAVL testTree;

    for (auto &key : data) {
        mass.push_back(key);
        testTree.Insert(key);
        table.Add(key);
    }

    int wordSize = mass[0].size();
    sizeM += sizeof(std::vector<std::string>) + mass.size() * (sizeof(std::string) +  sizeof(char) * wordSize);
    sizeH += table.GetMemorySize(wordSize);
    sizeT += testTree.GetMemorySize(wordSize);

    return std::make_tuple(sizeH, sizeT, sizeM);
}

Identifiers LoadFromFile(const std::string& fileName) {
    Identifiers identificators;
    std::string str;

    std::ifstream file(fileName);
    if(file.is_open()) {
        while (std::getline(file, str)) {
            identificators.push_back(str);
        }
    }

    return identificators;
}

