cmake_minimum_required( VERSION 3.11 FATAL_ERROR )

#-------------------------------------------------------------------------------

set( MODULE_NAME fmt )
set( MODULE_URL https://github.com/fmtlib/fmt.git )
set( MODULE_VERSION 7.0.3 )

include ( FetchModule.cmake )

#-------------------------------------------------------------------------------

set( MODULE_NAME glm )
set( MODULE_URL https://github.com/g-truc/glm.git )
set( MODULE_VERSION 0.9.9.8 )

include ( FetchModule.cmake )

#-------------------------------------------------------------------------------

set( MODULE_NAME glfw )
set( MODULE_URL https://github.com/glfw/glfw.git )
set( MODULE_VERSION 3.3.2 )

include ( FetchModule.cmake )

#-------------------------------------------------------------------------------

set( MODULE_NAME glew )
set( MODULE_URL https://github.com/Perlmint/glew-cmake.git )
set( MODULE_VERSION glew-cmake-2.1.0 )

add_definitions( -DGLEW_STATIC )
include ( FetchModule.cmake )


