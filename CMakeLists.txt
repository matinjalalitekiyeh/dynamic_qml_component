cmake_minimum_required(VERSION 3.22)

project(dynamic_qml_component
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_NAME "appdynamic_qml_component")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cnfg/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app/cnfg)

add_subdirectory(configured)

add_subdirectory(app)
