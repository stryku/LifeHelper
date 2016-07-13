cmake_minimum_required (VERSION 2.8.12)
project (Common)

set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir ${src_root}/sources/src)
set (inc_dir ${src_root}/sources/inc)

include_directories (${inc_dir})

set (Common_src ${src_dir}/...)
                     
set (Common_inc ${inc_dir}/...)

add_library (CommonLib OBJECT 
    ${Common_src}
	${Common_inc}
)
