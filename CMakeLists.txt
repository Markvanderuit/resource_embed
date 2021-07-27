cmake_minimum_required(VERSION 3.16)

project(StringEmbed LANGUAGES CXX)

add_library(LibStringEmbed INTERFACE)
target_include_directories(LibStringEmbed INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(ExecStringEmbed ${CMAKE_CURRENT_SOURCE_DIR}/src/string_embed.cpp)
target_compile_features(ExecStringEmbed PUBLIC cxx_std_17)
