BUILD_DIR=../build/os
OS=$(BUILD_DIR)/kernel.o

CFLAGS += -std=gnu99 -ffreestanding -O2 -Wall -Wextra

OS_SRCS := $(wildcard *.c)
OS_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(OS_SRCS))

all: $(OS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	i686-elf-gcc -c $(OS_SRCS) -o $(OS_OBJS) $(CFLAGS)

clean:
	rm $(BUILD_DIR)/*
