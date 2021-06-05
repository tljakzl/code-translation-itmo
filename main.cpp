#include "Tests.h"

int main() {

  //  RunTest<double>("testFind_8.csv", TestFind, 8);
  //  RunTest<double>("testFind_32.csv", TestFind, 32);

    RunTest<double>("testInsert_8.csv", TestInsert, 8, 50, 1000);
    RunTest<double>("testInsert_32.csv", TestInsert, 32, 50, 1000);

    //RunTest<int>("testMemory_32.csv", TestMemory, 32);

    return 0;
}
