cmake_minimum_required(VERSION 3.0)
project(03-mininal-service)

# cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find package
find_package(eCAL REQUIRED)

# minimal_server
add_executable(minimal_server src/minimal_server.cpp)
target_link_libraries(minimal_server eCAL::core)

# minimal_client_block
add_executable(minimal_client_block src/minimal_client_block.cpp)
target_link_libraries(minimal_client_block eCAL::core)

# minimal_client_callback
add_executable(minimal_client_callback src/minimal_client_callback.cpp)
target_link_libraries(minimal_client_callback eCAL::core)