
set(MYFIPSTEST_SRC ${CMAKE_CURRENT_LIST_DIR}/cpa_fips_sample_rsa.c  
                   ${ICP_LAC_DIR}/src/common/crypto/sym/nrbg/lac_sym_nrbg_api.c
                   ${CMAKE_CURRENT_LIST_DIR}/cpa_fips_sample_utils.c
                   ${CMAKE_CURRENT_LIST_DIR}/cpa_fips_sample_aes_gcm.c  
                   ${CMAKE_CURRENT_LIST_DIR}/cpa_fips_sample_dsa.c      
                   ${CMAKE_CURRENT_LIST_DIR}/cpa_fips_sample_ecdsa.c  
)

list(APPEND MYFIPSTEST_INC_DIR 
            ${CMAKE_CURRENT_LIST_DIR}
            ${ICP_API_DIR}/include/dc
            ${ICP_API_DIR}/include/lac
)

set(DOEXP_SRC domodexp.c ${MYFIPSTEST_SRC})

add_library(domodexp SHARED ${DOEXP_SRC})
target_include_directories(domodexp PUBLIC ${MYFIPSTEST_INC_DIR})
target_link_directories(domodexp PUBLIC ${ICP_BUILDOUTPUT_PATH})
target_link_libraries(domodexp PUBLIC qat_s usdm_drv_s)
target_link_libraries(domodexp PUBLIC pthread c)

message(STATUS "ICP_BUILDOUTPUT_PATH = ${ICP_BUILDOUTPUT_PATH}")

target_link_libraries(domodexp PUBLIC ${ICP_BUILDOUTPUT_PATH}/libosal.a)
target_link_libraries(domodexp PUBLIC ${ICP_BUILDOUTPUT_PATH}/libadf.a)

message(STATUS "MYFIPSTEST_INC_DIR = ${MYFIPSTEST_INC_DIR}")

add_executable(modexp main.cpp)
#target_include_directories(modexp PUBLIC ${MYFIPSTEST_INC_DIR})
target_link_directories(modexp PUBLIC ${ICP_BUILDOUTPUT_PATH})
target_link_libraries(modexp PUBLIC domodexp)
target_link_libraries(modexp PUBLIC qat_s usdm_drv_s)
target_link_libraries(modexp PUBLIC pthread c)
target_link_libraries(modexp PUBLIC ${ICP_BUILDOUTPUT_PATH}/libosal.a)
target_link_libraries(modexp PUBLIC ${ICP_BUILDOUTPUT_PATH}/libadf.a)
