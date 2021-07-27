cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Sensors)

set(SRC_LIST
    src/main.cpp
    src/MainNode.cpp
    src/Sensor.cpp
    src/CircBuffer.cpp
    src/RandomMeasGenerator.cpp
    src/Logger.cpp
)

include_directories(src)
include_directories(inc)
add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif (UNIX)

