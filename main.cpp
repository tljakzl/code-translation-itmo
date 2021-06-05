#include "Tests.h"

int main() {

    int word8 = 8;
    int word32 = 8;
    int step = 50;
    int maxSizeData = 500;

    RunTest<double>("testFind_8.csv", TestFind, word8, step, maxSizeData, step);
    RunTest<double>("testFind_32.csv", TestFind, word32, step, maxSizeData, step);

    RunTest<double>("testInsert_8.csv", TestInsert, word8, step, maxSizeData);
    RunTest<double>("testInsert_32.csv", TestInsert, word32, step, maxSizeData);

    RunTest<int>("testMemory_32.csv", TestMemory, 32);

    return 0;
}
