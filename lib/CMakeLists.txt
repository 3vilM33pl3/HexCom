
get_filename_component(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/protos/hexagon.proto ABSOLUTE)
get_filename_component(PROTO_PATH "${PROTO_FILE}" PATH)

set(PROTOBUF_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/hexagon.pb.cc")
set(PROTOBUF_HEADER "${CMAKE_CURRENT_BINARY_DIR}/hexagon.pb.h")
set(GRPC_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/hexagon.grpc.pb.cc")
set(GRPC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/hexagon.grpc.pb.h")

add_custom_command(
        OUTPUT "${PROTOBUF_SOURCE}" "${PROTOBUF_HEADER}" "${GRPC_SOURCE}" "${GRPC_HEADER}"
        COMMAND protobuf::protoc
        ARGS --grpc_out="${CMAKE_CURRENT_BINARY_DIR}"
        --descriptor_set_out=api_descriptor.pb
        --cpp_out="${CMAKE_CURRENT_BINARY_DIR}"
        -I "${PROTO_PATH}"
        --plugin=protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin>
        "${PROTO_FILE}"
        DEPENDS "${PROTO_FILE}")


add_library(hex_client_lib STATIC hex_client.cpp hex_client_impl.cpp hex_client_impl.h ${PROTOBUF_SOURCE} ${GRPC_SOURCE})
target_include_directories(hex_client_lib PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(hex_client_lib PUBLIC ../include)

target_link_libraries(hex_client_lib PRIVATE grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite ${llvm_libs})

