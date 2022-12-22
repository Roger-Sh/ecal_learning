cmake_minimum_required(VERSION 3.0)
project(06_ecal_binary)

 # cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find package
find_package(eCAL REQUIRED)

# binary_snd
add_executable(binary_snd src/binary_snd.cpp)
target_link_libraries(binary_snd eCAL::core)

# binary_rec
add_executable(binary_rec src/binary_rec.cpp)
target_link_libraries(binary_rec eCAL::core)
