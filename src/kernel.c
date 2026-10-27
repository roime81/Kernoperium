#include "kernoperium.h"
#include "ai_core.h"

#include <stdio.h>

static void print_task(const KernelTask *task) {
    printf("[task %d] %-18s state=%d prio=%3d urgency=%3d affinity=%3d confidence=%.2f score=%.2f\n",
           task->id,
           task->name,
           task->state,
           task->priority,
           task->urgency,
           task->affinity,
           task->confidence,
           ai_score_task(task));
}

void kernel_init(void) {
    printf("Kernoperium booting...\n");
    printf("Native AI Kernel of the Next Generation OS\n");
    printf("========================================\n");
}

void interrupt_raise(KernelRuntime *runtime, KernelInterruptType type, int vector, int cpu, const char *message) {
    if (runtime == NULL || runtime->irq_count >= KERNEL_MAX_IRQS) {
        return;
    }

    KernelInterrupt *irq = &runtime->irq_queue[runtime->irq_count];
    irq->type = type;
    irq->vector = vector;
    irq->cpu = cpu;
    irq->timestamp = (uint64_t)runtime->irq_count + 1U;
    irq->message[0] = '\0';

    if (message != NULL) {
        snprintf(irq->message, sizeof(irq->message), "%s", message);
    }

    runtime->irq_count += 1;
}

void scheduler_tick(KernelRuntime *runtime, KernelTelemetry *telemetry) {
    if (runtime == NULL || telemetry == NULL || runtime->task_count <= 0) {
        return;
    }

    ai_update_telemetry(telemetry, runtime->tasks, runtime->task_count);

    if (runtime->irq_count > 0) {
        printf("\nInterrupt queue (%d):\n", runtime->irq_count);
        for (int i = 0; i < runtime->irq_count; ++i) {
            const KernelInterrupt *irq = &runtime->irq_queue[i];
            printf("  IRQ[%d] type=%d vector=%d cpu=%d msg=%s\n",
                   i,
                   irq->type,
                   irq->vector,
                   irq->cpu,
                   irq->message);
        }
    }

    for (int i = 0; i < runtime->task_count; ++i) {
        print_task(&runtime->tasks[i]);
    }

    const int chosen = ai_select_task(runtime->tasks, runtime->task_count);
    if (chosen >= 0) {
        KernelTask *selected = &runtime->tasks[chosen];
        selected->state = TASK_RUNNING;
        telemetry->last_selected_id = selected->id;
        printf("\nSelected task for execution: %s\n", selected->name);
        printf("Scheduler confidence: %.2f\n", ai_score_task(selected));
        ai_learning_update(selected, 0.82f);
    }

    for (int i = 0; i < runtime->task_count; ++i) {
        if (runtime->tasks[i].state == TASK_RUNNING && i != chosen) {
            runtime->tasks[i].state = TASK_READY;
        }
    }

    printf("Telemetry: active=%d mean_priority=%.2f ai_confidence=%.2f load=%.2f tick=%llu\n\n",
           telemetry->active_tasks,
           telemetry->mean_priority,
           telemetry->ai_confidence,
           telemetry->load_factor,
           (unsigned long long)telemetry->tick_count);
}

int main(void) {
    kernel_init();

    KernelRuntime runtime = {0};
    runtime.task_count = 5;

    KernelTask tasks[] = {
        {1, "neural_guard", 82, 91, 88, 0.94f, 100, 0, TASK_READY},
        {2, "memory_tuner", 68, 72, 76, 0.81f, 230, 1, TASK_READY},
        {3, "power_balancer", 91, 84, 70, 0.89f, 180, 2, TASK_READY},
        {4, "user_agent", 77, 96, 92, 0.96f, 90, 0, TASK_READY},
        {5, "network_orchestrator", 73, 80, 86, 0.83f, 150, 3, TASK_READY}
    };

    for (int i = 0; i < 5; ++i) {
        runtime.tasks[i] = tasks[i];
    }

    interrupt_raise(&runtime, IRQ_TIMER, 0x20, 0, "timer_tick");
    interrupt_raise(&runtime, IRQ_IO, 0x21, 0, "disk_request");
    interrupt_raise(&runtime, IRQ_MEMORY, 0x30, 1, "page_fault");

    KernelTelemetry telemetry = {0, 0, 0.0f, 0.0f, 0.0f, 0, -1};

    scheduler_tick(&runtime, &telemetry);
    scheduler_tick(&runtime, &telemetry);
    scheduler_tick(&runtime, &telemetry);

    return 0;
}
