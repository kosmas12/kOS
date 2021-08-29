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

project(kOS.EFI LANGUAGES C VERSION 1.0.0)

add_executable(kOS.EFI
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Protocols/TextInput.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Protocols/TextOutput.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Services/ABI.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Services/Boot.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Services/Runtime.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/ConfigurationTable.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Entry.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Event.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/GUID.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Handle.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/MemoryDescriptor.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Status.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/SystemTable.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/TableHeader.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI/Time.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/EFI.h

    ${CMAKE_CURRENT_LIST_DIR}/Sources/Main.c
)

target_include_directories(kOS.EFI PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Includes)

add_dependencies(kOS.EFI kOS.libc)

target_link_options(kOS.EFI PRIVATE -eEFI_main)
target_link_libraries(kOS.EFI PRIVATE kOS.libc)

kOS_Generate_Target_Data(kOS.EFI)
# FIXME: this currently builds an ELF, not a COFF
