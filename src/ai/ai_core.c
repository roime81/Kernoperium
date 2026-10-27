#include "ai_core.h"

#include <stdio.h>

static float clampf(float value, float min_value, float max_value) {
    if (value < min_value) {
        return min_value;
    }
    if (value > max_value) {
        return max_value;
    }
    return value;
}

static float deadline_bias(uint64_t deadline) {
    if (deadline == 0U) {
        return 0.15f;
    }
    if (deadline < 100U) {
        return 0.95f;
    }
    if (deadline < 500U) {
        return 0.75f;
    }
    return 0.50f;
}

static float state_bias(KernelTaskState state) {
    switch (state) {
        case TASK_RUNNING:
            return 0.18f;
        case TASK_READY:
            return 0.10f;
        case TASK_BLOCKED:
            return -0.20f;
        case TASK_SLEEPING:
            return -0.08f;
        case TASK_TERMINATED:
            return -0.35f;
        default:
            return 0.0f;
    }
}

float ai_score_task(const KernelTask *task) {
    if (task == NULL) {
        return 0.0f;
    }

    const float priority_component = (float)task->priority / 100.0f;
    const float urgency_component = (float)task->urgency / 100.0f;
    const float affinity_component = (float)task->affinity / 100.0f;
    const float confidence_component = clampf(task->confidence, 0.0f, 1.0f);
    const float deadline_component = deadline_bias(task->deadline);
    const float state_component = state_bias(task->state);

    const float score =
        (0.38f * priority_component) +
        (0.22f * urgency_component) +
        (0.18f * affinity_component) +
        (0.12f * confidence_component) +
        (0.08f * deadline_component) +
        state_component;

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
    float total_load = 0.0f;

    for (int i = 0; i < count; ++i) {
        total_priority += tasks[i].priority;
        total_confidence += tasks[i].confidence;
        total_load += ai_score_task(&tasks[i]);
    }

    telemetry->active_tasks = count;
    telemetry->total_tasks = count;
    telemetry->mean_priority = (float)total_priority / (float)count;
    telemetry->ai_confidence = total_confidence / (float)count;
    telemetry->load_factor = total_load / (float)count;
    telemetry->tick_count += 1;
}

void ai_learning_update(KernelTask *task, float outcome) {
    if (task == NULL) {
        return;
    }

    const float old_confidence = task->confidence;
    const float adjusted = clampf(old_confidence * 0.80f + outcome * 0.20f, 0.0f, 1.0f);
    task->confidence = adjusted;

    if (outcome > 0.5f) {
        task->priority = (task->priority + 5 > 100) ? 100 : task->priority + 5;
    } else {
        task->priority = (task->priority - 3 < 0) ? 0 : task->priority - 3;
    }
}
