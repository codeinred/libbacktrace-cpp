# backtrace-cpp: A light wrapper around libbacktrace

This project provides a light wrapper around [libbacktrace] for easier consumption
and use of the library.

[libbacktrace]: https://github.com/ianlancetaylor/libbacktrace

## autotools / cmake

This project uses CMake, but libbacktrace requires autotools. The following
resources may be of interest

- https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=libbacktrace-git
- https://www.scivision.dev/cmake-external-project-autotools/
- https://stackoverflow.com/questions/5971921/building-a-library-using-autotools-from-cmake
- This particular answer: https://stackoverflow.com/a/59025724
- [CMake ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html)
