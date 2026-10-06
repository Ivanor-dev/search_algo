cmake_minimum_required(VERSION 3.10)
project(aps2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Sem tipo de build definido, usa Release (-O2/-O3): essencial para medir tempo
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Tipo de build" FORCE)
endif()

add_executable(aps2
    main.c
    insertion_sort.c
    selection_sort.c
    quick_sort.c
    merge_sort.c
)

target_include_directories(aps2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(aps2 PRIVATE -Wall -Wextra)
endif()