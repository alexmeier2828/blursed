cmake_minimum_required(VERSION 3.16)
project(MicroEditProj C)

find_package(Curses)

add_subdirectory(src)
add_subdirectory(test)

