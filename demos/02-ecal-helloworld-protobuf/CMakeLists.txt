cmake_minimum_required(VERSION 3.0)
project(02-ecal-helloworld-protobuf)

# cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find ecal
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
set(protobuf_files ${protobuf_folder}/hello_world.proto)

# helloworld_proto_puber
add_executable(helloworld_proto_puber src/helloworld_proto_puber.cpp)
PROTOBUF_TARGET_CPP(helloworld_proto_puber ${protobuf_folder} ${protobuf_files})
target_link_libraries(helloworld_proto_puber eCAL::core protobuf::libprotobuf)

# helloworld_proto_suber
add_executable(helloworld_proto_suber src/helloworld_proto_suber.cpp)
PROTOBUF_TARGET_CPP(helloworld_proto_suber ${protobuf_folder} ${protobuf_files})
target_link_libraries(helloworld_proto_suber eCAL::core protobuf::libprotobuf)