cmake_minimum_required(VERSION 3.24)
project(PicoDotNet_Interpreter C)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Wextra -Werror)
add_executable(PicoDotNet_Interpreter main.c)
