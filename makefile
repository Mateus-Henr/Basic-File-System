make:
	gcc -o main src/main.c \
        src/command/command.c \
        src/command/command.h \
        src/ufs/ufs.c \
        src/ufs/ufs.h \
        src/ufs/i_node.c \
        src/ufs/i_node.h \
        src/path/path.c \
        src/path/path.h \
        src/entry/entry_metadata.c \
        src/entry/entry_metadata.h \
        src/entry/entry_content.c \
        src/entry/entry_content.h \
        src/entry/timestamps.c \
        src/entry/timestamps.h \
        src/entry/directory/directory.c \
        src/entry/directory/directory.h \
        src/entry/file/file.c \
        src/entry/file/file.h \
        src/entry/directory/linkedlist/linked_list.c \
        src/entry/directory/linkedlist/linked_list.h \
        src/entry/file/block.c \
        src/entry/file/block.h \
        src/miscelaneous/error.h \
        src/miscelaneous/print.h \
        src/miscelaneous/colour.h

run:
	./main