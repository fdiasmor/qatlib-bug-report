
list(APPEND TEST_INC_DIR 
            ${CMAKE_CURRENT_LIST_DIR}
#            ${ICP_API_DIR}/include/dc
#            ${ICP_API_DIR}/include/lac
)

add_executable(test main.cpp)
target_include_directories(test PUBLIC ${TEST_INC_DIR})
target_link_directories(test PUBLIC ${ICP_BUILDOUTPUT_PATH}/)
target_link_libraries(test PUBLIC qat_s c pthread)
target_link_libraries(test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../build/linux_2.6/user_space/fips_sample_s.so)

