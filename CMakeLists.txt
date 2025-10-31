cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(DisableGlow VERSION 1.0.0)

# Add all source files inside src (recursively)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Set up the mod binary
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# --- FIXED SECTION ---
# Prefer the CMake variable if provided, fallback to environment variable
if (DEFINED GEODE_SDK)
    set(GEODE_SDK_PATH "${GEODE_SDK}")
elseif(DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK_PATH "$ENV{GEODE_SDK}")
else()
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK (or set environment variable GEODE_SDK).")
endif()

message(STATUS "Using Geode SDK at: ${GEODE_SDK_PATH}")
# ---------------------

# Add the Geode SDK
add_subdirectory(${GEODE_SDK_PATH} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Set up dependencies, resources, and link Geode.
setup_geode_mod(${PROJECT_NAME})