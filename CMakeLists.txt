cmake_minimum_required (VERSION 2.8.12)
project (GodProgram)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (HOST_LIBS_DIR "C:/moje/libs/lib/x86")
set (HOST_INC_DIR "C:/moje/libs/include")

find_package (ZMQ REQUIRED)
if (NOT ZMQ_FOUND)
    message (ERROR "ZMQ not found!")
endif()
include_directories (${ZMQ_INCLUDE_DIR})

set( CMAKE_PREFIX_PATH C:/Qt/Qt5.7.0/5.7/msvc2015/)

set (GodProgram_install_dir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (GodProgram_programs_install_dir ${GodProgram_install_dir}/programs)

add_subdirectory(Common)
add_subdirectory(Program2Folder)