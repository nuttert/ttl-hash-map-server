cmake_minimum_required(VERSION 3.5)
set(SUBPROJECT_NAME service)
# create library
add_library(${PROJECT_NAME}_${SUBPROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/service.cpp)

# target_link_libraries(${PROJECT_NAME}_${SUBPROJECT_NAME} server)

# add include directories
target_include_directories(${PROJECT_NAME}_${SUBPROJECT_NAME}
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
                           ${CMAKE_SOURCE_DIR}/modules/value/include
                           ${CMAKE_SOURCE_DIR}/modules/storage-manager/include
                           ${CMAKE_SOURCE_DIR}/modules/worker/include
                           ${CMAKE_SOURCE_DIR}/modules/server/include
                           ${CMAKE_SOURCE_DIR}/modules/key-value-container/include
                           ${CMAKE_SOURCE_DIR}/modules/ttl-manager/include
                           ${CMAKE_SOURCE_DIR}/modules/utils/include
                           ${CMAKE_SOURCE_DIR}/modules/parser/include
)