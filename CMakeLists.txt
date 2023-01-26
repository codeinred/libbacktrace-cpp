cmake_minimum_required(VERSION 3.14)

project(backtrace-cpp LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

set(LBT_BIN "${CMAKE_CURRENT_BINARY_DIR}/LBT")
set(LBT_STATIC_LIB ${LBT_BIN}/lib/libbacktrace.a)
set(LBT_INCLUDES ${LBT_BIN}/include)

# Ensure that the includes directory exists
file(MAKE_DIRECTORY ${LBT_INCLUDES})

find_program(MAKE NAMES make gmake mingw32-make REQUIRED)

include(ExternalProject)
ExternalProject_Add(
    libbacktrace_ext
    SOURCE_DIR "${LBT_SOURCE_DIR}"
    CONFIGURE_COMMAND
        "${LBT_SOURCE_DIR}/configure"
            --enable-shared
            --with-system-libunwind
            "--prefix=${LBT_BIN}"
    BUILD_COMMAND ${MAKE}
    BUILD_BYPRODUCTS ${LBT_STATIC_LIB})


add_library(libbacktrace STATIC IMPORTED GLOBAL)
add_library(libbacktrace::libbacktrace ALIAS libbacktrace)

add_dependencies(libbacktrace libbacktrace_ext)

set_target_properties(libbacktrace PROPERTIES IMPORTED_LOCATION ${LBT_STATIC_LIB})
set_target_properties(libbacktrace PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${LBT_INCLUDES})

add_executable(main src/main.cpp)
target_link_libraries(main libbacktrace::libbacktrace)
target_compile_options(main PRIVATE -g -fvisibility=hidden)
