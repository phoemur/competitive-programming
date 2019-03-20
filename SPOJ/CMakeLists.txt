cmake_minimum_required(VERSION 3.3)

file(GLOB SRC_FILES ./*.cpp)

foreach(testsourcefile ${SRC_FILES})
    string(REPLACE ".cpp" "" output ${testsourcefile})
    string(REGEX REPLACE "^.*\/" "" output ${output})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]" "" output ${output})
    add_executable(${output} ${testsourcefile})
endforeach(testsourcefile ${SRC_FILES})
