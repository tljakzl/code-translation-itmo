cmake_minimum_required(VERSION 3.19)
project(code_translation_itmo)

set(CMAKE_CXX_STANDARD 17)

add_executable(code_translation_itmo main.cpp Hash.cpp Hash.h TreeAVL.cpp TreeAVL.h HashTable.cpp HashTable.h Timer.cpp Timer.h Tests.cpp Tests.h)