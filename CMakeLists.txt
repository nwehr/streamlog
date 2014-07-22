##############################################################################
# Project Settings/Requirements
##############################################################################
cmake_minimum_required( VERSION 2.8 )

include_directories( "${PROJECT_SOURCE_DIR}" )

include_directories( "/usr/include" )
include_directories( "/usr/local/include" )
include_directories( "/opt/local/include" )

ADD_DEFINITIONS( -std=c++0x )

##############################################################################
# Build - Library
##############################################################################
add_library( streamlog SHARED "${PROJECT_SOURCE_DIR}/streamlog.cpp" )

##############################################################################
# Install - Library
##############################################################################
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set( MAKE_INSTALL_PREFIX "/opt/local" )
	set_target_properties( streamlog PROPERTIES MACOSX_RPATH 1 )
else()
	set( MAKE_INSTALL_PREFIX "/usr/local" )
endif()

install( FILES "${PROJECT_SOURCE_DIR}/streamlog.h" DESTINATION "${MAKE_INSTALL_PREFIX}/include/streamlog" )
install( TARGETS streamlog LIBRARY DESTINATION "${MAKE_INSTALL_PREFIX}/lib" )
