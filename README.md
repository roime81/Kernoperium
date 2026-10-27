# Kernoperium MVP

Native AI Kernel of the Next Generation OS.

Kernoperium is a research prototype for a next-generation operating system whose kernel is designed around adaptive intelligence rather than static priority alone. The project combines a microkernel-inspired runtime, interrupt/event simulation, and an AI-guided scheduler to demonstrate how an OS might reason about tasks, urgency, confidence, and resource pressure.

This repository is intentionally built as a minimum viable product (MVP). It is not a full production kernel, but it is a functional prototype that you can build, run, and inspect to understand the architecture.

## What it is

Kernoperium is a small operating-system prototype that models:

- platform initialization and boot flow
- task lifecycle and state transitions
- interrupt-driven event handling
- scheduler decisions based on task utility
- runtime telemetry and learning feedback
- x86 and RISC-V bootloader prototypes

In plain terms, it is a tiny AI-native kernel blueprint that shows how a kernel might schedule workloads using more than just a static priority queue.

## Why it exists

Traditional kernels often prioritize work with fixed weights, such as user priority or CPU quota. Kernoperium explores a different idea:

- every task has urgency, affinity, confidence, and deadline pressure
- the kernel scores tasks using a weighted utility model
- the scheduler chooses the task with the best expected system value
- telemetry feeds back into the task model so future decisions adapt over time

This makes the scheduler more responsive to system load and workload characteristics.

## How it works

The kernel model is built around four key ideas.

### 1. Task model

Each task includes:

- id
- name
- priority
- urgency
- affinity
- confidence
- deadline
- CPU target
- execution state

Example task metadata is defined in `include/kernoperium.h`.

### 2. Interrupt model

The runtime simulates hardware or software interrupts such as:

- timer interrupt
- I/O interrupt
- memory interrupt
- syscall interrupt
- fault interrupt
- scheduler interrupt
- power interrupt
- user interrupt

These interrupts are queued and then influence scheduling decisions.

### 3. AI scheduler

The scheduler calculates a score for each runnable task using a weighted heuristic:

score = 0.38 * priority + 0.22 * urgency + 0.18 * affinity + 0.12 * confidence + 0.08 * deadline + state_bias

This score is bounded between 0 and 1 and determines which task gets the next execution window. The project includes a lightweight learning update that slightly nudges task confidence and priority after successful scheduling outcomes.

### 4. Telemetry loop

Each scheduler tick updates:

- active task count
- mean priority
- AI confidence average
- load factor
- last selected task

This creates a loop that resembles a control system: observe -> score -> select -> learn -> repeat.

## System architecture

The project is organized into a few main parts:

- `include/kernoperium.h` — shared kernel interfaces and structures
- `src/kernel.c` — kernel demo and scheduler loop
- `src/ai/ai_core.c` — heuristic scoring and adaptive update logic
- `src/boot/x86_bootloader.c` — x86 bootloader prototype
- `src/boot/riscv_bootloader.c` — RISC-V bootloader prototype
- `docs/os_architecture.md` — large design blueprint
- `docs/roadmap.md` — roadmap toward a full OS
- `docs/mvp.md` — short MVP notes

## Build

From the repository root:

```bash
make
```

This builds:

- `kernoperium_mvp`
- `x86_bootloader_demo`
- `riscv_bootloader_demo`

## Run it

### 1. Run the main kernel demo

```bash
./kernoperium_mvp
```

This simulates a kernel boot, queued interrupts, task list rendering, and task selection.

### 2. Run the x86 boot prototype

```bash
./x86_bootloader_demo
```

This simulates a BIOS-like x86 environment and prints the boot metadata.

### 3. Run the RISC-V boot prototype

```bash
./riscv_bootloader_demo
```

This simulates a simple RISC-V boot sequence and memory handoff configuration.

## How to test it

### Quick validation

```bash
make test
```

This command builds all binaries and runs each one sequentially. It is the main smoke test for the project.

### Manual testing

```bash
make clean && make
./kernoperium_mvp
./x86_bootloader_demo
./riscv_bootloader_demo
```

### Expected behavior

The kernel demo should print a boot banner, list tasks, show queued interrupts, then select the highest-score task and print telemetry. The bootloader demos should print staged boot messages and metadata.

Example output from the kernel demo:

```text
Kernoperium booting...
Native AI Kernel of the Next Generation OS
========================================
[boot] initializing platform services
[boot] loading kernel image into memory
[boot] preparing scheduler and interrupt vectors

=== scheduler tick 1 ===
[task 1] neural_guard        state=0 prio= 82 urgency= 91 affinity= 88 confidence=0.94 score=0.86
[task 2] memory_tuner        state=0 prio= 68 urgency= 72 affinity= 76 confidence=0.81 score=0.72
[task 3] power_balancer     state=0 prio= 91 urgency= 84 affinity= 70 confidence=0.89 score=0.84
[task 4] user_agent         state=0 prio= 77 urgency= 96 affinity= 92 confidence=0.96 score=0.89
[task 5] network_orchestrator state=0 prio= 73 urgency= 80 affinity= 86 confidence=0.83 score=0.77

Selected task for execution: user_agent
Scheduler confidence: 0.89
Telemetry: active=5 mean_priority=74.00 ai_confidence=0.89 load=0.83 tick=1
```

## Testing checklist

Use the following checklist to validate the project:

- build succeeds with `make`
- `./kernoperium_mvp` runs without crashing
- interrupts are printed in the scheduler output
- selected task changes based on score
- telemetry values are updated after each tick
- x86 and RISC-V demo programs complete successfully

## MVP status

This project is a working research MVP and is suitable for:

- architecture exploration
- kernel concept validation
- scheduler prototyping
- educational demos
- future extension into a real microkernel

It is not yet a production kernel and does not provide real kernel/user separation, paging, or hardware-level booting.

## Next development steps

The next realistic phases are:

1. process/thread control blocks
2. real trap and interrupt vectors
3. memory allocator and paging
4. secure boot and signed modules
5. filesystem and user-space daemons
6. hardware-targeted builds for x86_64 or RISC-V64

## License

This project is released under the MIT License. See `LICENSE` for details.

## Conclusion

Kernoperium MVP is a lightweight but meaningful demonstration of an AI-native kernel concept. It shows how a modern OS can combine microkernel principles with adaptive task scoring and runtime learning, making it a solid foundation for a future next-generation operating system.
