#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <chrono>
#include "Hash.h"
#include "HashTable.h"
#include "TreeAVL.h"

static const int IDENTIFICATOR_COUNT = 100;
static const int IDENTIFICATOR_SIZE = 16;
static const char* DATA_FILENAME = "data.txt";
static int TEST_COUNT = 10;

using Identifiers = std::vector<std::string>;
static std::random_device rd;
static std::mt19937 gen(rd());

char getRandomChar()
{
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

void GenerateData(Identifiers& data, int identificatorCount, int identificatorSize)
{
    for(int i = 0; i < identificatorCount; i++)
        data.push_back(GetRandomIdentificator(identificatorSize));
}

class Timer{

public:
    void Start(){
        _t1 = std::chrono::high_resolution_clock::now();
    }
    void End(){
        _t2 = std::chrono::high_resolution_clock::now();
    }
    double GetDuration(){
        const std::chrono::duration<double, std::milli> ms = _t2 - _t1;
        return ms.count();
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> _t1;
    std::chrono::time_point<std::chrono::steady_clock> _t2;
};

void TestInsert(double& timeH, double& timeT, double& timeM, const Identifiers& data) {
    std::vector<std::string> mass;
    HashTable<std::string> table;
    TreeAVL testTree;
    Timer timer1;

    // Замер скорости вставки
    {
        timer1.Start();
        for (auto &key : data) {
            mass.push_back(key);
        }
        timer1.End();
        timeM = timer1.GetDuration();
    }

    {
        timer1.Start();
        for (auto &key : data) {
            testTree.Insert(key);
        }
        timer1.End();
        timeT = timer1.GetDuration();
    }

    {
        timer1.Start();
        for (auto &key : data) {
            table.Add(key);
        }
        timer1.End();
        timeH = timer1.GetDuration();
    }

    // Замер скорости поиска
    std::uniform_int_distribution<size_t> distrib(0, data.size());
    auto randNum = distrib(gen);
    std::string key = data.empty() ? std::string() : data[randNum];
    {
        timer1.Start();
        for(auto& str : mass)
        {
            if(str == key)
                break;
        }
        timer1.End();
        timeM = timer1.GetDuration();
    }

    {
        timer1.Start();
        testTree.Find(key);
        timer1.End();
        timeT = timer1.GetDuration();
    }

    {
        timer1.Start();
        table.Find(key);
        timer1.End();
        timeH = timer1.GetDuration();
    }
}

void TestFind(double& timeH, double& timeT, double& timeM, const Identifiers& data) {
    std::vector<std::string> mass;
    HashTable<std::string> table;
    TreeAVL testTree;
    Timer timer;

    for (auto &key : data) {
        mass.push_back(key);
        testTree.Insert(key);
        table.Add(key);
    }

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
}

int main() {
    std::ifstream file;
    file.open(DATA_FILENAME);

    if (!file.is_open()) {
        GenerateDataFile(DATA_FILENAME, IDENTIFICATOR_COUNT, IDENTIFICATOR_SIZE);
        file.close();
        file.open(DATA_FILENAME);
    }

    /*std::vector<std::string> identificators;
    std::string str;

    while (std::getline(file, str)) {
        identificators.push_back(str);
    }*/

    std::ofstream outfile;
    outfile.open("log.cvs", std::ostream::binary);
    char sp = ';';

    for (int k = 0; k < 70; ++k) {

        double timeH = 0;
        double timeM = 0;
        double timeT = 0;
        auto dataSize = 500*k;
        Identifiers data;
        GenerateData(data, dataSize, IDENTIFICATOR_SIZE);

        for (int k = 0; k < 1; ++k) {
            double timeCurrentH = 0;
            double timeCurrentM = 0;
            double timeCurrentT = 0;
            TestFind(timeCurrentH, timeCurrentT, timeCurrentM, data);

            timeH += timeCurrentH;
            timeT += timeCurrentT;
            timeM += timeCurrentM;
        }

        timeH /= 1;
        timeT /= 1;
        timeM /= 1;

        outfile << dataSize << sp;
        outfile << timeH << sp;
        outfile << timeT << sp;
        outfile << timeM << sp;
        outfile << std::endl;
    }

    outfile.close();
    return 0;
}
