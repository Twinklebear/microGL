add_executable(microGL main.c vector4f.c matrix4f.c matrix4f_stack.c
	vertex.c vertex_list.c microgl.c microgl_driver.c)

target_link_libraries(microGL ${nano_bmp_LIBRARY})

install(TARGETS microGL DESTINATION ${microGL_INSTALL_DIR})

