cmake_minimum_required(VERSION 3.16)
project(HexCom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

IF(UNIX)
    find_package(LLVM 9.0 REQUIRED CONFIG)
    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
    include_directories(${LLVM_INCLUDE_DIRS})
    add_definitions(${LLVM_DEFINITIONS})
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
ENDIF()

IF (WIN32)
    #    Point to Boost by setting BOOST_ROOT variable
    #    cmake -DBOOST_ROOT=C:/local/boost_1_69_0
    #    set(BOOST_ROOT C:/local/boost_1_69_0)
    #    On the windows instance of Github Actions Boost is located here:
    #    cmake -DBOOST_ROOT=C:/hostedtoolcache/windows/Boost/1.69.0
    #    set(BOOST_ROOT C:/hostedtoolcache/windows/Boost/1.69.0)
    add_definitions(/D_WIN32_WINNT=0x0601)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_COMPILER -vc141)
    set(Boost_ARCHITECTURE -x64)
ENDIF()

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

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
