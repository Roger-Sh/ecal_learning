cmake_minimum_required(VERSION 3.0)
project(01-ecal-helloworld)

# cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find package
find_package(eCAL REQUIRED)
message(WARNING "${Protobuf_VERSION}")
message(WARNING "${Protobuf_LIBRARY}")
message(WARNING "${Protobuf_INCLUDE_DIR}")
message(WARNING "${Protobuf_PROTOC_LIBRARY}")
message(WARNING "${Protobuf_LIBRARIES}")
message(WARNING "${Protobuf_INCLUDE_DIRS}")
message(WARNING "${Protobuf_PROTOC_LIBRARIES}")

# helloworld_puber
add_executable(helloworld_puber src/helloworld_puber.cpp)
target_link_libraries(helloworld_puber eCAL::core)

# helloworld_suber
add_executable(helloworld_suber src/helloworld_suber.cpp)
target_link_libraries(helloworld_suber eCAL::core)