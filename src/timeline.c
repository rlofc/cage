#include "timeline.h"
#include "toolbox.h"
#include <stdlib.h>

struct timeline* create_timeline(void)
{
    struct timeline* timeline = malloc( sizeof( struct timeline ) );
    if ( timeline != NULL )
        init_timeline( timeline );
    return timeline;
}

void destroy_timeline( struct timeline* timeline )
{
    free( timeline );
}

int append_event( struct timeline* timeline, uint32_t wait,
                   uint32_t duration, void* (*callback) ( void* data, float elapsed_ms, float progress ) )
{
    if ( timeline->acc_timer != 0 ) return -1;
    if ( timeline->n_events == MAX_TIMELINE_EVENTS ) return -1;
    timeline->events[ timeline->n_events ].ms_wait = wait;
    timeline->events[ timeline->n_events ].ms_duration = duration;
    timeline->events[ timeline->n_events ].callback = callback;
    timeline->n_events++;
    return 0;
}

void* update_timeline( struct timeline* timeline, void* data, float elapsed_ms )
{
    void* ret = NULL;
    uint32_t next_acc_timer;

    if ( timeline->next_event < timeline->n_events ) {
        timeline->timer += elapsed_ms;
        /* loop to make sure we will not miss a consecutive callback */
        next_acc_timer = timeline->acc_timer + timeline->events[ timeline->next_event ].ms_wait;
        while ( timeline->timer > next_acc_timer ) {
            uint32_t elapsed  = timeline->timer - next_acc_timer;
            uint32_t duration = timeline->events[ timeline->next_event ].ms_duration;
            if ( elapsed <= duration || duration < elapsed_ms ) {
                float progress = duration == 0 ? 1.0f : (float)elapsed/(float)duration;
                ret = timeline->events[ timeline->next_event ].callback( data, elapsed_ms, progress );
                break;
            } else {
                timeline->acc_timer += timeline->events[ timeline->next_event ].ms_wait;
                timeline->acc_timer += timeline->events[ timeline->next_event ].ms_duration;
                timeline->next_event++;
                if ( timeline->next_event == timeline->n_events ) break;
                next_acc_timer = timeline->acc_timer + timeline->events[ timeline->next_event ].ms_wait;
            }
        }
    }
    return ret;
}

void init_timeline( struct timeline* timeline )
{
    timeline->timer = 0;
    timeline->n_events = 0;
    timeline->next_event = 0;
    timeline->acc_timer = 0;
}

void cleanup_timeline( struct timeline* timeline )
{
    init_timeline( timeline );
}
