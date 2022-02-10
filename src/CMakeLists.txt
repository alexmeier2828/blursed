add_subdirectory(${CMAKE_SOURCE_DIR}/src/list)
add_executable(MicroEdit 
	main.c
	buffer.c
	textpager.c)

include_directories(${CMAKE_SOURCE_DIR}/src/list)
target_link_libraries(MicroEdit list)
