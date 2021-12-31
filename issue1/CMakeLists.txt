cmake_minimum_required(VERSION 3.13)
project(myfipstest LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX "install") 

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CMakePackageConfigHelpers)

set(ICP_ROOT $ENV{ICP_ROOT})
set(ICP_BUILDOUTPUT_PATH ${ICP_ROOT}/build)
set(ICP_BUILDSYSTEM_PATH ${ICP_ROOT}/quickassist/build_system)
set(ICP_API_DIR ${ICP_ROOT}/quickassist)
set(ICP_LAC_DIR ${ICP_ROOT}/quickassist/lookaside/access_layer)
set(ICP_OASL_DIR ${ICP_ROOT}/quickassist/utilities/oasl)
set(ICP_ADF_DIR ${ICP_ROOT}/quickassist/lookaside/access_layer/src/qat_direct)
set(CMN_ROOT ${ICP_ROOT}/quickassist/utilities/libusdm_drv)

set(MYFIPSTEST_INC_DIR ${ICP_API_DIR}/include
                       ${ICP_LAC_DIR}/include  
                       ${ICP_ADF_DIR}/include
                       ${ICP_OASL_DIR}/src/linux/user_space/include}
                       ${CMN_ROOT} 
)

# Macros for the test case
add_definitions(-DDO_CRYPTO)
add_definitions(-DUSER_SPACE)
add_definitions(-DCPM_LACKS_DRBG)
add_definitions(-DMAX_MR_ROUND=50)
add_definitions(-DLAC_BYTE_ORDER=__LITTLE_ENDIAN) 
add_definitions(-DDISABLE_NUMA_ALLOCATION)
add_compile_definitions(CPM_LACKS_DRBG)

# Compile fips library
add_subdirectory(test2)

