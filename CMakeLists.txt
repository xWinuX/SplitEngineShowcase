cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/Vulkan.cmake)

project(SplitEngineShowcase)

add_executable(SplitEngineShowcase main.cpp)

# add everything in include as an... well... include
target_include_directories(SplitEngineShowcase PRIVATE include)

find_package(SplitEngine CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PRIVATE SplitEngine::SplitEngine)

# Copy all res files to binary folder
file(COPY res DESTINATION "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Compile all shaders
#compile_shader(${PROJECT_NAME}
#        ENV vulkan1.3
#        FORMAT spv
#        SOURCES
#)
