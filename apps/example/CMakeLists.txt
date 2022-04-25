set(Boost_DEBUG ON)
set(BUILD_TESTING OFF)
set(Boost_USE_MULTITHREADED ON)

IF (WIN32)
    #    Point to Boost by setting BOOST_ROOT variable
    #    cmake -DBOOST_ROOT=C:/local/boost_1_69_0
    #    set(BOOST_ROOT C:/local/boost_1_69_0)
    #    On the windows instance of Github Actions Boost is located here:
    #    cmake -DBOOST_ROOT=C:/hostedtoolcache/windows/Boost/1.69.0
    #    set(BOOST_ROOT C:/hostedtoolcache/windows/Boost/1.69.0)
    add_definitions(/D_WIN32_WINNT=0x0601)
ENDIF()

#find_package(absl CONFIG REQUIRED)
find_package(cli CONFIG REQUIRED)

add_executable(hexworld_client hexworld_clientcli.cpp)
target_include_directories(hexworld_client PUBLIC ../../include)
target_link_libraries(hexworld_client hex_client_lib absl::base absl::flags absl::flags_parse cli::cli)
