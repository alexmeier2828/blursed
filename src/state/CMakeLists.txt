include_directories(${CMAKE_SOURCE_DIR}/src
					${CMAKE_SOURCE_DIR}/src/list)

add_library(me_state editorState.c)

install(TARGETS me_state
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
