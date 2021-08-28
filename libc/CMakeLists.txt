project(kOS.libc LANGUAGES C VERSION 1.0.0)

add_library(kOS.libc STATIC
    ${CMAKE_CURRENT_LIST_DIR}/Includes/sys/cdefs.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/stdio.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/stdlib.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/string.h

    ${CMAKE_CURRENT_LIST_DIR}/Sources/stdio/printf.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/stdio/putchar.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/stdio/puts.c

    ${CMAKE_CURRENT_LIST_DIR}/Sources/stdlib/abort.c

    ${CMAKE_CURRENT_LIST_DIR}/Sources/string/memcmp.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/string/memcpy.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/string/memmove.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/string/memset.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/string/strlen.c
)

target_include_directories(kOS.libc
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Includes

    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../Kernel/Includes # TODO: find a better way of doing this
)
