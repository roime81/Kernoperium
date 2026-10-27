# Kernoperium

Native AI Kernel of the Next Generation OS.

Kernoperium is a research operating-system kernel architecture designed around a simple but powerful principle: the kernel is not just a scheduler, but a closed-loop control system that continuously evaluates workload utility, resource pressure, and system health. This repository is a technical prototype for a next-generation AI-native microkernel.

## What is included

This repository now contains a staged prototype set:

- a microkernel task model with interrupt handling simulation
- an AI-aware scheduler with heuristic scoring and adaptive telemetry
- x86 and RISC-V bootloader prototypes
- an architecture and roadmap document for the OS

## Project structure

- `include/kernoperium.h` — shared kernel definitions and interfaces
- `src/ai/ai_core.h` — AI scheduler declarations
- `src/ai/ai_core.c` — heuristic scoring and learning logic
- `src/kernel.c` — microkernel task and interrupt simulation
- `src/boot/x86_bootloader.c` — x86 bootstrap prototype
- `src/boot/riscv_bootloader.c` — RISC-V bootstrap prototype
- `docs/os_architecture.md` — operating-system architecture blueprint
- `docs/roadmap.md` — long-term implementation roadmap

## Build

```bash
make
```

This produces:

- `kernoperium_demo`
- `x86_bootloader_demo`
- `riscv_bootloader_demo`

## Run

```bash
./kernoperium_demo
./x86_bootloader_demo
./riscv_bootloader_demo
```

## Design goals

The system is organized around four layers:

1. boot and platform bring-up
2. interrupt and task management
3. AI-guided scheduling and resource balancing
4. system telemetry and long-term optimization

This repository intentionally focuses on architectural clarity rather than production-system completeness. It is a plausible foundation for a future AI-native kernel and operating system.
