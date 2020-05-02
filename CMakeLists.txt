cmake_minimum_required(VERSION 3.16)
project(HexCom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

include(FetchContent)

FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG        v1.27.3)
FetchContent_MakeAvailable(grpc)

IF (WIN32)
    add_definitions(/D_WIN32_WINNT=0x0601)
    set(INSTALL_PREFIX )
ENDIF()

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