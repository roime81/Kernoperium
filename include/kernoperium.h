#ifndef KERNOPERIUM_H
#define KERNOPERIUM_H

#include <stddef.h>
#include <stdint.h>

#define KERNEL_MAX_TASKS 16
#define KERNEL_NAME_LEN 32

typedef struct {
    int id;
    char name[KERNEL_NAME_LEN];
    int priority;
    int urgency;
    int affinity;
    float confidence;
    uint64_t deadline;
    int cpu;
} KernelTask;

typedef struct {
    int active_tasks;
    int total_tasks;
    float mean_priority;
    float ai_confidence;
    uint64_t tick_count;
} KernelTelemetry;

float ai_score_task(const KernelTask *task);
int ai_select_task(const KernelTask *tasks, int count);
void ai_update_telemetry(KernelTelemetry *telemetry, const KernelTask *tasks, int count);
void kernel_init(void);
void scheduler_tick(KernelTask *tasks, int count, KernelTelemetry *telemetry);

#endif
