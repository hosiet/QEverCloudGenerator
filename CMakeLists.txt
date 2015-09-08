cmake_minimum_required(VERSION 2.8)
project(QEverCloudGenerator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
include(QEverCloudSetupQt)
include(QEverCloudCompilerSettings)

add_subdirectory(lemon)
get_directory_property(lemon DIRECTORY lemon DEFINITION PROJECT_NAME)
get_directory_property(lempar DIRECTORY lemon DEFINITION lempar)

add_subdirectory(thrift_parser)
get_directory_property(thrift_parser DIRECTORY thrift_parser DEFINITION PROJECT_NAME)

add_subdirectory(generated)
