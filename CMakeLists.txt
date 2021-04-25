cmake_minimum_required(VERSION 3.2)

project(amqp_publisher C CXX)

SET (EXAMPLE_PUBLISH "amqp_publisher")
SET (EXAMPLE_CONSUME "amqp_consumer")

# https://github.com/CopernicaMarketingSoftware/AMQP-CPP

find_package(Threads)
find_package(OpenSSL)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)

if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
link_directories("/usr/local/lib")

add_executable(${EXAMPLE_PUBLISH} main_publish.cpp
                                 SimplePocoHandler.cpp)
add_executable(${EXAMPLE_CONSUME} main_consume.cpp
                                 SimplePocoHandler.cpp)

target_include_directories(${EXAMPLE_PUBLISH} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${EXAMPLE_PUBLISH} PRIVATE -Wall -Wextra -pedantic -Werror )
target_link_libraries(${EXAMPLE_PUBLISH} PUBLIC 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${OpenSSL_LIBRARIES}
                             ${Poco_LIBRARIES}
                             amqpcpp)
set_target_properties(${EXAMPLE_PUBLISH} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${EXAMPLE_PUBLISH} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


target_include_directories(${EXAMPLE_CONSUME} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${EXAMPLE_CONSUME} PRIVATE -Wall -Wextra -pedantic -Werror )
target_link_libraries(${EXAMPLE_CONSUME} PUBLIC 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${OpenSSL_LIBRARIES}
                             ${Poco_LIBRARIES}
                             amqpcpp)
set_target_properties(${EXAMPLE_CONSUME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${EXAMPLE_CONSUME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


