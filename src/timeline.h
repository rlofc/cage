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
#ifndef TIMELINE_H_G613QT9P
#define TIMELINE_H_G613QT9P

#include <stdint.h>
#include "types.h"

#define MAX_TIMELINE_EVENTS 100

/**
 * Timeline event holds a single registered
 * event in a timeline. Timeline events can have a gap
 * of time between the last scheduled event.
 * Timeline events can also have a duration, which makes
 * them long-running events.
 * The manifestation of a timeline event is a callback call.
 */
struct timeline_event {
    /** Time to wait before activating the event */
    uint32_t ms_wait;
    /** Callback to call to */
    void* (*callback)(void* data, float elapsed_ms, float progress);
    /** Duration of the event */
    uint32_t ms_duration;
};

/**
 * A timeline holds a sequence of events
 * on a, well.. time line. Each event has a start time,
 * a duration and a callback function.
 * The callback gets called each time the timeline
 * is updated, as long as the event is active.
 *
 * You can use a time line to sequence animations,
 * cut-scenes, in-level scenes and other event-driven
 * behaviors.
 *
 * Events in a timeline cannot overlap. If you need
 * events to overlap (such as in a dialogue)
 * you will need to create more than one timeline,
 * just like you would have separate tracks in a
 * video editor or an animation software.
 */
struct timeline {
    /* Events to activate */
    struct timeline_event events[MAX_TIMELINE_EVENTS];
    /* Number of registered events */
    int n_events;
    /* Timer to keep track of the timeline running time */
    uint32_t timer;
    /* Accumulated timer to keep track of the timeline running time */
    uint32_t acc_timer;
    /* Pending event */
    int next_event;
    bool paused;
};

/**
 * Allocate and prepare a new timeline
 * ready for use.
 *
 * @return - an allocated, ready to use timeline.
 */
struct timeline* create_timeline(void);

/**
 * Destroy a previously created timeline
 */
void destroy_timeline(struct timeline* timeline);

/**
 * Append an event to the timeline
 * @param timeline Timeline to append the event to
 * @param wait Time to wait after the last event
 * @param duration Time to actively call the callback or 0 for
 *                 a single call
 * @param callback Callback function to call to
 *
 * @return -1 on error or the new event index
 */
int append_event(struct timeline* timeline,
                 uint32_t wait,
                 uint32_t duration,
                 void* (*callback)(void* data,
                                   float elapsed_ms,
                                   float progress));
/**
 * Append an set of events to the timeline
 * @param timeline Timeline to append the events to
 * @param nevents Number of events to append
 * @param events \ref timeline_event array
 *
 * @return -1 on error or the number of appended events
 */
int append_events(struct timeline* timeline,
                  int nevents,
                  struct timeline_event events[]);

/**
 * Update the timeline timers and invoke event callbacks
 */
void* update_timeline(struct timeline* timeline, void* data, float elapsed_ms);

/**
 * Pause a running timeline, stopping any running timer
 * accounting.
 */
void pause_timeline(struct timeline* timeline);

/**
 * Reset & restart a running or completed timeline.
 */
void reset_timeline(struct timeline* timeline);

/**
 * Used to prepare an already allocated timeline
 */
void init_timeline(struct timeline* timeline);

/**
 * Cleans a used timeline, but does not deallocate it
 */
void cleanup_timeline(struct timeline* timeline);

#endif /* end of include guard: TIMELINE_H_G613QT9P */
