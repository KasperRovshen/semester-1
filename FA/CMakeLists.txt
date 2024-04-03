cmake_minimum_required(VERSION 3.8)

project(FaaT LANGUAGES CXX)

file(GLOB SOURCES
    h/*.h
    src/*.cpp)

add_executable(FA ${SOURCES})