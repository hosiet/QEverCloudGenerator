cmake_minimum_required(VERSION 2.8)
project(thrift_parser)

set(HEADERS
    Generator.h
    Lexer.h
    Parser.h
    ParserHelper.h)

set(SOURCES
    Generator.cpp
    Lexer.cpp
    main.cpp
    Parser.cpp)

# Pre build step: copy thrift_lemon.y to build dir, execute lemon on it and remove the output file
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/thrift_lemon.out"
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/thrift_lemon.y" "${CMAKE_CURRENT_BINARY_DIR}"
                   COMMAND ${CMAKE_COMMAND} -E echo "thrift_lemon.y was copied to build dir"
                   COMMAND ${lemon} "${CMAKE_CURRENT_BINARY_DIR}/thrift_lemon.y"
                   COMMAND ${CMAKE_COMMAND} -E echo "lemon was executed on thrift_lemon.y"
                   DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/thrift_lemon.y")

add_custom_target(pre_build
                  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/thrift_lemon.out"
                  SOURCES thrift_lemon.y)

list(APPEND IDL_COMPILED_FILES "${CMAKE_CURRENT_BINARY_DIR}/thrift_lemon.h")
list(APPEND IDL_COMPILED_FILES "${CMAKE_CURRENT_BINARY_DIR}/thrift_lemon.cpp")

set_source_files_properties(${IDL_COMPILED_FILES}
                            PROPERTIES GENERATED TRUE)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${IDL_COMPILED_FILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

add_dependencies(${PROJECT_NAME} pre_build)

