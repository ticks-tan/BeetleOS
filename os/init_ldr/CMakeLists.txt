cmake_minimum_required(VERSION 3.20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/_build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_build/bin)

set(CMAKE_ASM_NASM_FLAGS "-g -I${PROJECT_SOURCE_DIR}/init_ldr/include/")
# set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

list(APPEND SOURCE_ASM16_FILES
        src/real_int_save.asm
        )
list(APPEND SOURCE_ASM32_FILES
        src/init_img_head.asm
        src/init_ldr_entry.asm
        )

include_directories(include)

set_source_files_properties(${SOURCE_ASM16_FILES} PROPERTIES COMPILE_FLAGS "-e_start -f elf32")
set_source_files_properties(${SOURCE_ASM32_FILES} PROPERTIES COMPILE_FLAGS "-e_start -f elf32")

add_library(img_init_header
        OBJECT
        src/init_img_head.asm
        src/init_head.cc
        src/vgastr.cc
        )
add_library(init_int_save
        OBJECT
        src/real_int_save.asm
        )

add_library(init_ldr_kernel
        OBJECT
        src/init_ldr_entry.asm
        src/ldr_entry.cc
        src/ldr_type.cc
        src/mach_start_param.cc
        src/graph.cc
        src/check_cpu.cc
        src/vgastr.cc
        )

