# Check if cmake has the required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

if(APPLE)
cmake_policy(SET CMP0042 NEW)
endif()

project(LightSoft)

include(FindROOT.cmake)

#Check the compiler and set the compile and link flags
set(CMAKE_BUILD_TYPE Debug)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

set(INCLUDE_DIRECTORIES ${ROOT_INCLUDE_DIR})
include_directories( ${INCLUDE_DIRECTORIES})
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include/") 

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR})
link_directories( ${LINK_DIRECTORIES})

# Retry project header and source files
file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# Exclude LinkDef.h from previous selection
list(REMOVE_ITEM HPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/LinkDef.h")

# Fill list of source files 
#set(CPP_FILES )

# Fill list of header files 
#set(HPP_FILES )

# Set everything needed for the root dictonary and create the dictionary
set(LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/LinkDef.h )
set(DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/Dict.cxx) 
ROOT_GENERATE_DICTIONARY("${HPP_FILES}" "${LINKDEF}" "${DICTIONARY}" "${INCLUDE_DIRECTORIES}")

# add the LinkDef to the list of header files
SET(HPP_FILES ${HPP_FILES} ${LINKDEF})

# add the dictionary to the list of source files
SET(CPP_FILES ${CPP_FILES} ${DICTIONARY}) 

############### build the library #####################
add_library(LightSoft SHARED ${CPP_FILES} ${HPP_FILES})
target_link_libraries(LightSoft ${ROOT_LIBRARIES})

############### install the library ###################
install(TARGETS LightSoft DESTINATION ${CMAKE_BINARY_DIR}/lib)

############### install the library headers ###################
install(FILES ${HPP_FILES} DESTINATION ${CMAKE_BINARY_DIR}/include)
