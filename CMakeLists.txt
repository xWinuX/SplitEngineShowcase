cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(SplitEngineShowcase)

add_executable(
        SplitEngineShowcase
        main.cpp
        src/Systems/SpriteRendering.cpp
        include/SplitEngineShowcase/System/SpriteRendering.hpp
        include/SplitEngineShowcase/Component/Transform.hpp
        include/SplitEngineShowcase/Component/Sprite.hpp
        include/SplitEngineShowcase/Component/Player.hpp
        include/SplitEngineShowcase/Component/Camera.hpp
        src/Systems/Camera.cpp
        include/SplitEngineShowcase/System/Camera.hpp
        src/Systems/PlayerController.cpp
        include/SplitEngineShowcase/System/PlayerController.hpp
        include/SplitEngineShowcase/Component/Physics.hpp
        src/Systems/Physics.cpp
        include/SplitEngineShowcase/System/Physics.hpp
        include/SplitEngineShowcase/Component/AudioSource.hpp
        src/Systems/AudioSourcePlayer.cpp
        include/SplitEngineShowcase/System/AudioSourcePlayer.hpp
        include/SplitEngineShowcase/Assets.hpp
)

target_include_directories(SplitEngineShowcase PRIVATE include)

find_package(SplitEngine CONFIG REQUIRED)
target_link_libraries(SplitEngineShowcase PRIVATE SplitEngine::SplitEngine)

add_custom_command(TARGET SplitEngineShowcase POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:SplitEngineShowcase>/res)

add_custom_target(CopyResources ALL DEPENDS ${CMAKE_SOURCE_DIR}/res)

set(SHADER_FILES
        "res/shaders/debug/Debug.vert"
        "res/shaders/debug/Debug.frag"
)

find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

foreach (SHADER_FILE ${SHADER_FILES})
    set(SPIRV_OUTPUT $<TARGET_FILE_DIR:SplitEngineShowcase>/${SHADER_FILE}.spv)

    add_custom_command(TARGET SplitEngineShowcase POST_BUILD
            COMMAND ${glslc_executable}
            -o ${SPIRV_OUTPUT}
            $<TARGET_FILE_DIR:SplitEngineShowcase>/${SHADER_FILE}
            DEPENDS ${CMAKE_SOURCE_DIR}/${SHADER_FILE}
            RESULT_VARIABLE glslang_result
            OUTPUT_VARIABLE glslang_output
            ERROR_VARIABLE glslang_error
            COMMENT "Compiling ${SHADER_FILE} to SPIR-V")

    if (NOT ${glslang_result} EQUAL 0)
        message(FATAL_ERROR "Error compiling ${SHADER_NAME}: ${glslang_output}\n${glslang_error}")
    endif ()

    list(APPEND SPIRV_OUTPUTS ${SPIRV_OUTPUT})
endforeach ()

add_custom_target(CompileShaders ALL DEPENDS ${SPIRV_OUTPUTS})
