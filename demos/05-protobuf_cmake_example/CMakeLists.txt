PROJECT(minimal_protobuf_cmake_example)
CMAKE_MINIMUM_REQUIRED (VERSION 3.0)

# CMAKE set
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find Protobuf
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message ("protobuf found")
else()
    message (FATAL_ERROR "Cannot find Protobuf")
endif()
message(WARNING "${Protobuf_VERSION}")
message(WARNING "${Protobuf_LIBRARIES}")
message(WARNING "${Protobuf_INCLUDE_DIRS}")
message(WARNING "${Protobuf_PROTOC_LIBRARIES}")
message(WARNING "${Protobuf_LIBRARY}")
message(WARNING "${Protobuf_INCLUDE_DIR}")
message(WARNING "${Protobuf_PROTOC_LIBRARY}")

# generate protobuf files
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS proto/message.proto)
message ("PROTO_SRCS = ${PROTO_SRCS}")
message ("PROTO_HDRS = ${PROTO_HDRS}")

# build main
ADD_EXECUTABLE(main main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(main
    PUBLIC
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(main
    PUBLIC
    ${PROTOBUF_LIBRARIES}
)
