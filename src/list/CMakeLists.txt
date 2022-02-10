add_library(list linkedlist.c)

install(TARGETS list
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
