include_directories(${CMAKE_SOURCE_DIR}/src
					${CMAKE_SOURCE_DIR}/src/list
					${CMAKE_SOURCE_DIR}/src/state)

add_library(me_editorModes 
	normalMode.c
	insertMode.c
	commandMode.c)

install(TARGETS me_editorModes
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
