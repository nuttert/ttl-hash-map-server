cmake_minimum_required(VERSION 3.5)
project(${PROJECT_NAME})

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++20
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED) 
find_package(Boost 1.67 REQUIRED)

if(${TEST_MODE})
  add_executable(
    ${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/test/main.cpp
  )
else()
  add_executable(
    ${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/main.cpp
  )
endif()

add_subdirectory(modules/utils)
add_subdirectory(modules/parser)
add_subdirectory(modules/worker)
add_subdirectory(modules/value)
add_subdirectory(modules/storage-manager)
add_subdirectory(modules/ttl-manager)
add_subdirectory(modules/key-value-container)
add_subdirectory(modules/server)
add_subdirectory(modules/main_service)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${GTEST_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${Threads_INCLUDE_DIR}
)


  

target_link_libraries(${PROJECT_NAME} 
    ${GTEST_BOTH_LIBRARIES} 
    ${Boost_BOTH_LIBRARIES} 
    ${PROJECT_NAME}_service
    ${PROJECT_NAME}_server
    ${PROJECT_NAME}_key-value-container
    ${PROJECT_NAME}_ttl-manager
    ${PROJECT_NAME}_storage-manager
    ${PROJECT_NAME}_value
    ${PROJECT_NAME}_worker
    ${PROJECT_NAME}_parser
    Threads::Threads 
    evpp
)