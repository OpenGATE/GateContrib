cmake_minimum_required(VERSION 2.6)

################################################################################
# Project configuration
################################################################################

set(projectName pdp)
set(projectBinary ${projectName}.x)

project(${projectName} CXX) # using only C++

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

add_definitions(-std=c++11 -Wall -Wunused-parameter) # using C++11 standard

################################################################################
# Handling of ROOT 
################################################################################

## Find CERN ROOT
# first try to find ROOT 6 or ROOT 5 compiled with CMake
# if present, such ROOT should be possible to find without explicit setting of any paths
find_package(ROOT 6 QUIET)

# try to locate ROOT using ROOTSYS and root-config in case ROOTSYS is not set
# this might be necessary for ROOT 5 built with autotools rather than CMake
set(root_prefix $ENV{ROOTSYS})
if(root_prefix)
  list(APPEND CMAKE_MODULE_PATH ${root_prefix}/etc/cmake/)
else()
  execute_process(COMMAND root-config --etcdir OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
  list(APPEND CMAKE_MODULE_PATH ${ROOT_ETCDIR}/cmake)
endif()
find_package(ROOT 5 QUIET)
if(ROOT_FOUND)
  message(STATUS "ROOT (version ${ROOT_VERSION}) was found using FindROOT (legacy mode)")
else()
  # as last resort, use the bundled FindROOT module
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fallback)
  find_package(ROOT 5 REQUIRED)
  if(ROOT_FOUND)
    message(WARNING "No CMake modules from a ROOT installation were found. ROOT (version ${ROOT_VERSION}) was only found using fallback mode)")
  endif()
endif()

if(ROOT_USE_FILE)
  include(${ROOT_USE_FILE})
endif()

################################################################################
# Sources and linking 
################################################################################

file(GLOB SOURCES *.cpp)

file(GLOB HEADERS *.h)
 
add_executable(pdp ${SOURCES} ${HEADERS} )
target_link_libraries(pdp ${ROOT_LIBRARIES} )
