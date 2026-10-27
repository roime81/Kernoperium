# Kernoperium MVP

Native AI Kernel of the Next Generation OS.

Kernoperium MVP is a runnable prototype of an AI-native operating system kernel. It demonstrates a minimal but realistic control loop:

- boot sequence simulation
- interrupt-driven event handling
- task queue management
- adaptive scheduler scoring
- telemetry and learning feedback
- x86 and RISC-V bootstrap prototypes

This project is intentionally engineered as a minimum viable product for research and demonstration, not as a production kernel.

## MVP feature set

- Boot and initialization flow
- Microkernel-style task state model
- Interrupt queue and event dispatch simulation
- AI-guided scheduling with heuristic score
- Runtime telemetry and confidence adaptation
- Buildable demos for kernel + bootloader prototypes

## Repository structure

- `include/kernoperium.h` — shared kernel API and data structures
- `src/kernel.c` — MVP kernel runtime and demo loop
- `src/ai/ai_core.c` — task scoring and adaptive policy logic
- `src/boot/x86_bootloader.c` — x86 boot prototype
- `src/boot/riscv_bootloader.c` — RISC-V boot prototype
- `docs/mvp.md` — MVP overview and engineering notes
- `docs/os_architecture.md` — architecture blueprint
- `docs/roadmap.md` — future roadmap

## Build

```bash
make
```

## Run

```bash
./kernoperium_mvp
./x86_bootloader_demo
./riscv_bootloader_demo
```

## Example output

```text
Kernoperium booting...
Native AI Kernel of the Next Generation OS
========================================
[boot] initializing platform services
[boot] loading kernel image into memory
[task 4] user_agent          state=0 prio= 77 urgency= 96 affinity= 92 confidence=0.96 score=0.86
...
Selected task for execution: user_agent
Telemetry: active=5 mean_priority=74.00 ai_confidence=0.89 load=0.83 tick=1
```

## MVP status

Status: operational as a simulation and design validation tool.

Next steps toward a production kernel:
- privilege separation and syscall layer
- real interrupt vector table
- memory allocator and paging
- secure boot and signed modules
- real user-mode runtime

