cmake_minimum_required (VERSION 2.8.12)
project (GodProgram)

set (program_name "GodProgram")

find_package (Qt5Widgets)
find_package (Qt5UiTools REQUIRED)

set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir ${src_root}/GodProgram)
set (inc_dir ${src_root}/GodProgram)
set (ui_dir ${src_root}/GodProgram)
set (resources_dir ${src_root}/resources)
set (install_dir ${GodProgram_install_dir})

message (${program_name} " will be installed in:")
message (${install_dir})

set (subprogramsIncludes ${Program2Sources}/inc/)

include_directories (${inc_dir} 
                     ${subprogramsIncludes}
                     ${Qt5UiTools_INCLUDE_DIRS})
           
set (GodProgram_src	${src_dir}/main.cpp
                    ${src_dir}/mainwindow.cpp)
					
set (GodProgram_inc ${inc_dir}/mainwindow.hpp
					${inc_dir}/TabCreators.hpp)
                     
set (GodProgramLib_hdr ${inc_dir}/mainwindow.hpp)
set (GodProgramLib_ui  ${ui_dir}/mainwindow.ui)
set (GodProgramBin_src ${src_dir}/main.cpp)

qt5_wrap_cpp(GodProgramLib_hdr_moc ${GodProgramLib_hdr})
qt5_wrap_ui (GodProgramLib_ui_moc  ${GodProgramLib_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (GodProgramMocObjects OBJECT 
    ${GodProgramLib_hdr_moc}
    ${GodProgramLib_ui_moc}
)

add_executable(GodProgram ${GodProgram_src}
						  ${GodProgram_inc} 
						  $<TARGET_OBJECTS:GodProgramMocObjects>
						  $<TARGET_OBJECTS:CommonObjects>)
						  
target_link_libraries (GodProgram Qt5::Widgets Qt5::UiTools ${ZMQ_LIBRARIES})


install(TARGETS GodProgram DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)
