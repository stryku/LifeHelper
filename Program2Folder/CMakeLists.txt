cmake_minimum_required (VERSION 2.8.12)
project (Program2)

set (program_name "Program2")

find_package (Qt5Widgets)
find_package (Qt5UiTools REQUIRED)

set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir ${src_root}/sources/src)
set (inc_dir ${src_root}/sources/inc)
set (internals_dir ${src_dir}/program2internals)
set (internals_inc_dir ${inc_dir}/program2internals)
set (ui_dir ${src_root}/uiforms)
set (lib_dir ${src_root}/lib)
set (install_dir ${src_root}/bin)
set (resources_dir ${src_root}/resources)

set (GodInstallDir ${GodProgram_programs_install_dir}/${program_name})

message (${program_name} " will be installed in:")
message (${install_dir})
message (${GodInstallDir})

include_directories (${inc_dir}
                     ${common_inc_dir}
                     ${Qt5UiTools_INCLUDE_DIRS})

set (Program2Objects_src ${internals_dir}/view/detail/QtWidgetManager.cpp
                         
                         ${internals_dir}/communication/MessageType.cpp)
                         
                     
set (Program2Objects_inc ${internals_inc_dir}/ProgramInfo.hpp
                         
                         ${internals_inc_dir}/communication/MessageFromGod.hpp
                         ${internals_inc_dir}/communication/MessageHandler.hpp
                         ${internals_inc_dir}/communication/MessageType.hpp
                         ${internals_inc_dir}/communication/MessageParser.hpp
                         
                         ${internals_inc_dir}/input/InputPropagator.hpp
                         ${internals_inc_dir}/input/InputHandler.hpp
                         ${internals_inc_dir}/input/InputObserver.hpp
                         
                         ${internals_inc_dir}/model/Model.hpp
                         ${internals_inc_dir}/model/SocketModelReceiver.hpp
                         ${internals_inc_dir}/model/SocketModelSender.hpp
                         ${internals_inc_dir}/model/ModelObserver.hpp
                         
                         ${internals_inc_dir}/view/QtView.hpp
                         ${internals_inc_dir}/view/SocketView.hpp
                         
                         ${internals_inc_dir}/view/detail/QtWidgetManager.hpp)
                     
set (Program2_src   ${src_dir}/main.cpp
                    ${src_dir}/mainwindow.cpp
                    ${src_dir}/ProgramInternalsCreators.cpp)

set (Program2_inc   ${inc_dir}/mainwindow.h
                    ${inc_dir}/ProgramInstance.hpp
                    ${inc_dir}/ProgramRemoteInstance.hpp
                    ${inc_dir}/ProgramInternalsCreators.h)
                     
set (Program2Objects_hdr ${inc_dir}/mainwindow.h)
set (Program2Objects_ui  ${ui_dir}/mainwindow.ui)
set (Program2Bin_src ${src_dir}/main.cpp)

qt5_wrap_cpp(Program2Objects_hdr_moc ${Program2Objects_hdr})
qt5_wrap_ui (Program2Objects_ui_moc  ${Program2Objects_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (Program2Objects OBJECT 
    ${Program2Objects_src}
    ${Program2Objects_inc}
)
#target_link_libraries (Program2Objects Qt5::Widgets Qt5::UiTools)

add_executable(Program2 
               ${Program2_src} 
               ${Program2_inc} 
               ${Program2Objects_hdr_moc}
               ${Program2Objects_ui_moc}
               $<TARGET_OBJECTS:Program2Objects> 
               $<TARGET_OBJECTS:CommonObjects>)
               
target_link_libraries (Program2 Qt5::Widgets Qt5::UiTools ${ZMQ_LIBRARIES})


install(TARGETS Program2 DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)


install(TARGETS Program2 DESTINATION  ${GodInstallDir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${GodInstallDir}
)
