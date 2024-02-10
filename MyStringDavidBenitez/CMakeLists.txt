cmake_minimum_required(VERSION 3.15)

project(
MyString_Class
VERSION 0.0.1
LANGUAGES CXX)

set(PROJECT_HEADERS 
    include/MyString.h
    include/argparse.h
    include/AutoTest.h
)

set(PROJECT_SOURCES 
    src/MyString.cpp
    src/StringTest.cpp
    src/AutoTest.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})