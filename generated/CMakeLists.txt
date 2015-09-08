cmake_minimum_required(VERSION 2.8)
project(generated)

file(GLOB thrift_files "${CMAKE_CURRENT_SOURCE_DIR}/../thrift/*.thrift")

set(GENERATED_FILENAMES
    types.h
    types_impl.h
    types.cpp
    services.h
    services.cpp
    EDAMErrorCode.h
    constants.h
    constants.cpp)

foreach(GENERATED_FILENAME ${GENERATED_FILENAMES})
    set(GENERATED_FILE "${CMAKE_CURRENT_BINARY_DIR}/${GENERATED_FILENAME}")

    add_custom_command(OUTPUT "${GENERATED_FILE}"
                       COMMAND ${CMAKE_COMMAND} -E echo "Generating file ${GENERATED_FILENAME}..."
                       COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/generated"
                       COMMAND ${thrift_parser} "${CMAKE_CURRENT_SOURCE_DIR}/../thrift/src/" "${CMAKE_CURRENT_BINARY_DIR}/generated/"
                       COMMAND ${CMAKE_COMMAND} -E echo "Ran thrift parser on thrift sources to generate ${GENERATED_FILE}" 
                       DEPENDS ${thrift_files})

                   add_custom_target(generate_${GENERATED_FILENAME} ALL DEPENDS "${GENERATED_FILE}")
endforeach()
