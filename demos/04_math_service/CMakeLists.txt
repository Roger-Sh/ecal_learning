cmake_minimum_required(VERSION 3.0)
project(04-math-service)

# cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find package
find_package(eCAL REQUIRED)

# find protobuf
find_package(Protobuf REQUIRED)
message(WARNING "${Protobuf_VERSION}")
message(WARNING "${Protobuf_LIBRARY}")
message(WARNING "${Protobuf_INCLUDE_DIR}")
message(WARNING "${Protobuf_PROTOC_LIBRARY}")
message(WARNING "${Protobuf_LIBRARIES}")
message(WARNING "${Protobuf_INCLUDE_DIRS}")
message(WARNING "${Protobuf_PROTOC_LIBRARIES}")

# set protobuf folder&files
set(protobuf_folder ${PROJECT_SOURCE_DIR}/proto)
set(protobuf_files ${protobuf_folder}/math_service.proto)

# math_server
add_executable(math_server src/math_server.cpp)
PROTOBUF_TARGET_CPP(math_server ${protobuf_folder} ${protobuf_files})
target_link_libraries(math_server eCAL::core protobuf::libprotobuf)

# math_client
add_executable(math_client src/math_client.cpp)
PROTOBUF_TARGET_CPP(math_client ${protobuf_folder} ${protobuf_files})
target_link_libraries(math_client eCAL::core protobuf::libprotobuf)