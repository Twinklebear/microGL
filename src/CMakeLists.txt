add_executable(microGL main.c vector4f.c matrix4f.c matrix4f_stack.c
	vertex.c vertex_list.c)

target_link_libraries(microGL ${SDL2_LIBRARY})

install(TARGETS microGL DESTINATION ${microGL_INSTALL_DIR})

