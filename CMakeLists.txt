cmake_minimum_required(VERSION 3.20)
project(tictactoe VERSION 1.0 LANGUAGES CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(backend)
add_subdirectory(cli)
