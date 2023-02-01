cmake_minimum_required(VERSION 3.0)
project(08_ecal_cvmat_protobuf)

# cmake set
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find eCAL
find_package(eCAL REQUIRED)
message(WARNING "${eCAL_VERSION}")
# message(WARNING "${eCAL_LIB}")
# message(WARNING "${eCAL_LIBS}")
# message(WARNING "${eCAL_LIBRARY}")
# message(WARNING "${eCAL_LIBRARIES}")
# message(WARNING "${eCAL_INCLUDE_DIR}")
# message(WARNING "${eCAL_INCLUDE_DIRS}")
# message(WARNING "${eCAL_INCLUDES}")

# find protobuf
find_package(Protobuf REQUIRED)
message(WARNING "${Protobuf_VERSION}")
message(WARNING "${Protobuf_LIBRARY}")
message(WARNING "${Protobuf_LIBRARIES}")
message(WARNING "${Protobuf_INCLUDE_DIR}")
message(WARNING "${Protobuf_INCLUDE_DIRS}")
message(WARNING "${Protobuf_PROTOC_LIBRARY}")
message(WARNING "${Protobuf_PROTOC_LIBRARIES}")

# find opencv
find_package(OpenCV REQUIRED)
message(WARNING "${OpenCV_VERSION}")
message(WARNING "${OpenCV_LIBS}")
message(WARNING "${OpenCV_LIBRARIES}")
message(WARNING "${OpenCV_INCLUDE_DIRS}")

# set protobuf folder&files
set(protobuf_folder ${PROJECT_SOURCE_DIR}/proto)
set(protobuf_files ${protobuf_folder}/cvmat.proto ${protobuf_folder}/cvmatArray.proto)

# cvmat_proto_puber
add_executable(cvmat_proto_puber src/cvmat_proto_puber.cpp)
PROTOBUF_TARGET_CPP(cvmat_proto_puber ${protobuf_folder} ${protobuf_files})
target_link_libraries(cvmat_proto_puber eCAL::core ${Protobuf_LIBRARIES} ${OpenCV_LIBS})

# cvmat_proto_suber
add_executable(cvmat_proto_suber src/cvmat_proto_suber.cpp)
PROTOBUF_TARGET_CPP(cvmat_proto_suber ${protobuf_folder} ${protobuf_files})
target_link_libraries(cvmat_proto_suber eCAL::core ${Protobuf_LIBRARIES} ${OpenCV_LIBS})
