cmake_minimum_required( VERSION 3.11 FATAL_ERROR )

project(
    teqi-canvas
    VERSION 0.0.0
    DESCRIPTION "A minimal 3D-graphics starting point"
    HOMEPAGE_URL "https://github.com/gurki/"
    LANGUAGES CXX
)

add_subdirectory( dependencies )

add_compile_definitions( TQ_CANVAS_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/" )

add_library( ${PROJECT_NAME} STATIC
    src/window.cpp
    src/shader.cpp
    src/shaderprogram.cpp
    src/keys.cpp
    src/mouse.cpp
    src/texture.cpp
)

add_library( ${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME} )

target_compile_features( ${PROJECT_NAME}
    PUBLIC
        cxx_std_17  #  std::optional, nested namespaces
    PRIVATE
        cxx_auto_type
        cxx_defaulted_functions
        cxx_lambdas
        cxx_range_for
        cxx_trailing_return_types
        cxx_unicode_literals
        cxx_inline_namespaces
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        dependencies/
)

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
        glfw
        libglew_static
        glm::glm
        fmt::fmt
)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)


#-------------------------------------------------------------------------------

add_executable( ${PROJECT_NAME}-demo
    demo/main.cpp
)

target_link_libraries( ${PROJECT_NAME}-demo
    PRIVATE
        ${PROJECT_NAME}::${PROJECT_NAME}
)