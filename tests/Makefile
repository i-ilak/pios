# Set Compiler flags
SFLAGS = -fpic -ffreestanding -nostdlib
CFLAGS = -O2 -Wall -Wextra -g
LDFLAGS = -ffreestanding -O2 -nostdlib

# Set Build / Source / Include / Docs directories
BUILD_DIR = build
SRC_DIR = src
INC_DIR = ../os/include

KER_SRC = ../os/src/kernel
COMMON_SRC = ../os/src/common

KERNEL_VERSION = 0.1.0

.PHONY: clean all build docs docs_pdf clean_docs release release_armstub

all: build

# Compile project
## Compile every asm file in /arch/$(ARCH_DIR)
$(BUILD_DIR)/%_s.o: $(ARCH_DIR)/%.S
	mkdir -p $(@D)
	clang $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Compile every C file in /src/kernel
$(BUILD_DIR)/%_c.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	clang $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -DAARCH_32 -DMODEL_1 -c $< -o $@

## Compile every C file in /src/common
$(BUILD_DIR)/%_c.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	clang $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -DAARCH_32 -DMODEL_1 -c $< -o $@

## Find all object files (from corresponding C, asm files)
ASM_FILES = $(wildcard $(ARCH_DIR)/*.S)
KER_C_FILES = $(wildcard $(KER_SRC)/*.c)
COMMON_C_FILES = $(wildcard $(COMMON_SRC)/*.c)

OBJ_FILES = $(ASM_FILES:$(ARCH_DIR)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(KER_C_FILES:$(KER_SRC)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(COMMON_C_FILES:$(COMMON_SRC)/%.c=$(BUILD_DIR)/%_c.o)

## Link all object files and create final image
build: $(OBJ_FILES)
	clang -o build/test.o -c test.c -I/System/Volumes/Data/opt/homebrew/Cellar/cmocka/1.1.7/include 
	clang -o build/test build/test.o build/string_c.o build/stdlib_c.o -L/System/Volumes/Data/opt/homebrew/Cellar/cmocka/1.1.7/lib -lcmocka

# Clean rules
clean:
	rm -rf $(BUILD_DIR) *.img *.elf *.bin *.gz *.zip

run:
	./build/test
