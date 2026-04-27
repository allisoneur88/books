CC     = clang
CFLAGS = -Og

TARGET_X86 = x86_64-apple-macos
TARGET_ARM = arm64-apple-macos

SRC = $(wildcard *.c)

ASM_X86 = $(SRC:.c=.x86.s)
ASM_ARM = $(SRC:.c=.arm.s)
BIN     = $(SRC:.c=)

.PHONY: all x86 arm bin clean

all: bin x86 arm

x86: $(ASM_X86)
arm: $(ASM_ARM)
bin: $(BIN)

%.x86.s: %.c
	$(CC) $(CFLAGS) -S -target $(TARGET_X86) $< -o $@

%.arm.s: %.c
	$(CC) $(CFLAGS) -S -target $(TARGET_ARM) $< -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.x86.s *.arm.s $(BIN)

