cmake_minimum_required (VERSION 2.8.12)
project (Common)

set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir ${src_root}/sources/src)
set (inc_dir ${src_root}/sources/inc)

include_directories (${inc_dir})
				
set (Common_inc ${inc_dir}/utils/log.hpp
				${inc_dir}/utils/ToString.hpp
				${inc_dir}/utils/traits/traits.hpp
				${inc_dir}/Communication/OneWayChannel.hpp
				${inc_dir}/Communication/ChannelFactory.hpp
				${inc_dir}/Communication/ReceivedMessagesProxy.hpp
				${inc_dir}/Communication/Proxy.hpp
				${inc_dir}/Communication/ZmqFrontendBackendBinder.hpp
				${inc_dir}/Communication/AddressProviders.hpp
				${inc_dir}/Communication/messages/XmlMessageBuilder.hpp
                ${inc_dir}/Communication/messages/SignalType.hpp
				${inc_dir}/Communication/messages/MessageType.hpp
				${inc_dir}/Communication/messages/SignalsFactory.hpp)
				
				
set (Common_src ${src_dir}/Communication/ChannelFactory.cpp
			    ${src_dir}/utils/ToString.cpp)

add_library (CommonObjects OBJECT 
    ${Common_src}
	${Common_inc}
)
