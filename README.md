## Compile
### Windows

Point to Boost by setting BOOST_ROOT variable:

    cmake -DBOOST_ROOT=C:/local/boost_1_69_0

On the windows instance of Github Actions Boost is located 

    C:/hostedtoolcache/windows/Boost/1.69.0

Run cmake with:

    cmake -DBOOST_ROOT=C:/hostedtoolcache/windows/Boost/1.69.0
    
CMake options
```shell script
cmake -GNinja -DCMAKE_BUILD_TYPE=Release
      -DCMAKE_C_COMPILER="cl.exe"
      -DCMAKE_CXX_COMPILER="cl.exe"
      -DBOOST_ROOT=C:/local/boost_1_69_0
```
Environment variable to make gRPC compile. roots.pem is a generic certificate file included in most browser      
```shell script
GRPC_DEFAULT_SSL_ROOTS_FILE_PATH=F:/Projects/Narrowboat/hexcom/roots.pem
```      

## Run
    hexworld_client --address [backend address]