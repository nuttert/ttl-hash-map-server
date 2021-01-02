cmake_minimum_required(VERSION 3.5)
set(SUBPROJECT_NAME storage-manager)
# create library
add_library(${PROJECT_NAME}_${SUBPROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/storage-manager.cpp)




# add include directories
target_include_directories(${PROJECT_NAME}_${SUBPROJECT_NAME}
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
                           ${CMAKE_SOURCE_DIR}/modules/utils/include
                           ${CMAKE_SOURCE_DIR}/modules/value/include
)