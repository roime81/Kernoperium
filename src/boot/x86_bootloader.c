#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define X86_BOOT_MAGIC 0xAA55U

typedef struct {
    uint16_t magic;
    uint16_t sector_size;
    uint32_t kernel_load_address;
    uint32_t kernel_size;
    uint8_t boot_drive;
    uint8_t cpu_mode;
    uint8_t reserved[10];
} X86BootHeader;

static void x86_print_stage(const char *stage_name) {
    printf("[x86 boot] %s\n", stage_name);
}

int main(void) {
    X86BootHeader boot = {
        .magic = X86_BOOT_MAGIC,
        .sector_size = 512,
        .kernel_load_address = 0x100000,
        .kernel_size = 4096,
        .boot_drive = 0x80,
        .cpu_mode = 0x20,
    };

    x86_print_stage("initializing BIOS-compatible environment");
    x86_print_stage("locating stage-2 bootloader");
    x86_print_stage("loading kernel image into protected memory");

    printf("boot magic: 0x%04x\n", boot.magic);
    printf("sector size: %u bytes\n", boot.sector_size);
    printf("kernel load address: 0x%08x\n", boot.kernel_load_address);
    printf("kernel size: %u bytes\n", boot.kernel_size);
    printf("boot drive: 0x%02x\n", boot.boot_drive);
    printf("cpu mode: 0x%02x\n", boot.cpu_mode);

    printf("x86 bootloader prototype complete.\n");
    return 0;
}
