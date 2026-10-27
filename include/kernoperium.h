#ifndef KERNOPERIUM_H
#define KERNOPERIUM_H

#include <stddef.h>
#include <stdint.h>

#define KERNEL_MAX_TASKS 16
#define KERNEL_MAX_IRQS 16
#define KERNEL_NAME_LEN 32

typedef enum {
    TASK_READY = 0,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SLEEPING,
    TASK_TERMINATED
} KernelTaskState;

typedef enum {
    IRQ_NONE = 0,
    IRQ_TIMER,
    IRQ_IO,
    IRQ_MEMORY,
    IRQ_SYSCALL,
    IRQ_FAULT,
    IRQ_SCHEDULER,
    IRQ_POWER,
    IRQ_USER
} KernelInterruptType;

typedef struct {
    int id;
    char name[KERNEL_NAME_LEN];
    int priority;
    int urgency;
    int affinity;
    float confidence;
    uint64_t deadline;
    int cpu;
    KernelTaskState state;
} KernelTask;

typedef struct {
    int vector;
    KernelInterruptType type;
    uint64_t timestamp;
    int cpu;
    char message[KERNEL_NAME_LEN];
} KernelInterrupt;

typedef struct {
    int active_tasks;
    int total_tasks;
    float mean_priority;
    float ai_confidence;
    float load_factor;
    uint64_t tick_count;
    int last_selected_id;
} KernelTelemetry;

typedef struct {
    KernelTask tasks[KERNEL_MAX_TASKS];
    int task_count;
    KernelInterrupt irq_queue[KERNEL_MAX_IRQS];
    int irq_count;
} KernelRuntime;

float ai_score_task(const KernelTask *task);
int ai_select_task(const KernelTask *tasks, int count);
void ai_update_telemetry(KernelTelemetry *telemetry, const KernelTask *tasks, int count);
void ai_learning_update(KernelTask *task, float outcome);
void kernel_init(void);
void interrupt_raise(KernelRuntime *runtime, KernelInterruptType type, int vector, int cpu, const char *message);
void scheduler_tick(KernelRuntime *runtime, KernelTelemetry *telemetry);

#endif
