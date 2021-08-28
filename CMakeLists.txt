set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.0.0)
project(kOS VERSION 1.0.0)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

if(NOT ${CMAKE_ASM_COMPILER_ID} STREQUAL "Clang" OR NOT ${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(FATAL_ERROR "kOS does not support GCC, MSVC and other compilers other than LLVM.")
endif()

add_compile_options(--target=i386-pc-none -m32 -D__is_libk)

string(REGEX MATCH "Windows-?" MATCHED ${CMAKE_HOST_SYSTEM})
if(MATCHED)
    find_program(LD_LLD NAMES ld.lld REQUIRED)
    set(CMAKE_C_LINK_EXECUTABLE "\"${LD_LLD}\" <OBJECTS> -o <TARGET> <LINK_LIBRARIES> <LINK_FLAGS>")
endif()

add_subdirectory(libc)
add_subdirectory(Kernel)
