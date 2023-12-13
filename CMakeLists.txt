cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/Vulkan.cmake)

project(SplitEngineShowcase)

add_executable(SplitEngineShowcase main.cpp)

# add everything in include as an... well... include
target_include_directories(SplitEngineShowcase PRIVATE include)

set(CMAKE_FIND_DEBUG_MODE 1)

# Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC Vulkan::Vulkan)

# Vulkan Headers
find_package(VulkanHeaders CONFIG)
target_link_libraries(SplitEngineShowcase PUBLIC Vulkan::Headers)

# Vulkan Memory Allocator
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC GPUOpen::VulkanMemoryAllocator)

# SPIRV Cross
find_package(spirv_cross_core CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC spirv-cross-core)

find_package(spirv_cross_glsl CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC spirv-cross-glsl)

find_package(spirv_cross_cpp CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC spirv-cross-cpp)

find_package(spirv_cross_reflect CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC spirv-cross-reflect)

find_package(spirv_cross_util CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC spirv-cross-util)

# IMGUI
find_package(imgui CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC imgui::imgui)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PUBLIC glm::glm)

# SDL 2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase
        PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

# STB
find_package(Stb REQUIRED)
target_include_directories(SplitEngineShowcase PRIVATE ${Stb_INCLUDE_DIR})


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
