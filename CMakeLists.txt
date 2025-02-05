cmake_minimum_required(VERSION 3.0)

include(FetchContent)
find_package(Git REQUIRED)

set(FR_VCPKG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")

FetchContent_Declare(vcpkg-download
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG "2024.07.12"
    SOURCE_DIR ${FR_VCPKG_DIR})
FetchContent_GetProperties(vcpkg-download)
if (NOT vcpkg-download_POPULATED)
    message(STATUS "Fetch vcpkg ...")
    FetchContent_Populate(vcpkg-download)
endif ()

set(VCPKG_BOOTSTRAP_OPTIONS "-disableMetrics")
set(VCPKG_INSTALL_OPTIONS "--no-print-usage")
set(CMAKE_TOOLCHAIN_FILE "${FR_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")
set(ENV{VCPKG_FORCE_DOWNLOADED_BINARIES} ON)


project(foveatedrenderer)

file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE glad_sources glad/src/*.c glad/include/*.h)

add_executable(foveatedrenderer ${sources} ${glad_sources})

target_include_directories(foveatedrenderer PUBLIC src glad/include)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(foveatedrenderer PUBLIC glfw glm::glm spdlog::spdlog)
