/* Copyright (c) 2014-2016 Ithai Levi @RLofC
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */
#include "timeline.h"
#include "utils.h"
#include <stdlib.h>

struct timeline* create_timeline(void)
{
    struct timeline* timeline = malloc(sizeof(struct timeline));
    if (timeline != NULL)
        init_timeline(timeline);
    else
        ERROR("Unable to malloc a timeline");
    return timeline;
}

void destroy_timeline(struct timeline* timeline)
{
    free(timeline);
}

int append_event(struct timeline* timeline,
                 uint32_t wait,
                 uint32_t duration,
                 void* (*callback)(void* data,
                                   float elapsed_ms,
                                   float progress))
{
    struct timeline_event* event;
    if (timeline->acc_timer != 0) {
        ERROR("Cannot append event after timeline updates");
        return -1;
    }
    if (timeline->n_events == MAX_TIMELINE_EVENTS) {
        ERROR("Reached timeline events capacity limit");
        return -1;
    }
    event = &timeline->events[timeline->n_events];
    event->ms_wait = wait;
    event->ms_duration = duration;
    event->callback = callback;
    timeline->n_events++;
    return 0;
}

int append_events(struct timeline* timeline,
                  int nevents,
                  struct timeline_event events[])
{
    int i;
    for (i = 0; i < nevents; i++) {
        if (append_event(timeline, events[i].ms_wait, events[i].ms_duration,
                         events[i].callback) == -1)
            break;
    }
    return i == nevents ? i : -1;
}

void* update_timeline(struct timeline* timeline, void* data, float elapsed_ms)
{
    void* ret = NULL;
    if (timeline->paused) return ret;
    uint32_t next_acc_timer;

    if (timeline->next_event < timeline->n_events) {
        timeline->timer += elapsed_ms;
        /* loop to make sure we will not miss a consecutive callback */
        next_acc_timer =
        timeline->acc_timer + timeline->events[timeline->next_event].ms_wait;
        while (timeline->timer > next_acc_timer) {
            int eee = timeline->next_event;
            uint32_t elapsed = timeline->timer - next_acc_timer;
            uint32_t duration =
            timeline->events[timeline->next_event].ms_duration;
            if (duration < elapsed_ms || elapsed > duration) {
                timeline->acc_timer +=
                timeline->events[timeline->next_event].ms_wait;
                timeline->acc_timer +=
                timeline->events[timeline->next_event].ms_duration;
                timeline->next_event++;
                if (timeline->next_event < timeline->n_events)  // break;
                    next_acc_timer =
                    timeline->acc_timer +
                    timeline->events[timeline->next_event].ms_wait;
            }
            if ((elapsed <= duration || duration < elapsed_ms) &&
                eee < timeline->n_events) {
                float progress =
                duration == 0 ? 1.0f : (float)elapsed / (float)duration;
                ret =
                timeline->events[eee].callback(data, elapsed_ms, progress);
            }
            if (elapsed <= duration ||
                timeline->next_event < timeline->n_events)
                break;
        }
    }
    return ret;
}

void init_timeline(struct timeline* timeline)
{
    timeline->n_events = 0;
    reset_timeline(timeline);
}

void pause_timeline(struct timeline* timeline)
{
    timeline->paused = true;
}

void reset_timeline(struct timeline* timeline)
{
    timeline->paused = false;
    timeline->timer = 0;
    timeline->next_event = 0;
    timeline->acc_timer = 0;
}

void cleanup_timeline(struct timeline* timeline)
{
    init_timeline(timeline);
}
