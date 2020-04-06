project(Empaerior CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "Src/Application.cpp"
    "Src/Application.h"
    "Src/Empaerior.h"
    "Src/main.h"
    "Src/pch.cpp"
    "Src/pch.h"
)
source_group("" FILES ${no_group_source_files})

set(assetmanager
    "Src/assetmanager/AssetManager.cpp"
    "Src/assetmanager/AssetManager.h"
)
source_group("assetmanager" FILES ${assetmanager})

set(core
    "Src/core/Point2.h"
    "Src/core/Rect.h"
    "Src/core/Vector2.h"
    "Src/core/unsafe_vector.h"
)
source_group("core" FILES ${core})

set(core__debugging
    "Src/core/debugging/get_data_info.h"
    "Src/core/debugging/Log.cpp"
    "Src/core/debugging/Log.h"
    "Src/core/debugging/v_proffiler.h"
)
source_group("core\\debugging" FILES ${core__debugging})

set(core__defines
    "Src/core/defines/Basic_Defines.h"
    "Src/core/defines/Defines.h"
    "Src/core/defines/Struct_Defines.h"
)
source_group("core\\defines" FILES ${core__defines})

set(core__ecs
    "Src/core/ecs/ECS.h"
    "Src/core/ecs/Entity.h"
)
source_group("core\\ecs" FILES ${core__ecs})

set(core__ecs__components
    "Src/core/ecs/components/ComponentManager.h"
)
source_group("core\\ecs\\components" FILES ${core__ecs__components})

set(core__ecs__system
    "Src/core/ecs/system/system.h"
)
source_group("core\\ecs\\system" FILES ${core__ecs__system})

set(core__exceptions
    "Src/core/exceptions/Exceptions.h"
)
source_group("core\\exceptions" FILES ${core__exceptions})

set(core__utilities
    "Src/core/utilities/Math.h"
    "Src/core/utilities/Timer.cpp"
    "Src/core/utilities/Timer.h"
    "Src/core/utilities/Utilities.cpp"
    "Src/core/utilities/Utilities.h"
)
source_group("core\\utilities" FILES ${core__utilities})

set(input
    "Src/input/input.h"
    "Src/input/keyboard.h"
    "Src/input/mouse.cpp"
    "Src/input/mouse.h"
)
source_group("input" FILES ${input})

set(input__eventhandler
    "Src/input/eventhandler/EventHandler.cpp"
    "Src/input/eventhandler/EventHandler.h"
)
source_group("input\\eventhandler" FILES ${input__eventhandler})

set(rendering
    "Src/rendering/Camera.cpp"
    "Src/rendering/Camera.h"
    "Src/rendering/Window.cpp"
    "Src/rendering/Window.h"
)
source_group("rendering" FILES ${rendering})

set(rendering__SDLwrappers
    "Src/rendering/SDLwrappers/Ptr_Wrappers.h"
    "Src/rendering/SDLwrappers/Rendering_Wrappers.h"
    "Src/rendering/SDLwrappers/SDL_Wrappers.h"
)
source_group("rendering\\SDLwrappers" FILES ${rendering__SDLwrappers})

set(rendering__glyphs
    "Src/rendering/glyphs/Glyphs.cpp"
    "Src/rendering/glyphs/Glyphs.h"
)
source_group("rendering\\glyphs" FILES ${rendering__glyphs})

set(rendering__objects
    "Src/rendering/objects/Sprite.cpp"
    "Src/rendering/objects/Sprite.h"
)
source_group("rendering\\objects" FILES ${rendering__objects})

set(state
    "Src/state/State.cpp"
    "Src/state/State.h"
)
source_group("state" FILES ${state})

set(systems
    "Src/systems/Component.h"
    "Src/systems/Systems.h"
	"Src/systems/Systems.cpp"
)
source_group("systems" FILES ${systems})

set(ALL_FILES
    ${no_group_source_files}
    ${assetmanager}
    ${core}
    ${core__debugging}
    ${core__defines}
    ${core__ecs}
    ${core__ecs__components}
    ${core__ecs__system}
    ${core__exceptions}
    ${core__utilities}
    ${input}
    ${input__eventhandler}
    ${rendering}
    ${rendering__SDLwrappers}
    ${rendering__glyphs}
    ${rendering__objects}
    ${state}
    ${systems}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Empaerior)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "Empaerior"
        TARGET_NAME_DIST    "Empaerior"
        TARGET_NAME_RELEASE "Empaerior"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "Empaerior"
        TARGET_NAME_DIST    "Empaerior"
        TARGET_NAME_RELEASE "Empaerior"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug32-windows-/Empaerior/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist32-windows-/Empaerior/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release32-windows-/Empaerior/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug64-windows-/Empaerior/"
        OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist64-windows-/Empaerior/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release64-windows-/Empaerior/"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_image/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_ttf/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/spdlog/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Src;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_image/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_mixer/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/SDL/SDL2_ttf/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../External_Libraries/spdlog/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "EMPAERIOR_DEBUG"
        ">"
        "$<$<CONFIG:Dist>:"
            "EMPAERIOR_DIST"
        ">"
        "$<$<CONFIG:Release>:"
            "EMPAERIOR_RELEASE"
        ">"
        "_CRT_SECURE_NO_WARNINGS;"
        "EMPAERIOR_WINDOWS;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "EMPAERIOR_DEBUG"
        ">"
        "$<$<CONFIG:Dist>:"
            "EMPAERIOR_DIST"
        ">"
        "$<$<CONFIG:Release>:"
            "EMPAERIOR_RELEASE"
        ">"
        "_CRT_SECURE_NO_WARNINGS;"
        "EMPAERIOR_WINDOWS;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /MD;
                /ZI
            >
            $<$<CONFIG:Dist>:
                /Gm-;
                /Ox;
                /Oi;
                /GF;
                /MD;
                /Gy;
				/Ot;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
                /Gm-;
                /Ox;
                /Oi;
                /GF;
                /MD;
                /Gy;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /MD;
                /ZI
            >
            $<$<CONFIG:Dist>:
                /Gm-;
                /Ox;
                /Oi;
                /GF;
                /MD;
                /Gy;
				/Ot;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
                /Gm-;
                /Ox;
                /Oi;
                /GF;
                /MD;
                /Gy;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Dist>:
                /OPT:REF;
                /OPT:ICF
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Dist>:
                /OPT:REF;
                /OPT:ICF
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()