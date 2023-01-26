cmake_minimum_required(VERSION 3.14)

project(backtrace-cpp LANGUAGES C CXX)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME libbacktrace
    GITHUB_REPOSITORY ianlancetaylor/libbacktrace
    GIT_TAG ad106d5fdd5d960bd33fae1c48a351af567fd075
    DOWNLOAD_ONLY True
)

if(libbacktrace_ADDED)
    message("Library added!")
    message("Source dir: ${libbacktrace_SOURCE_DIR}")
endif()
