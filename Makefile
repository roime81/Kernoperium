#include "kernoperium.h"
#include "ai_core.h"

#include <stdio.h>
#include <string.h>

static void print_task(const KernelTask *task) {
    printf("[task %d] %-18s prio=%3d urgency=%3d affinity=%3d confidence=%.2f score=%.2f\n",
           task->id,
           task->name,
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

void scheduler_tick(KernelTask *tasks, int count, KernelTelemetry *telemetry) {
    if (tasks == NULL || telemetry == NULL || count <= 0) {
        return;
    }

    ai_update_telemetry(telemetry, tasks, count);

    for (int i = 0; i < count; ++i) {
        print_task(&tasks[i]);
    }

    const int chosen = ai_select_task(tasks, count);
    if (chosen >= 0) {
        printf("\nSelected task for execution: %s\n", tasks[chosen].name);
        printf("Scheduler confidence: %.2f\n", ai_score_task(&tasks[chosen]));
    }

    printf("Telemetry: active=%d mean_priority=%.2f ai_confidence=%.2f tick=%llu\n\n",
           telemetry->active_tasks,
           telemetry->mean_priority,
           telemetry->ai_confidence,
           (unsigned long long)telemetry->tick_count);
}

int main(void) {
    kernel_init();

    KernelTask tasks[] = {
        {1, "neural_guard", 82, 91, 88, 0.94f, 100, 0},
        {2, "memory_tuner", 68, 72, 76, 0.81f, 230, 1},
        {3, "power_balancer", 91, 84, 70, 0.89f, 180, 2},
        {4, "user_agent", 77, 96, 92, 0.96f, 90, 0},
        {5, "network_orchestrator", 73, 80, 86, 0.83f, 150, 3}
    };

    KernelTelemetry telemetry = {0, 0, 0.0f, 0.0f, 0};

    scheduler_tick(tasks, 5, &telemetry);
    scheduler_tick(tasks, 5, &telemetry);
    scheduler_tick(tasks, 5, &telemetry);

    return 0;
}

