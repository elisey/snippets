cmake_minimum_required (VERSION 2.8.4)

set(CMAKE_CXX_STANDART 11)
# set(CPPUTEST_LIBRARIES CppUTest CppUTestExt)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

#----------------------------------------------------#
project (ring_buffet_test)
add_executable(	ring_buffet_test
				${PROJECT_SOURCE_DIR}/main.cpp
				${PROJECT_SOURCE_DIR}/ring_buffer_test.cpp
				${PROJECT_SOURCE_DIR}/ring_buffer.c)
include_directories ("${PROJECT_SOURCE_DIR}")
find_library(CPPUTEST_LIB CppUTest)
find_library(CPPUTEST_EXT_LIB CppUTestExt)
target_link_libraries(ring_buffet_test ${CPPUTEST_LIB} ${CPPUTEST_EXT_LIB})
add_custom_command( TARGET ring_buffet_test COMMAND ./ring_buffet_test  POST_BUILD)