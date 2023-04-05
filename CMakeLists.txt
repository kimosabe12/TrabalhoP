cmake_minimum_required(VERSION 3.23)
project(TrabalhoP C)

set(CMAKE_C_STANDARD 99)

add_executable(TrabalhoP main.c Paragens.c Paragens.h headers.h gestao_linhas.c gestao_linhas.h)
