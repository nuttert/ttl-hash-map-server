cmake_minimum_required(VERSION 3.5)
set(SUBPROJECT_NAME value)
# create library
add_library(${PROJECT_NAME}_${SUBPROJECT_NAME} STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/value.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/time-model.cpp
)

find_package(nlohmann_json 3.7.0 REQUIRED)
target_link_libraries(${PROJECT_NAME}_${SUBPROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# add include directories
target_include_directories(${PROJECT_NAME}_${SUBPROJECT_NAME}
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
)