cmake_minimum_required(VERSION 3.10)
project(BankingService)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executables i.e the files
add_executable(BankingService
    main.cpp
    Bank.cpp
    Bank.h
    Chatbot.cpp
    Chatbot.h
    Transaction.cpp
    Transaction.h
    UserAccount.cpp
    UserAccount.h
)

# Create accounts directory during build
add_custom_command(
    TARGET BankingService POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/accounts
)

# USing MSVC compiler
if(MSVC)
    target_compile_options(BankingService PRIVATE /W4)
else()
    # For gcc/clang compilers
    target_compile_options(BankingService PRIVATE -Wall -Wextra)
endif()