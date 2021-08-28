project(kOS.Kernel LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Kernel
    ${CMAKE_CURRENT_LIST_DIR}/Includes/Kernel/TerminalIO.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/Timing.h

    ${CMAKE_CURRENT_LIST_DIR}/Sources/Platforms/i386/Bootloader.s
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Platforms/i386/CRTi.s
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Platforms/i386/CRTn.s
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Platforms/i386/TerminalIO.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Platforms/i386/VGA.h

    ${CMAKE_CURRENT_LIST_DIR}/Sources/IRQ/IDT.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/IRQ/IDT.h
    ${CMAKE_CURRENT_LIST_DIR}/Sources/IRQ/LoadIDT.s
    ${CMAKE_CURRENT_LIST_DIR}/Sources/IRQ/ReadWritePort.s

    ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/GDT/GDT.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/GDT/GDT.h
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/GDT/GDTFlush.s
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/Kernel.c

    ${CMAKE_CURRENT_LIST_DIR}/Sources/Keyboard/KeyboardHandler.s
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Keyboard/KeyboardMap.h
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Keyboard/Keyboard.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Keyboard/Keyboard.h
)

target_include_directories(kOS.Kernel PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Includes)

add_dependencies(kOS.Kernel kOS.libc)
target_link_libraries(kOS.Kernel PRIVATE kOS.libc)

target_link_options(kOS.Kernel PRIVATE -T${CMAKE_CURRENT_LIST_DIR}/Sources/Platforms/i386/Format.ld)
