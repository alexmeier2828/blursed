add_subdirectory(list)
add_executable(MicroEdit 
	main.c
	buffer.c
	textpager.c)

include_directories(${CMAKE_SOURCE_DIR}/src/list)
target_link_libraries(MicroEdit 
	${CURSES_LIBRARIES}
	list)
