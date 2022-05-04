add_library(list linkedlist.c)
add_library(dict dictionary.c)

install(TARGETS list dict
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
