cmake_minimum_required(VERSION 3.1)

project(OOP LANGUAGES CXX)

file(GLOB SOURCES
    h/*.h
    src/*.cpp)

add_executable(OOP ${SOURCES})