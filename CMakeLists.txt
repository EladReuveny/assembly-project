cmake_minimum_required(VERSION 3.24)
project(Maman14 C)

set(CMAKE_C_STANDARD 90)

add_executable(Maman14 assembler.c analyze.c macro.c instructions.c instructions.h machinecode.c machinecode.h symbols.c symbols.h utilities.h utilities.c)
