#=========================================================
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)
CMAKE_POLICY(SET CMP0012 NEW)
CMAKE_POLICY(SET CMP0025 NEW)

#=========================================================
PROJECT(Gate)

SET(GATE_SOURCE_DIR "" CACHE PATH "Path to source of Gate")
IF (GATE_SOURCE_DIR STREQUAL "")
  MESSAGE(FATAL_ERROR "Set a path for GATE_SOURCE_DIR")
ENDIF()
FILE(COPY ${GATE_SOURCE_DIR}/cmake-modules DESTINATION ${PROJECT_SOURCE_DIR})

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules ${CMAKE_MODULE_PATH})

#=========================================================
# Help function to debug CMake
MACRO (DD in)
  MESSAGE(${in}=[${${in}}])
ENDMACRO(DD)

#===============
# Do not use RPATH for Mac, it fails to run Gate when install it
 IF (APPLE)
   SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
 ENDIF()
#=========================================================
# Default build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

FIND_PACKAGE(Geant4 REQUIRED)

#=========================================================
# Refuse to build with MT geant4, allow dev override
IF(Geant4_multithreaded_FOUND)
    MESSAGE(FATAL_ERROR "GATE should be compiled with a non-multithreaded installation of Geant4")
ENDIF()

#=========================================================
# Build variables for G4 Version

STRING(REGEX REPLACE "(.*)[.](.*)[.](.*)" "\\1" G4VERSION_MAJOR ${Geant4_VERSION})
STRING(REGEX REPLACE "(.*)[.](.*)[.](.*)" "\\2" G4VERSION_MINOR ${Geant4_VERSION})
STRING(REGEX REPLACE "(.*)[.](.*)[.](.*)" "\\3" G4VERSION_PATCH ${Geant4_VERSION})
#MESSAGE(${Geant4_VERSION})
#MESSAGE(${G4VERSION_MAJOR})
#MESSAGE(${G4VERSION_MINOR})
#MESSAGE(${G4VERSION_PATCH})
IF(NOT ${G4VERSION_MAJOR}.${G4VERSION_MINOR} EQUAL 10.5 AND NOT ${G4VERSION_MAJOR}.${G4VERSION_MINOR} EQUAL 10.6)
  MESSAGE("Warning! GATE version 9.0 is not validated for Geant4 ${G4VERSION_MAJOR}.${G4VERSION_MINOR} distribution. Please use Geant4 10.6 distribution instead.")
ENDIF()

#=========================================================
# Option for Root use
SET(GATE_USE_ROOT ON)
SET(GATE_ANALYSIS_USE_GENERAL ON)
SET(GATE_ANALYSIS_USE_FILE ON)

#=========================================================
# ROOT
IF(GATE_USE_ROOT)
  FIND_PACKAGE(ROOT REQUIRED)
  INCLUDE_DIRECTORIES(${ROOT_INCLUDE_DIR})
  SET(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR})
  #MESSAGE("Found Root in ${ROOT_INCLUDE_DIR} ${ROOT_LIBRARY_DIR} ${ROOT_LIBRARIES}")
  #IF(ROOT_INCLUDE_DIR)
    #MESSAGE("Your current Root version is ${ROOT_VERSION}")
  #ELSE()
  IF(NOT ROOT_INCLUDE_DIR)
    MESSAGE("Root not found! Please install Root and make it available in PATH")
  ENDIF()
ENDIF()

#=========================================================
# Option for XRAYLIB use
IF(GATE_USE_XRAYLIB)
  FIND_PACKAGE(LIBXRL REQUIRED)
  INCLUDE_DIRECTORIES(${LIBXRL_INCLUDE_DIR})
  SET(LINK_DIRECTORIES ${LIBXRL_LIBRARIES})
  IF(NOT LIBXRL_INCLUDE_DIR)
    MESSAGE("xraylib not found! Please install xraylib and make it available in PATH or manually set the LIBXRL_LIBRARY and LIBXRL_INCLUDE variables.")
  ENDIF()
ENDIF(GATE_USE_XRAYLIB)

#=========================================================
# Option for Clhep use
IF(GATE_USE_SYSTEM_CLHEP)
  FIND_PACKAGE(CLHEP REQUIRED)
  INCLUDE_DIRECTORIES(${CLHEP_INCLUDE_DIR})
  SET(LINK_DIRECTORIES ${CLHEP_LIBRARIES})
  MESSAGE("Your current CLHEP version is ${CLHEP_VERSION}")
  MESSAGE("Please refer to http://geant4.web.cern.ch/geant4/support/ReleaseNotes4.${G4VERSION_MAJOR}.${G4VERSION_MINOR}.html to verify that your CLHEP version is supported by Geant4.")

  #MESSAGE("Found Clhep in ${CLHEP_INCLUDE_DIR} ${CLHEP_LIBRARY}")
ENDIF()

#=========================================================
# Option for LMF use
IF(GATE_USE_LMF)
  FIND_PATH(LMF_HOME lmf /usr /usr/local)
  SET(LMF_INCLUDE_DIR "${LMF_HOME}/includes")
  SET(LMF_LIBRARIES "${LMF_HOME}/lib")
  SET(LMF_LIBRARY "-L${LMF_LIBRARIES} -lLMF")
  INCLUDE_DIRECTORIES(${LMF_INCLUDE_DIR})
  SET(LINK_DIRECTORIES ${LMF_LIBRARIES})
  #MESSAGE("Found Lmf in ${LMF_INCLUDE_DIR} ${LMF_LIBRARIES} ${LMF_LIBRARY}")
ENDIF(GATE_USE_LMF)

#=========================================================
# Option for ECAT7 use
IF(GATE_USE_ECAT7)
  FIND_PATH(ECAT7_HOME ecat /usr /usr/local)
  SET(ECAT7_INCLUDE_DIR "${ECAT7_HOME}/include")
  SET(ECAT7_LIBRARIES "${ECAT7_HOME}/lib")
  SET(ECAT7_LIBRARY "-L${ECAT7_LIBRARIES} -lecat")
  INCLUDE_DIRECTORIES(${ECAT7_INCLUDE_DIR})
  SET(LINK_DIRECTORIES ${ECAT7_LIBRARIES})
  #MESSAGE("Found Ecat in ${ECAT7_INCLUDE_DIR} ${ECAT7_LIBRARIES} ${ECAT7_LIBRARY}")
ENDIF(GATE_USE_ECAT7)

#=========================================================
# Create configuration file
CONFIGURE_FILE(${GATE_SOURCE_DIR}/GateConfiguration.h.in ${PROJECT_BINARY_DIR}/GateConfiguration.h)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

#=========================================================
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
INCLUDE(${Geant4_USE_FILE})
INCLUDE_DIRECTORIES(
  ${GATE_SOURCE_DIR}/source/io/include
  ${GATE_SOURCE_DIR}/source/arf/include
  ${GATE_SOURCE_DIR}/source/geometry/include
  ${GATE_SOURCE_DIR}/source/physics/include
  ${GATE_SOURCE_DIR}/source/digits_hits/include
  ${GATE_SOURCE_DIR}/source/general/include
  ${GATE_SOURCE_DIR}/source/externals/clhep/include)

#=========================================================
# Locate sources and headers for this project
FILE(GLOB sources
  ${GATE_SOURCE_DIR}/source/io/src/*.cc
  ${GATE_SOURCE_DIR}/source/arf/src/*.cc
  ${GATE_SOURCE_DIR}/source/geometry/src/*.cc
  ${GATE_SOURCE_DIR}/source/digits_hits/src/*.cc
  ${GATE_SOURCE_DIR}/source/physics/src/*.cc
  ${GATE_SOURCE_DIR}/source/general/src/*.cc
  ${GATE_SOURCE_DIR}/source/externals/clhep/src/CLHEP/Matrix/*.cc
  ${GATE_SOURCE_DIR}/source/externals/clhep/src/CLHEP/RandomObjects/*.cc)

FILE(GLOB headers
  ${GATE_SOURCE_DIR}/source/io/include/*.hh
  ${GATE_SOURCE_DIR}/source/arf/include/*.hh
  ${GATE_SOURCE_DIR}/source/geometry/include/*.hh
  ${GATE_SOURCE_DIR}/source/physics/include/*.hh
  ${GATE_SOURCE_DIR}/source/digits_hits/include/*.hh
  ${GATE_SOURCE_DIR}/source/general/include/*.hh
  ${GATE_SOURCE_DIR}/source/externals/clhep/include/*.hh
  ${GATE_SOURCE_DIR}/source/gpu/include/*.hh)

#=========================================================
IF(GATE_USE_TORCH)
  FIND_PACKAGE(Torch REQUIRED)
ENDIF()

#=========================================================
#ITK
ADD_SUBDIRECTORY(${GATE_SOURCE_DIR}/source/externals/itk-mhd ${PROJECT_BINARY_DIR}/itk-mhd)
SET(ITK_LIBRARIES MetaIO itkzlib)
INCLUDE_DIRECTORIES(
${GATE_SOURCE_DIR}/source/externals/itk-mhd/
${GATE_SOURCE_DIR}/source/externals/itk-mhd/itkzlib
${GATE_SOURCE_DIR}/source/externals/itk-mhd/src
${PROJECT_BINARY_DIR}/itk-mhd/)
SET(ITKMHD_LIBS MetaIO itkzlib)

#=========================================================
# Add the executable, and link it to the Geant4/ROOT/CLHEP/ITK libraries
ADD_EXECUTABLE(GateRootSeqCoincTree2SivanTraFileConverter GateRootSeqCoincTree2SivanTraFileConverter.cc ${sources} ${headers})
ADD_EXECUTABLE(GateRootSeqCoincTree2MACACOListMode GateRootSeqCoincTree2MACACOListMode.cc ${sources} ${headers})

TARGET_LINK_LIBRARIES(GateRootSeqCoincTree2SivanTraFileConverter ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} ${LIBXML2_LIBRARIES} ${LIBXRL_LIBRARIES} ${LMF_LIBRARY} ${ECAT7_LIBRARY} ${ITK_LIBRARIES} pthread)
TARGET_LINK_LIBRARIES(GateRootSeqCoincTree2MACACOListMode ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} ${LIBXML2_LIBRARIES} ${LIBXRL_LIBRARIES} ${LMF_LIBRARY} ${ECAT7_LIBRARY} ${ITK_LIBRARIES} pthread)

#=========================================================
INSTALL(TARGETS GateRootSeqCoincTree2SivanTraFileConverter DESTINATION bin)
INSTALL(TARGETS GateRootSeqCoincTree2MACACOListMode DESTINATION bin)

#=========================================================
# We remove the warning option "shadow", because there are tons of
# such warning related to clhep/g4 system of units. Additionally,
# we force the c++11 std. This is mandatory for Geant4 >= 10.2.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 11)

#=========================================================

#=========================================================
# Display Geant4 version
MESSAGE("Your current Geant4 version is ${Geant4_VERSION}")

#=========================================================
# Add gprof to RELWITHDEBINFO target
IF(NOT APPLE)
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -pg")
  SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -pg")
  SET(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} -pg")
ENDIF()
#=========================================================
