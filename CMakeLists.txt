cmake_minimum_required(VERSION 3.22)
project(MicroEdit C)

find_package(Curses)

include_directories(./src/list)
add_executable(MicroEdit 
	src/main.c
	src/buffer.c)

#test
include(test/cmocka/FetchCMocka.cmake)
add_executable(test 
	test/linkedlist_test.c
	src/list/linkedlist.c)
target_link_libraries(test PRIVATE cmocka-static)
target_link_libraries(MicroEdit ${CURSES_LIBRARIES})
