CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -Iinclude -Isrc/ai

TARGET = kernoperium_mvp
BOOT_X86 = x86_bootloader_demo
BOOT_RISCV = riscv_bootloader_demo

all: $(TARGET) $(BOOT_X86) $(BOOT_RISCV)

$(TARGET): src/kernel.c src/ai/ai_core.c
	$(CC) $(CFLAGS) -o $(TARGET) src/kernel.c src/ai/ai_core.c

$(BOOT_X86): src/boot/x86_bootloader.c
	$(CC) $(CFLAGS) -o $(BOOT_X86) src/boot/x86_bootloader.c

$(BOOT_RISCV): src/boot/riscv_bootloader.c
	$(CC) $(CFLAGS) -o $(BOOT_RISCV) src/boot/riscv_bootloader.c

test: all
	./$(TARGET)
	./$(BOOT_X86)
	./$(BOOT_RISCV)
	@echo "All Kernoperium MVP demos passed."

clean:
	rm -f $(TARGET) $(BOOT_X86) $(BOOT_RISCV)

.PHONY: all clean test
