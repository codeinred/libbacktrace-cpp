cmake_minimum_required(VERSION 3.14)

project(backtrace-cpp LANGUAGES C CXX)

include(cmake/CPM.cmake)

# If successful, LBT_ADDED will be True,
# and LBT_SOURCE_DIR will be set
CPMAddPackage(
    NAME LBT
    GITHUB_REPOSITORY ianlancetaylor/libbacktrace
    GIT_TAG ad106d5fdd5d960bd33fae1c48a351af567fd075
    DOWNLOAD_ONLY True
)


if(NOT LBT_ADDED)
    message(FATAL_ERROR "Unable to obtain libbacktrace")
else()
    message("libbacktrace source dir: ${LBT_SOURCE_DIR}")
endif()

set(LBT_PKG_DIR "${CMAKE_CURRENT_BINARY_DIR}/LBT")

find_program(MAKE NAMES make gmake mingw32-make REQUIRED)

include(ExternalProject)
ExternalProject_Add(
    LBT
    SOURCE_DIR "${LBT_SOURCE_DIR}"
    CONFIGURE_COMMAND
        "${LBT_SOURCE_DIR}/configure"
            --enable-shared
            --with-system-libunwind
            "--prefix=${LBT_PKG_DIR}"
    BUILD_COMMAND ${MAKE})
