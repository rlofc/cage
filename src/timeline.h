#ifndef TIMELINE_H_G613QT9P
#define TIMELINE_H_G613QT9P

#include <stdint.h>

#define MAX_TIMELINE_EVENTS 100

struct toolbox;

/* A timeline holds a sequence of events
 * on a, well.. time line. Each event has a start time
 * ,a duration and a callback function.
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
 *
 * Timelines should help you maintain a cleaner code.
 */
struct timeline {
    struct {
        uint32_t ms_after;
        uint32_t ms_duration;
        void* (*callback) ( struct toolbox* t, float progress );
    } events[MAX_TIMELINE_EVENTS];
    int n_events;
    uint32_t timer;
    uint32_t acc_timer;
    int next_event;
};

/* Allocate and prepare a new timeline
 * ready for use.
 *
 * @return - an allocated, ready to use timeline.
 */
struct timeline* create_timeline(void);

/* Destroy a previously created timeline
 */
void destroy_timeline( struct timeline* timeline );

/* Append an event to the timeline
 *
 * @return -1 on error or the new event index
 */
int append_event( struct timeline* timeline, uint32_t begin_after, 
                   uint32_t duration, void* (*callback) ( struct toolbox* tbox, float progress ) );

/* Update the timeline timers and invoke event callbacks
 */
void* update_timeline( struct timeline* timeline, struct toolbox* tbox );

/* Used to prepare an already allocated timeline
 */
void init_timeline( struct timeline* timeline );

/* Cleans a used timeline, but does not deallocate it
 */
void cleanup_timeline( struct timeline* timeline );

#endif /* end of include guard: TIMELINE_H_G613QT9P */
