#include <iostream>
#include <random>
#include <string>
#include <fstream>


static const int IDENTIFICATOR_COUNT = 100;
static const int IDENTIFICATOR_SIZE = 20;

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

    GenerateDataFile("data.txt",IDENTIFICATOR_COUNT, IDENTIFICATOR_SIZE);
    return 0;
}
