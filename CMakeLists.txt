cmake_minimum_required(VERSION 3.10)
project(BankingService)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add the executables i.e the files
include_directories(
${PROJECT_SOURCE_DIR}/include
${PROJECT_SOURCE_DIR}/src
)
file(GLOB all_SRCS
"${PROJECT_SOURCE_DIR}/include/*.h"
"${PROJECT_SOURCE_DIR}/include/*.hpp"
"${PROJECT_SOURCE_DIR}/src/*.cpp"
"${PROJECT_SOURCE_DIR}/src/*.c"
)
add_executable(${CMAKE_PROJECT_NAME} ${all_SRCS})

# USing MSVC compiler
if(MSVC)
    target_compile_options(BankingService PRIVATE /W4)
else()
    # For gcc/clang compilers
    target_compile_options(BankingService PRIVATE -Wall -Wextra)
endif()