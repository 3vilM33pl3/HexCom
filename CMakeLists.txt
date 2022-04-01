cmake_minimum_required(VERSION 3.16)
project(HexCom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

IF(UNIX AND NOT APPLE)
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
#    set(Boost_NO_SYSTEM_PATHS ON)
#    set(Boost_USE_STATIC_LIBS ON)
#    set(Boost_COMPILER -vc142)
#    set(Boost_ARCHITECTURE -x64)
    # ASM compile fails for 64 bit builds
    set(OPENSSL_NO_ASM ON)
ENDIF()

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

#IF(MSVC)
##    SET(CMAKE_CXX_FLAGS "/EHsc -wd5039 -wd4577")
#    TARGET_COMPILE_OPTIONS(ssl PRIVATE /EHsc -wd5039 -wd4577)
#ENDIF()

set(gRPC_BUILD_GRPC_CPP_PLUGIN ON)
set(gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF)
set(gRPC_BUILD_GRPC_NODE_PLUGIN OFF)
set(gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF)
set(gRPC_BUILD_GRPC_PHP_PLUGIN OFF)
set(gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF)
set(gRPC_BUILD_GRPC_RUBY_PLUGIN  OFF)
set(gRPC)

set(gRPC_USE_PROTO_LITE OFF)

find_package(grpc CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

add_subdirectory(lib)
add_subdirectory(apps/example)

add_custom_target(create_zip COMMAND tar -cvf archive.zip -C ${CMAKE_CURRENT_BINARY_DIR}/hexcom-install/ .)

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
file(MAKE_DIRECTORY ${hexcom_install_dir})

set(HEXCOM_HEADER_FILES
        ${CMAKE_SOURCE_DIR}/include/hex_client.h
        ${CMAKE_SOURCE_DIR}/include/hex_com_state.h
        ${CMAKE_SOURCE_DIR}/include/hex_lib.h
        )

if(WIN32)
    set(HEXCOM_LIBS
            ${CMAKE_CURRENT_BINARY_DIR}/lib/hex_client_lib.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/address_sorting.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/cares/cares/lib/cares.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/crypto.lib 
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/gpr.lib 
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/grpc.lib 
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/grpc++.lib 
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/protobuf/libprotobufd.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/ssl.lib 
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/upb.lib 
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/zlib/zlibstaticd.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/base/absl_base.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/numeric/absl_int128.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/base/absl_raw_logging_internal.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/base/absl_throw_delegate.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/time/absl_time.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/time/absl_time_zone.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/strings/absl_str_format_internal.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/strings/absl_strings_internal.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/strings/absl_strings.lib
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/types/absl_bad_optional_access.lib
            )
    set(UNREAL_PROJECT_DIR F:/Unreal/HexWorld/)
    set(UNREAL_PLATFORM Win64)
    
elseif(UNIX)
    set(HEXCOM_LIBS
            ${CMAKE_CURRENT_BINARY_DIR}/lib/libhex_client_lib.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/protobuf/libprotobuf.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgrpc++.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgrpc.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libgpr.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libaddress_sorting.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/libssl.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/boringssl-with-bazel/libcrypto.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/libupb.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/zlib/libz.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/cares/cares/lib/libcares.a
            ${CMAKE_CURRENT_BINARY_DIR}/_deps/grpc-build/third_party/abseil-cpp/absl/base/*.a)

    set(UNREAL_PROJECT_DIR /home/olivier/Projects/UnrealProjects/HexWorld)
    set(UNREAL_PLATFORM Linux)
endif()

add_custom_target(copy_ue4)
add_custom_target(copy_files)
add_custom_target(copy_headers)

add_dependencies(copy_ue4 copy_headers)
add_dependencies(copy_headers hex_client_lib)
add_dependencies(copy_files hex_client_lib)

# do the copying
foreach( file_i ${HEXCOM_LIBS})
    add_custom_command(
            TARGET copy_files
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} ${hexcom_install_dir}
    )
endforeach( file_i )

foreach( file_i ${HEXCOM_LIBS})
    add_custom_command(
            TARGET copy_ue4
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} ${UNREAL_PROJECT_DIR}Plugins/HexWorldCreator/Source/ThirdParty/HexWorldCreatorLibrary/${UNREAL_PLATFORM}/Release/
    )
endforeach( file_i )

foreach( file_i ${HEXCOM_INCLUDE_FILES})
    add_custom_command(
            TARGET copy_headers
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} ${UNREAL_PROJECT_DIR}Plugins/HexWorldCreator/Source/ThirdParty/HexWorldCreatorLibrary/include/hexworld/
    )
endforeach( file_i )

set(MY_DEPENDENCY_PATHS ./lib)
#
## Transfer the value of ${MY_DEPENDENCY_PATHS} into the install script
install(CODE "set(MY_DEPENDENCY_PATHS \"${MY_DEPENDENCY_PATHS}\")")

install(CODE [[
  file(GET_RUNTIME_DEPENDENCIES
    LIBRARIES $<TARGET_FILE:hex_client_lib>
    EXECUTABLES $<TARGET_FILE:hexworld_client>
    RESOLVED_DEPENDENCIES_VAR _r_deps
    UNRESOLVED_DEPENDENCIES_VAR _u_deps
#    DIRECTORIES ${MY_DEPENDENCY_PATHS}
  )
  foreach(_file ${_r_deps})
    file(INSTALL
      DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
      TYPE SHARED_LIBRARY
      FOLLOW_SYMLINK_CHAIN
      FILES "${_file}"
    )
  endforeach()
  list(LENGTH _u_deps _u_length)
  if("${_u_length}" GREATER 0)
    message(WARNING "Unresolved dependencies detected!")
  endif()
  foreach (lib_conflict ${_u_deps})
    message(STATUS "${lib_conflict} found at: ${conflicts_${lib_conflict}}")
  endforeach()
]] DESTINATION ${hexcom_install_dir})