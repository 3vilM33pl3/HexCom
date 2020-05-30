cmake_minimum_required(VERSION 3.16)
project(HexCom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

# if linux
#set(CMAKE_C_COMPILER /usr/bin/clang-9)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++-9)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi ")

#set(CMAKE_THREAD_LIBS_INIT "-lpthread")
#set(CMAKE_HAVE_THREADS_LIBRARY 1)
#set(CMAKE_USE_WIN32_THREADS_INIT 0)
#set(CMAKE_USE_PTHREADS_INIT 1)
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#set(protobuf_VERBOSE ON)

find_package(LLVM 9.0 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG        v1.29.1)
FetchContent_MakeAvailable(grpc)

IF(MSVC)
#    SET(CMAKE_CXX_FLAGS "/EHsc -wd5039 -wd4577")
    TARGET_COMPILE_OPTIONS(ssl PRIVATE /EHsc -wd5039 -wd4577)
ENDIF()

set(gRPC_BUILD_GRPC_CPP_PLUGIN ON)
set(gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF)
set(gRPC_BUILD_GRPC_NODE_PLUGIN OFF)
set(gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF)
set(gRPC_BUILD_GRPC_PHP_PLUGIN OFF)
set(gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF)
set(gRPC_BUILD_GRPC_RUBY_PLUGIN  OFF)
set(gRPC)

set(gRPC_USE_PROTO_LITE OFF)

add_subdirectory(lib)
add_subdirectory(apps/example)

add_custom_target(create_zip
        COMMAND tar -cvf archive.zip -C ${CMAKE_CURRENT_BINARY_DIR}/hexcom-install/ .
        )

#install(FILES
#        ${CMAKE_CURRENT_BINARY_DIR}/lib/libhex_client_lib.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/protobuf/libprotobuf.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgrpc++.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgrpc.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgpr.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libaddress_sorting.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/libssl.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/libcrypto.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libupb.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/zlib/libz.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/cares/cares/lib/libcares.a
#        ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/base/*.
#        DESTINATION
#        ${CMAKE_CURRENT_BINARY_DIR}/hexcom-install/)

set(hexcom_install_dir ${CMAKE_CURRENT_BINARY_DIR}/../hexcom-install/)

add_custom_target(copy_files ALL
        COMMAND mkdir -p ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/lib/libhex_client_lib.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/protobuf/libprotobuf.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgrpc++.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgrpc.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgpr.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libaddress_sorting.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/libssl.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/libcrypto.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libupb.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/zlib/libz.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/cares/cares/lib/libcares.a ${hexcom_install_dir}
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/base/*.a ${hexcom_install_dir})

add_custom_target(copy_ue4 ALL
        COMMAND cp ${hexcom_install_dir}lib*.a /home/olivier/Projects/UnrealProjects/HexWorld/Plugins/HexWorldCreator/Source/ThirdParty/HexWorldCreatorLibrary/Linux/Release/)

add_dependencies(create_zip copy_files)
add_dependencies(copy_files hex_client_lib)
add_dependencies(copy_ue4 copy_files)
