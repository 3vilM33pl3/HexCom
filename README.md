
Hexcom is the client library which can be used to communicate with the [`hexcloud`](https://github.com/3vilM33pl3/hexcloud) backend.

# VCPKG

`vcpkg install grpc --triplet x64-windows`

`vcpkg install protobuf --triplet x64-windows`

`vcpkg install boost --triplet x64-windows`


## Compile
### Windows
Make sure your toolchain is configured for 64 bit builds. 
#### BOOST
Install Boost with the Windows installer found [here](https://sourceforge.net/projects/boost/files/boost-binaries/1.69.0/).
(Download `boost_1_69_0-msvc-14.1-64.exe` for 64 bit builds) 

Point to Boost by setting BOOST_ROOT variable:

    cmake -DBOOST_ROOT=C:/local/boost_1_69_0

On the windows instance of Github Actions Boost is located 

    C:/hostedtoolcache/windows/Boost/1.69.0

Run cmake with:

    cmake -DBOOST_ROOT=C:/hostedtoolcache/windows/Boost/1.69.0

#### Ninja (Optional but recommended)
Ninja dramatically accelerates building c++ programs. 

The easiest way to install Ninja is with [Chocolatey](https://chocolatey.org/) the package manager for Windows.
After installing Chocolatey run this command in Powershell (run as Administrator):

    choco install ninja
    
Run CMake like this to enable Ninja:
```shell
cmake -GNinja -DCMAKE_BUILD_TYPE=Release
      -DCMAKE_C_COMPILER="cl.exe"
      -DCMAKE_CXX_COMPILER="cl.exe"
      -DBOOST_ROOT=C:/local/boost_1_69_0    
```

#### gRPC
In case gRPC doesn't compile you possibly have to point to a valid root certificate. 
To do this set an environment variable pointing to the root certificate included in the project.
This roots.pem is a generic certificate file included with most browsers.      
```shell 
GRPC_DEFAULT_SSL_ROOTS_FILE_PATH=C:/Projects/hexcom/roots.pem
```      

#### install YASM (Optional)
The build is configured with ` set(OPENSSL_NO_ASM ON)` because the 64bit compile fails to compile the 
assembly code in boringssl. In case you want to enable ASM you will have to install YASM.

Installing [Yasm](https://yasm.tortall.net/) is needed so `boringssl` dependency can compile.
The easiest way to install is with [Chocolatey](https://chocolatey.org/) the package manager for Windows.
After installing Chocolatey run this command in Powershell (run as Administrator):

    choco install yasm    

## Run
    hexworld_client --address [backend address]