cmake_minimum_required(VERSION 3.22)
project(MicroEdit C)

find_package(Curses)

include(src/CMakeLists.txt)

#test
include(test/cmocka/FetchCMocka.cmake)
include_directories(src/list)
include_directories(src/)
add_executable(linkedlist_tests
	test/linkedlist_test.c
	src/list/linkedlist.c)
add_executable(textpager_tests
	test/textpager_tests.c
	src/textpager.c
	src/list/linkedlist.c)


target_link_libraries(linkedlist_tests PRIVATE cmocka-static)
target_link_libraries(textpager_tests PRIVATE cmocka-static)
target_link_libraries(MicroEdit ${CURSES_LIBRARIES})

#tests
enable_testing()
add_test(linked_list linkedlist_tests)
add_test(text_pager, textpager_tests)
