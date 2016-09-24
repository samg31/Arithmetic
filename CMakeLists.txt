CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(aprecision)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_EXECUTABLE(aprecision ../src/main.cpp ../src/number.cpp )
