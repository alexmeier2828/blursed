#test
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/list)
include(cmocka/FetchCMocka.cmake)

add_executable(linkedlist_tests linkedlist_test.c)

# TODO This is sortof bad, but theres no way to link textpager.c without actually making it a librar, and I don't feel like doing that. 
add_executable(textpager_tests textpager_tests.c ${CMAKE_SOURCE_DIR}/src/textpager.c)

target_link_libraries(linkedlist_tests PRIVATE cmocka-static list)
target_link_libraries(textpager_tests PRIVATE cmocka-static list)

#tests
enable_testing()
add_test(linked_list linkedlist_tests)
add_test(text_pager, textpager_tests)
