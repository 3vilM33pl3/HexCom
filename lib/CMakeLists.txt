
get_filename_component(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/protos/hexagon_world.proto ABSOLUTE)
get_filename_component(PROTO_PATH "${PROTO_FILE}" PATH)

set(PROTOBUF_LIBRARY libprotobuf-lite)
set(GRPC_GRPCPP_LIBRARY grpc++)

set(PROTOC_EXECUTABLE $<TARGET_FILE:protoc>)
set(GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

set(PROTOBUF_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/hexagon_world.pb.cc")
set(PROTOBUF_HEADER "${CMAKE_CURRENT_BINARY_DIR}/hexagon_world.pb.h")
set(GRPC_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/hexagon_world.grpc.pb.cc")
set(GRPC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/hexagon_wprld.grpc.pb.h")

add_custom_command(
        OUTPUT "${PROTOBUF_SOURCE}" "${PROTOBUF_HEADER}" "${GRPC_SOURCE}" "${GRPC_HEADER}"
        COMMAND ${PROTOC_EXECUTABLE}
        ARGS --grpc_out="${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out="${CMAKE_CURRENT_BINARY_DIR}"
        -I "${PROTO_PATH}"
        --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${PROTO_FILE}"
        DEPENDS "${PROTO_FILE}")


add_library(hex_client_lib STATIC hex_client.cpp hex_client_impl.cpp hex_client_impl.h ${PROTOBUF_SOURCE} ${GRPC_SOURCE})
target_include_directories(hex_client_lib PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(hex_client_lib PUBLIC ../include)

target_link_libraries(hex_client_lib ${GRPC_GRPCPP_LIBRARY} ${PROTOBUF_LIBRARY})
