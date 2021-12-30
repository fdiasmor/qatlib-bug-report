cmake_minimum_required(VERSION 3.13)
project(myfipstest LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CMakePackageConfigHelpers)

set(TEST_INC_DIR ${CMAKE_CURRENT_LIST_DIR})

set(ICP_ROOT $ENV{ICP_ROOT})
set(ICP_BUILDOUTPUT_PATH ${ICP_ROOT}/build)
#set(ICP_BUILDSYSTEM_PATH ${ICP_ROOT}/quickassist/build_system)
set(ICP_API_DIR ${ICP_ROOT}/quickassist)
#set(ICP_LAC_DIR ${ICP_ROOT}/quickassist/lookaside/access_layer)
#set(ICP_OSAL_DIR ${ICP_ROOT}/quickassist/utilities/oasl)
#set(ICP_ADF_DIR ${ICP_ROOT}/quickassist/lookaside/access_layer/src/qat_direct)
#set(CMN_ROOT ${ICP_ROOT}/quickassist/utilities/libusdm_drv)

#set(QAT_FW_API_DIR ${ICP_ROOT}/quickassist/lookaside/firmware/include/)
#set(COMMON_FW_API_DIR ${ICP_ROOT}/quickassist/lookaside/firmware/common/include/)
#set(ME_ACCESS_LAYER_CMN_API_DIR ${ICP_ROOT}/quickassist/lookaside/firmware/common/include/)
#set(ADF_CMN_DIR $(ICP_ROOT)/quickassist/lookaside/access_layer/include)

set(TEST_INC_DIR ${ICP_API_DIR}/include
                 #${ICP_LAC_DIR}/include  
                 #${ICP_ADF_DIR}/include
                 #${CMN_ROOT} 
)

# Macros for the test case
#add_definitions(-DDO_CRYPTO)
#add_definitions(-DUSER_SPACE)
#add_compile_definitions(CPM_LACKS_DRBG)

add_subdirectory(test)

