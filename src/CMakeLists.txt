add_subdirectory(list)
add_subdirectory(state)
add_subdirectory(editorMode)

add_executable(blursed
	main.c
	buffer.c
	textpager.c)

include_directories(${CMAKE_SOURCE_DIR}/src/list
					${CMAKE_SOURCE_DIR}/src/state
					${CMAKE_SOURCE_DIR}/src/editorMode)

target_link_libraries(blursed
	${CURSES_LIBRARIES}
	list
	me_state
	me_editorModes)
