#test
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/list)
include_directories(${CMAKE_SOURCE_DIR}/src/state)
include(cmocka/FetchCMocka.cmake)

add_executable(linkedlist_tests linkedlist_test.c)

# TODO This is sortof bad, but theres no way to link textpager.c without actually making it a librar, and I don't feel like doing that. 
add_executable(textpager_tests textpager_tests.c ${CMAKE_SOURCE_DIR}/src/textpager.c)

add_executable(editorState_tests editorStateTests.c)

target_link_libraries(linkedlist_tests PRIVATE cmocka-static list)
target_link_libraries(textpager_tests PRIVATE cmocka-static list)
target_link_libraries(editorState_tests PRIVATE cmocka-static list me_state)

#tests
enable_testing()
add_test(linkedList linkedlist_tests)
add_test(textPager, textpager_tests)
add_test(editorState, editorState_tests)
