cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(SchoolEnhancementSystem)


#Extending the module database


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")

#########################################################
# Find SFML
#########################################################
find_package(SFML COMPONENTS
    system window graphics network audio REQUIRED)
if (NOT SFML_FOUND)
    message(ERROR " SFML NOT FOUND!")
endif (NOT SFML_FOUND)
include_directories(${SFML_INCLUDE_DIR})


#########################################################
# Include Files
#########################################################
SET(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(${CMAKE_SOURCE_DIR}/Common)
add_executable(KnowledgeNet
        Scripts/Main.cpp
        Scripts/Block.cpp)

########################################################
# Linking & stuff
#########################################################

  # create the program "test"
target_link_libraries(KnowledgeNet ${SFML_LIBRARIES})
