cmake_minimum_required (VERSION 3.13...3.21)

set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(
    Unamed_Projects  # Project name, change this as needed.
    LANGUAGES C CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")  # Keep all runtime files in one directory.

file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS  # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
file(
    GLOB_RECURSE HEADER_FILES
    CONFIGURE_DEPENDS  # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.hpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Ensure the C++17 standard is available.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enforce UTF-8 encoding on MSVC.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()
set(CMAKE_DEBUG_FIND_MODE 1)

find_package(raylib CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${raylib_INCLUDE_DIRS} PUBLIC ${PROJECT_SOURCE_DIR}/src/)

target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
set(IMPORTED_IMPLIB 1)