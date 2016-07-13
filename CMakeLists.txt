cmake_minimum_required (VERSION 2.8.12)
project (GodProgram)

set( CMAKE_PREFIX_PATH C:/Qt/Qt5.7.0/5.7/msvc2015/)

set (GodProgram_install_dir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (GodProgram_programs_install_dir ${GodProgram_install_dir}/programs)

add_subdirectory(Common)
add_subdirectory(Program2Folder)