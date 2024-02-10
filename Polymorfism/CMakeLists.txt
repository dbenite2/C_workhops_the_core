cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

project(
DavidBenitezPolimorfism
VERSION 0.0.1
LANGUAGES CXX)

set(PROJECT_HEADERS 
    include/Circle.h
    include/Shape.h
    include/IJSONSerializer.h
    include/JSONBuilder.h
    include/Point2D.h
    include/Square.h
    include/Triangle.h
    include/Singleton.h
)

set(PROJECT_SOURCES 
    src/Circle.cpp
    src/Shape.cpp
    src/JSONBuilder.cpp
    src/Square.cpp
    src/Triangle.cpp
    src/Main.cpp
    src/Singleton.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})