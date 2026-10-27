# Kernoperium MVP Notes

## Goal

Kernoperium MVP is designed to validate the idea of an AI-native operating system at a small scale: a boot sequence, task model, interrupt queue, and adaptive scheduler all run as a realistic simulation.

## What the MVP validates

1. Task scoring is explainable and bounded.
2. Interrupts can trigger scheduling decisions.
3. The scheduler can learn from task outcomes.
4. The architecture can be extended toward a real microkernel.

## Current behavior

The demo uses a synthetic task set representing:
- a neural guard task
- a memory tuner task
- a power balancer task
- a user agent task
- a network orchestrator task

Each task carries state, urgency, affinity, confidence, deadline pressure, and a runtime estimate. The scheduler uses a composite score to decide which task receives the next execution window.

## Score model

The scheduler uses a weighted utility model:

score = 0.38 * priority + 0.22 * urgency + 0.18 * affinity + 0.12 * confidence + 0.08 * deadline + state_bias

This is intentionally simple, bounded, and transparent so it can be extended as the system grows.

## Why this is MVP-grade

The project now provides:
- a cohesive build target
- a runnable kernel demo
- interrupt and task simulation
- AI-informed decision logic
- architecture documents for future expansion

## Future milestones

- real privilege levels and system calls
- true timer interrupt and trap handling
- memory allocator and paging
- secure boot and module signing
- user-space daemons and filesystem layer
