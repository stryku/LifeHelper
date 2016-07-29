cmake_minimum_required (VERSION 2.8.12)
project (LifeHelper)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (HOST_LIBS_DIR "C:/moje/libs/lib/x86")
set (HOST_INC_DIR "C:/moje/libs/include")

find_package (ZMQ REQUIRED)
if (NOT ZMQ_FOUND)
    message (ERROR "ZMQ not found!")
endif()
include_directories (${ZMQ_INCLUDE_DIR})

set(BOOST_ROOT C:/moje/libs/boost/boost_1_61_0)
find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message (ERROR "Boost not found!")
endif()
include_directories (${Boost_INCLUDE_DIRS})

set( CMAKE_PREFIX_PATH C:/Qt/Qt5.7.0/5.7/msvc2015/)

set (common_inc_dir ${CMAKE_CURRENT_SOURCE_DIR}/Common/sources/inc)
include_directories (${common_inc_dir})

set (GodProgram_install_dir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (GodProgram_programs_install_dir ${GodProgram_install_dir}/programs)

set (Program2Sources ${CMAKE_CURRENT_SOURCE_DIR}/Program2Folder/sources)


add_subdirectory(Common)
add_subdirectory(Program2Folder)
add_subdirectory(GodProgram)