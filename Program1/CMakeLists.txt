cmake_minimum_required (VERSION 2.8.12)
project (Program2)


find_package (Qt5Widgets)
find_package (Qt5UiTools REQUIRED)

set (src_dir ${PROJECT_SOURCE_DIR}/sources/src)
set (internals_dir ${src_dir}/internals)
set (inc_dir ${PROJECT_SOURCE_DIR}/sources/inc)
set (ui_dir ${PROJECT_SOURCE_DIR}/uiforms)
set (lib_dir ${PROJECT_SOURCE_DIR}/lib)
set (bin_dir ${PROJECT_SOURCE_DIR}/bin)


set(CMAKE_INSTALL_PREFIX "${bin_dir}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)

include_directories (${inc_dir} 
					 ${Qt5UiTools_INCLUDE_DIRS})

set (Program1Lib_src ${internals_dir}/view/P2ConsoleView.cpp
					 ${internals_dir}/view/P2QtView.cpp
					 ${internals_dir}/view/P2View.cpp
					 ${internals_dir}/view/detail/P2QtWidgetManager.cpp
					 ${internals_dir}/input/P2Input.cpp
					 ${internals_dir}/input/P2InputHandler.cpp
					 ${internals_dir}/input/P2InputObserver.cpp
					 ${internals_dir}/model/P2Model.cpp
					 ${internals_dir}/model/P2ModelObserver.cpp
					 ${internals_dir}/controller/P2QtController.cpp
					 ${internals_dir}/controller/P2Controller.cpp)
					 
set (Program1_src  	${src_dir}/main.cpp
					${src_dir}/mainwindow.cpp
					 ${src_dir}/ProgramFactory.cpp
					 ${src_dir}/ViewFactory.cpp)
					 
set (Program1Lib_hdr ${inc_dir}/mainwindow.h)
set (Program1Lib_ui  ${ui_dir}/mainwindow.ui)
set (Program1Bin_src ${src_dir}/main.cpp)

qt5_wrap_cpp(Program1Lib_hdr_moc ${Program1Lib_hdr})
qt5_wrap_ui (Program1Lib_ui_moc  ${Program1Lib_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (Program1Lib STATIC 
    ${Program1Lib_src}
    ${Program1Lib_hdr_moc}
    ${Program1Lib_ui_moc}
)

target_link_libraries (Program1Lib Qt5::Widgets Qt5::UiTools)

add_executable(Program1 ${Program1_src})
target_link_libraries (Program1 Program1Lib)


install(TARGETS Program1Lib DESTINATION  ${lib_dir}/)
install(TARGETS Program1 DESTINATION  ${bin_dir}/)
