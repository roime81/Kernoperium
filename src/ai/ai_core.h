#include "ai_core.h"

#include <stdio.h>
#include <string.h>

static float clampf(float value, float min_value, float max_value) {
    if (value < min_value) {
        return min_value;
    }
    if (value > max_value) {
        return max_value;
    }
    return value;
}

float ai_score_task(const KernelTask *task) {
    if (task == NULL) {
        return 0.0f;
    }

    const float priority_component = (float)task->priority / 100.0f;
    const float urgency_component = (float)task->urgency / 100.0f;
    const float affinity_component = (float)task->affinity / 100.0f;
    const float confidence_component = clampf(task->confidence, 0.0f, 1.0f);

    const float score =
        (0.45f * priority_component) +
        (0.25f * urgency_component) +
        (0.20f * affinity_component) +
        (0.10f * confidence_component);

    return clampf(score, 0.0f, 1.0f);
}

int ai_select_task(const KernelTask *tasks, int count) {
    if (tasks == NULL || count <= 0) {
        return -1;
    }

    int best_index = 0;
    float best_score = ai_score_task(&tasks[0]);

    for (int i = 1; i < count; ++i) {
        const float current_score = ai_score_task(&tasks[i]);
        if (current_score > best_score) {
            best_score = current_score;
            best_index = i;
        }
    }

    return best_index;
}

void ai_update_telemetry(KernelTelemetry *telemetry, const KernelTask *tasks, int count) {
    if (telemetry == NULL || tasks == NULL || count <= 0) {
        return;
    }

    int total_priority = 0;
    float total_confidence = 0.0f;

    for (int i = 0; i < count; ++i) {
        total_priority += tasks[i].priority;
        total_confidence += tasks[i].confidence;
    }

    telemetry->active_tasks = count;
    telemetry->total_tasks = count;
    telemetry->mean_priority = (float)total_priority / (float)count;
    telemetry->ai_confidence = total_confidence / (float)count;
    telemetry->tick_count += 1;
}
