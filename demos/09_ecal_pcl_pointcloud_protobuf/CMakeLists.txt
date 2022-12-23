cmake_minimum_required(VERSION 3.0)
project(09_ecal_pcl_pointcloud_protobuf)

# cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find eCAL
find_package(eCAL REQUIRED)
message(WARNING "${eCAL_VERSION}")

# find Protobuf
find_package(Protobuf REQUIRED)
message(WARNING "${Protobuf_VERSION}")
message(WARNING "${Protobuf_LIBRARY}")
message(WARNING "${Protobuf_LIBRARIES}")
message(WARNING "${Protobuf_INCLUDE_DIR}")
message(WARNING "${Protobuf_INCLUDE_DIRS}")
message(WARNING "${Protobuf_PROTOC_LIBRARY}")
message(WARNING "${Protobuf_PROTOC_LIBRARIES}")

# find PCL
# find_package(PCL 1.9.1 REQUIRED
#     PATHS "/home/shan/App/pcl/pcl-pcl-1.9.1/build/installed"
#     NO_DEFAULT_PATH
# )
find_package(PCL REQUIRED)
message(WARNING "${PCL_VERSION}")
message(WARNING "${PCL_LIBRARIES}")
message(WARNING "${PCL_LIBRARY_DIRS}")
message(WARNING "${PCL_INCLUDE_DIRS}")
message(WARNING "${PCL_DEFINITIONS}")

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# set protobuf folder&files
set(protobuf_folder ${PROJECT_SOURCE_DIR}/proto)
set(protobuf_files ${protobuf_folder}/pcl_pointcloud_xyz.proto)

# pcl_protobuf_puber
add_executable(pcl_protobuf_puber src/pcl_protobuf_puber.cpp)
PROTOBUF_TARGET_CPP(pcl_protobuf_puber ${protobuf_folder} ${protobuf_files})
target_link_libraries(pcl_protobuf_puber eCAL::core ${Protobuf_LIBRARIES} ${PCL_LIBRARIES})

# pcl_protobuf_suber
add_executable(pcl_protobuf_suber src/pcl_protobuf_suber.cpp)
PROTOBUF_TARGET_CPP(pcl_protobuf_suber ${protobuf_folder} ${protobuf_files})
target_link_libraries(pcl_protobuf_suber eCAL::core ${Protobuf_LIBRARIES} ${PCL_LIBRARIES})
