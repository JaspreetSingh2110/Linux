cmake_minimum_required(VERSION 2.8.9)
project(process_manager)
 
#Bring the headers into the project
include_directories(include)
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(processMgr ${SOURCES})
