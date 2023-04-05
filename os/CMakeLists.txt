cmake_minimum_required(VERSION 3.14)

project(BeetleOS VERSION 0.1 LANGUAGES ASM_NASM CXX)


include_directories(
        ${PROJECT_SOURCE_DIR}/base/include
)

add_subdirectory(init_ldr)