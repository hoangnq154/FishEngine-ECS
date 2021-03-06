cmake_minimum_required(VERSION 3.9)
project(FishEngine-ECS)
set(CMAKE_CXX_STANDARD 17)

# Output
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# glfw
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(./ThirdParty/glfw/)
include_directories(./ThirdParty/glfw/include)
SET_TARGET_PROPERTIES(glfw PROPERTIES FOLDER "ThirdParty")


# # nVidia PhysX
# if (MSVC)
#     SET( PhysX_ROOT_DIR "D:\\library\\PhysX-3.4-master\\PhysX_3.4" )
# else()
#     SET( PhysX_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/Physx-3.4/PhysX_3.4 )
# endif()
# include_directories( ${PhysX_ROOT_DIR}/Include )
# include_directories( ${PhysX_ROOT_DIR}/../PxShared/include )
# include_directories( ${PhysX_ROOT_DIR}/Snippets )
# if (NOT EXISTS ${PhysX_ROOT_DIR}/Include/PxPhysicsAPI.h)
#     message(FATAL_ERROR "Physx not found")
# endif()
# # if (MSVC)
# #     FILE(GLOB PhysXSDK_LIBRARIES_DEBUG ${PhysX_ROOT_DIR}/Lib/vc15win64/*DEBUG*lib ${PhysX_ROOT_DIR}/../PxShared/lib/vc15win64/*DEBUG*lib)
# #     FILE(GLOB PhysXSDK_LIBRARIES_CHECKED ${PhysX_ROOT_DIR}/Lib/vc15win64/*CHECKED*lib ${PhysX_ROOT_DIR}/../PxShared/lib/vc15win64/*CHECKED*lib)
# #     SET(PhysXSDK_LIBRARIES optimized ${PhysXSDK_LIBRARIES_CHECKED} debug ${PhysXSDK_LIBRARIES_DEBUG})
# # else()
# #     FILE(GLOB PhysXSDK_LIBRARIES ${PhysX_ROOT_DIR}/Lib/osx64/*.a ${PhysX_ROOT_DIR}/../PxShared/lib/osx64/*.a)
# # endif()
# if (MSVC)
#     # PhysXSDK
#     # set(PhysX_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/PhysXSDK)
#     set(PhysXSDK_LIBRARIES_DIR "D:\\program\\FishEngine-Experiment\\ThirdParty\\PhysX-3.4\\PhysX_3.4\\Lib\\vc15win64")
#     set(PhysXSDK_LIBRARIES "")
#     foreach(x PhysX3 PhysX3Common PxPvdSDK PxFoundation)
#         set(lib1 ${PhysXSDK_LIBRARIES_DIR}/${x}DEBUG_x64.lib)
#         set(lib2 ${PhysXSDK_LIBRARIES_DIR}/${x}CHECKED_x64.lib)
#         IF(NOT EXISTS ${lib1})
#             message(FATAL_ERROR "physx root directory does not exist: ${lib1}")
#         endif ()
#         IF(NOT EXISTS ${lib2})
#             message(FATAL_ERROR "physx root directory does not exist: ${lib2}")
#         endif ()
#         list (APPEND PhysXSDK_LIBRARIES debug ${lib1} optimized ${lib2})
#     endforeach()
#     foreach(x PhysX3Extensions)
#         set(lib1 ${PhysXSDK_LIBRARIES_DIR}/${x}DEBUG.lib)
#         set(lib2 ${PhysXSDK_LIBRARIES_DIR}/${x}CHECKED.lib)
#         IF(NOT EXISTS ${lib1})
#             message(FATAL_ERROR "physx root directory does not exist: ${lib1}")
#         endif ()
#         IF(NOT EXISTS ${lib2})
#             message(FATAL_ERROR "physx root directory does not exist: ${lib2}")
#         endif ()
#         list (APPEND PhysXSDK_LIBRARIES debug ${lib1} optimized ${lib2})
#     endforeach()
# else()
#     # FILE(GLOB PhysXSDK_LIBRARIES ./ThirdParty/Physx-3.4/Lib/osx64/*.a)
#     FILE(GLOB PhysXSDK_LIBRARIES ${PhysX_ROOT_DIR}/Lib/osx64/*.a ${PhysX_ROOT_DIR}/../PxShared/lib/osx64/*.a)
# endif()
# #message("PhysXSDK_LIBRARIES" ${PhysXSDK_LIBRARIES})


macro(AutoGroup root_dir)
	foreach(group ${ARGN})
		file(GLOB_RECURSE files ${root_dir}/${group}/*.hpp ${root_dir}/${group}/*.inl ${root_dir}/${group}/*.cpp)
		source_group(${group} FILES ${files})
	endforeach(group)
endmacro()


# # glm
# include_directories(./ThirdParty/glm)
# #FishGUI
# SET(FishGUI_DIR ../FishGUI)
# SET(FishGUI_INCLUDE_DIR ${FishGUI_DIR}/include)
# SET(FishGUI_SRC_DIR ${FishGUI_DIR}/src)
# # aux_source_directory(${FishGUI_SRC_DIR} SRCS)
# file(GLOB_RECURSE SRCS ${FishGUI_SRC_DIR}/*.cpp)
# FILE(GLOB_RECURSE HEADERS ${FishGUI_DIR}/include/FishGUI/*.hpp)
# include_directories( ${FishGUI_INCLUDE_DIR} )
# # set(FishGUI_EXTENSION_DIR ${FishGUI_DIR}/examples/common)
# # include_directories(${FishGUI_EXTENSION_DIR})
# # FILE(GLOB_RECURSE EXTENSIONS ${FishGUI_EXTENSION_DIR}/*.hpp ${FishGUI_EXTENSION_DIR}/*.cpp)
# # source_group("extensions" FILES ${EXTENSIONS})
# add_library(FishGUI ${SRCS} ${HEADERS})


file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Include/FishEngine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Include/FishEngine/*.hpp 
    ${CMAKE_CURRENT_LIST_DIR}/Include/FishEngine/*.inl)
file(GLOB_RECURSE SRCS 
    ${CMAKE_CURRENT_LIST_DIR}/Source/FishEngine/*.cpp)
add_library(FishEngine ${HEADERS} ${SRCS})


file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Include/FishEditor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Include/FishEditor/*.hpp)
file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_LIST_DIR}/Source/FishEditor/*.cpp)
add_library(FishEditor ${HEADERS} ${SRCS})


AutoGroup(./Include/FishEngine Math Systems Components ECS Render)
AutoGroup(./Source/FishEngine Math Systems Components)

include_directories("./ThirdParty/tinygltf")
include_directories("./ThirdParty/bgfx/include")
include_directories("./ThirdParty/bimg/include")
include_directories("./ThirdParty/bx/include")
include_directories("./ThirdParty/bgfx/3rdparty")
include_directories("./ThirdParty/bgfx/examples/common")
if (MSVC)
    include_directories("./ThirdParty/bx/include/compat/msvc")
endif()


file(GLOB_RECURSE IMGUI_HEADERS "./ThirdParty/bgfx/3rdparty/dear-imgui/*.h" "./ThirdParty/bgfx/examples/common/imgui/*.h")
file(GLOB_RECURSE IMGUI_SRCS "./ThirdParty/bgfx/3rdparty/dear-imgui/*.cpp" "./ThirdParty/bgfx/examples/common/imgui/*.cpp")
add_library(imgui ${IMGUI_HEADERS} ${IMGUI_SRCS})
SET_TARGET_PROPERTIES(imgui PROPERTIES FOLDER "ThirdParty")


target_link_libraries(FishEngine glfw)
target_link_libraries(FishEngine imgui)
target_link_libraries(FishEditor FishEngine)

if (MSVC)
	target_compile_definitions(FishEngine PRIVATE _ITERATOR_DEBUG_LEVEL=0)
    target_compile_definitions(FishEditor PRIVATE _ITERATOR_DEBUG_LEVEL=0)
	set(BGFX_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/ThirdParty/bgfx/.build/win64_vs2017/bin")
else()
    target_compile_definitions(FishEngine PRIVATE BGFX_CONFIG_RENDERER_OPENGL=410)
	set_target_properties(FishEngine PROPERTIES LINK_FLAGS "-framework OpenGL -framework Cocoa -framework metal -framework QuartzCore")
	set(BGFX_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/ThirdParty/bgfx/.build/osx64_clang/bin")
endif()

set(BGFX_LIBRARIES "")
foreach(x bgfx bx bimg bimg_decode)
    if (MSVC)
        set(lib1 ${BGFX_LIB_DIR}/${x}Debug.lib)
        set(lib2 ${BGFX_LIB_DIR}/${x}Release.lib)
    else()
        set(lib1 ${BGFX_LIB_DIR}/lib${x}Debug.a)
        set(lib2 ${BGFX_LIB_DIR}/lib${x}Release.a)
    endif()
    IF(NOT EXISTS ${lib1})
        message(FATAL_ERROR "bgfx lib not found: ${lib1}")
    endif ()
    IF(NOT EXISTS ${lib2})
        message(FATAL_ERROR "bgfx lib not found: ${lib2}")
    endif ()
    list (APPEND BGFX_LIBRARIES debug ${lib1} optimized ${lib2})
endforeach(x)
target_link_libraries(FishEngine ${BGFX_LIBRARIES})

include_directories("./Include")

add_executable(demo1 "./Examples/demo1.cpp")
target_link_libraries(demo1 FishEngine)

add_executable(demo2 "./Examples/demo2.cpp")
target_link_libraries(demo2 FishEngine)

add_executable(Editor MACOSX_BUNDLE "./Examples/model_viewer.cpp")
target_link_libraries(Editor FishEditor)

if (MSVC)
	target_compile_definitions(imgui PRIVATE _ITERATOR_DEBUG_LEVEL=0)
    target_compile_definitions(demo1 PRIVATE _ITERATOR_DEBUG_LEVEL=0)
    target_compile_definitions(demo2 PRIVATE _ITERATOR_DEBUG_LEVEL=0)
    target_compile_definitions(Editor PRIVATE _ITERATOR_DEBUG_LEVEL=0)
else()
    target_compile_definitions(demo1 PRIVATE BGFX_CONFIG_RENDERER_OPENGL=410)
    target_compile_definitions(imgui PRIVATE BGFX_CONFIG_RENDERER_OPENGL=410)
    target_compile_definitions(demo2 PRIVATE BGFX_CONFIG_RENDERER_OPENGL=410)
    target_compile_definitions(Editor PRIVATE BGFX_CONFIG_RENDERER_OPENGL=410)
    set_target_properties(demo1 PROPERTIES LINK_FLAGS "-framework OpenGL -framework Cocoa -framework metal -framework QuartzCore")
    set_target_properties(demo2 PROPERTIES LINK_FLAGS "-framework OpenGL -framework Cocoa -framework metal -framework QuartzCore")
    set_target_properties(Editor PROPERTIES LINK_FLAGS "-framework OpenGL -framework Cocoa -framework metal -framework QuartzCore")

    SET( INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/MacOSXBundleInfo.plist.in)
    IF (NOT EXISTS ${INFO_PLIST})
        MESSAGE(FATAL_ERROR "${INFO_PLIST} not found!")
    ENDIF()
    set_target_properties(Editor PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${INFO_PLIST}" )
endif()
