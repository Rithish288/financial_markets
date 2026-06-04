cmake_minimum_required(VERSION 4.0)
project(financial_markets)

set(CMAKE_CXX_STANDARD 20)

add_executable(financial_markets main.cpp
        order_book.cpp
        order_book.h)
