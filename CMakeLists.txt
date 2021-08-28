# Copyright (c) 2021 The kOS authors.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software.
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.0.0)
project(kOS VERSION 1.0.0)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

if(NOT ${CMAKE_ASM_COMPILER_ID} STREQUAL "Clang" OR NOT ${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(FATAL_ERROR "kOS does not support GCC, MSVC and other compilers other than LLVM.")
endif()

add_compile_options(--target=i386-unknown -m32 -fPIC)

string(REGEX MATCH "Windows-?" MATCHED ${CMAKE_HOST_SYSTEM})
if(MATCHED)
    find_program(LD_LLD NAMES ld.lld REQUIRED)
    set(CMAKE_C_LINK_EXECUTABLE "\"${LD_LLD}\" <OBJECTS> -o <TARGET> <LINK_LIBRARIES> <LINK_FLAGS>")
else()
    add_link_options(-fuse-ld=lld)
    add_link_options(--target=i386-pc-none)
endif()

add_subdirectory(libc)
add_subdirectory(Kernel)
