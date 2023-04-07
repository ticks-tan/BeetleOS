cmake_minimum_required(VERSION 3.20)

project(BeetleOS VERSION 0.1 LANGUAGES ASM_NASM CXX)
enable_language(ASM_NASM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(
        ${PROJECT_SOURCE_DIR}/base/include
)

add_subdirectory(init_ldr)