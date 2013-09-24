##############################################################################
# Project Settings/Requirements
##############################################################################
cmake_minimum_required( VERSION 2.6 )
project( eloquentd )

include_directories( "${PROJECT_SOURCE_DIR}/../" )

##############################################################################
# Build - Library
##############################################################################
add_library( log SHARED "${PROJECT_SOURCE_DIR}/log.cpp" )

##############################################################################
# Install - Library
##############################################################################
install( FILES "${PROJECT_SOURCE_DIR}/log.h" DESTINATION "/usr/local/include/log" )
install( TARGETS log LIBRARY DESTINATION "/usr/local/lib" )
