add_subdirectory(list)
add_subdirectory(state)

add_executable(MicroEdit 
	main.c
	buffer.c
	textpager.c)

include_directories(${CMAKE_SOURCE_DIR}/src/list
					${CMAKE_SOURCE_DIR}/src/state)

target_link_libraries(MicroEdit 
	${CURSES_LIBRARIES}
	list
	me_state)
