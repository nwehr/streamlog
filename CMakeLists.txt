##############################################################################
# Project Settings/Requirements
##############################################################################
cmake_minimum_required( VERSION 2.6 )

include_directories( "${PROJECT_SOURCE_DIR}" )

include_directories( "/usr/include" )
include_directories( "/usr/local/include" )

##############################################################################
# Build - Library
##############################################################################
add_library( streamlog SHARED "${PROJECT_SOURCE_DIR}/streamlog.cpp" )

##############################################################################
# Install - Library
##############################################################################
set( MAKE_INSTALL_PREFIX "/usr/local" )
install( FILES "${PROJECT_SOURCE_DIR}/streamlog.h" DESTINATION "/usr/local/include/streamlog" )
install( TARGETS streamlog LIBRARY DESTINATION "/usr/local/lib" )
