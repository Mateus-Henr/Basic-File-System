cmake_minimum_required(VERSION 3.25)
project(Basic_File_System C)

set(CMAKE_C_STANDARD 99)

add_executable(Basic_File_System src/main.c
        src/entry/timestamps.c
        src/entry/timestamps.h
        src/entry/entry_metadata.c
        src/entry/entry_metadata.h
        src/ufs/i_node.c
        src/ufs/i_node.h
        src/ufs/linkedlist/linked_list_i_node.c
        src/ufs/linkedlist/linked_list_i_node.h
        src/ufs/ufs.c
        src/ufs/ufs.h
        src/entry/entry_content.c
        src/entry/entry_content.h
        src/entry/file/file.c
        src/entry/file/file.h
        src/entry/directory/directory.c
        src/entry/directory/directory.h
        src/entry/directory/linkedlist/linked_list.c
        src/entry/directory/linkedlist/linked_list.h
        src/memory/block.c
        src/memory/block.h
        src/path/path.c
        src/path/path.h
        src/command/command.c
        src/command/command.h
        src/miscelaneous/colour.h
        src/miscelaneous/error.h
        src/miscelaneous/print.h
        src/entry/entry_header.c
        src/entry/entry_header.h
        src/memory/memory.c
        src/memory/memory.h
        src/memory/block.c
        src/memory/block.h
        src/memory/linkedlist/linked_list_block.c
        src/memory/linkedlist/linked_list_block.h)

target_link_libraries(Basic_File_System m)