#include <stdint.h>
#include <stdio.h>

#define RV64_BOOT_MAGIC 0x52435631U

typedef struct {
    uint32_t magic;
    uint32_t hart_id;
    uint64_t kernel_entry;
    uint64_t dtb_address;
    uint64_t memory_size;
    uint32_t mode;
} RiscvBootHeader;

static void riscv_print_stage(const char *stage_name) {
    printf("[riscv boot] %s\n", stage_name);
}

int main(void) {
    RiscvBootHeader boot = {
        .magic = RV64_BOOT_MAGIC,
        .hart_id = 0,
        .kernel_entry = 0x80000000ULL,
        .dtb_address = 0x90000000ULL,
        .memory_size = 1024ULL * 1024ULL * 1024ULL,
        .mode = 0x1,
    };

    riscv_print_stage("initializing firmware and device tree");
    riscv_print_stage("loading kernel into memory at entry point");
    riscv_print_stage("handoff to supervisor mode");

    printf("boot magic: 0x%08x\n", boot.magic);
    printf("hart id: %u\n", boot.hart_id);
    printf("kernel entry: 0x%016llx\n", (unsigned long long)boot.kernel_entry);
    printf("dtb address: 0x%016llx\n", (unsigned long long)boot.dtb_address);
    printf("memory size: %llu MiB\n", (unsigned long long)(boot.memory_size / (1024ULL * 1024ULL)));
    printf("mode: 0x%08x\n", boot.mode);

    printf("RISC-V bootloader prototype complete.\n");
    return 0;
}
