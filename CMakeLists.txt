cmake_minimum_required(VERSION 3.16)

project(MyProject LANGUAGES CXX)

# Pouzita verze C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Hlavni program
add_executable(MyProject
    src/main.cpp
    src/SysTickHandler.cpp
    src/Timer.cpp
)

# Adresar s hlavickovymi soubory
target_include_directories(MyProject PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

# Parametry prekladace
target_compile_options(MyProject PRIVATE
    -Wall
    -Wextra
)
