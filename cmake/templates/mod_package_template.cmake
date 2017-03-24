# Package file for @package_name@, part of Inviwo projects
# It defines the following variables
# 
# @package_name@_FOUND
# @package_name@_INCLUDE_DIR
# @package_name@_LIBRARY_DIR
# @package_name@_LIBRARIES
# @package_name@_DEFINITIONS
# @package_name@_LINK_FLAGS
# 

get_filename_component(PARENT_DIR ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
get_filename_component(PARENT_NAME ${PARENT_DIR} NAME)
ivw_debug_message(STATUS "${PARENT_NAME} added dependency on @_project_name@")

set(BUILD_@package_name@ 1)
set(@package_name@_PROJECT @_project_name@)
set(@package_name@_FOUND 1)
set(@package_name@_INCLUDE_DIR "@ivw_allIncDirs@")
set(@package_name@_LIBRARY_DIR "@_allLibsDir@")
set(@package_name@_LIBRARIES "@ivw_allLibs@")
set(@package_name@_DEFINITIONS @_allDefinitions@)
set(@package_name@_LINK_FLAGS @_allLinkFlags@)