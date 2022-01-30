cmake_minimum_required(VERSION 3.22)
project(MicroEdit C)

find_package(Curses)


add_executable(MicroEdit 
	main.c
	buffer.c)

target_link_libraries(MicroEdit ${CURSES_LIBRARIES})
