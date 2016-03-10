#include "cage.h"
#include "tiled_actor.h"

/*******************************************************************************
 * ACTOR
 ******************************************************************************/

static point actor_walk_inc[_NUM_OF_ACTOR_DIRS] = {
    {.x = 0, .y = 1 },  /* ACTOR_DOWN */
    {.x = -1, .y = 0 }, /* ACTOR_LEFT */
    {.x = 1, .y = 0 },  /* ACTOR_RIGHT */
    {.x = 0, .y = -1 }, /* ACTOR_UP */
};

void set_actor_mode(struct actor* actor, struct actor_mode intent)
{
    actor->intent_mode = intent; 
}

/*******************************************************************************
 * ACTOR POSITIONING LOGIC
 ******************************************************************************/
static bool is_opposite_dir(enum actor_dir a, enum actor_dir b)
{
    return (a == ACTOR_UP && b == ACTOR_DOWN) ||
           (a == ACTOR_DOWN && b == ACTOR_UP) ||
           (a == ACTOR_LEFT && b == ACTOR_RIGHT) ||
           (a == ACTOR_RIGHT && b == ACTOR_LEFT);
}

/*******************************************************************************
 * TILE MOVEMENT LOGIC
 ******************************************************************************/

static int slide_to_integral_tile(struct map_spec* map,
                                  struct actor* actor,
                                  int distance)
{
    struct slide_params {
        point nullifier;
        int base;
        int sign;
    } slide_params[_NUM_OF_ACTOR_DIRS] = {
        {.nullifier = {.x = 0, .y = 1 },
         .base = map->tile_size,
         .sign = 1 }, /* ACTOR_DOWN */
        {.nullifier = {.x = 1, .y = 0 },
         .base = 0,
         .sign = -1 }, /* ACTOR_LEFT */
        {.nullifier = {.x = 1, .y = 0 },
         .base = map->tile_size,
         .sign = 1 }, /* ACTOR_RIGHT */
        {.nullifier = {.x = 0, .y = 1 },
         .base = 0,
         .sign = -1 }, /* ACTOR_UP */
    };

    int cdistance = distance > map->tile_size ? map->tile_size : distance;
    struct slide_params* sp = &slide_params[actor->active_mode.dir];
    point newpos;
    int x = actor->pos.x;
    int y = actor->pos.y;
    int dx = sp->base - (x % map->tile_size);
    int dy = sp->base - (y % map->tile_size);
    dx = cdistance < abs(dx) || dx == 0 ? cdistance * sp->sign : dx;
    dy = cdistance < abs(dy) || dy == 0 ? cdistance * sp->sign : dy;
    newpos.x = x + (dx * sp->nullifier.x);
    newpos.y = y + (dy * sp->nullifier.y);
    actor->pos = newpos;
    return abs(x - newpos.x) + abs(y - newpos.y);
}

struct tile_pos get_current_tile(struct map_spec* map, struct actor* actor)

{
    struct tile_pos ret;
    int r = actor->pos.y / map->tile_size;
    int c = actor->pos.x / map->tile_size;
    ret.row = r;
    ret.col = c;
    return ret;
}

struct tile_pos get_target_tile(struct map_spec* map,
                                struct actor* actor,
                                enum actor_dir intent)

{
    struct tile_pos ret;
    int r = actor->pos.y / map->tile_size;
    int c = actor->pos.x / map->tile_size;
    ret.row = r + actor_walk_inc[intent].y;
    ret.col = c + actor_walk_inc[intent].x;
    return ret;
}

bool is_actor_in_integral_tile(struct map_spec* map, struct actor* actor)
{
    return (int)actor->pos.x % map->tile_size == 0 &&
           (int)actor->pos.y % map->tile_size == 0;
}

static void update_actor_walk(struct map_spec* map,
                              struct actor* actor,
                              float elapsed_ms,
                              int (*is_walkable)(struct map_spec* map,
                                                 struct actor* actor,
                                                 struct tile_pos pos),
                              bool (*custom_code)(struct map_spec* map,
                                                  struct actor* actor,
                                                  float elapsed_ms))
{
    bool changed_direction =
    is_opposite_dir(actor->active_mode.dir, actor->intent_mode.dir);
    int distance =
    actor->current_speed > 0 ? elapsed_ms / actor->current_speed : 0;
    while (distance > 0) {
        if (is_actor_in_integral_tile(map, actor) || changed_direction) {
            if (is_walkable(map, actor,
                            get_target_tile(map,
                                            actor, actor->intent_mode.dir))) {
                actor->old_mode.dir = actor->active_mode.dir;
                actor->active_mode.dir = actor->intent_mode.dir;
            } else {
                if (is_walkable(map, actor,
                                get_target_tile(
                                map, actor, actor->active_mode.dir)) == false) {
                    actor->intent_mode.state = ACTOR_STILL;
                    break;
                }
            }
        }
        actor->old_mode.state = actor->active_mode.state;
        actor->active_mode.state = ACTOR_MOVING;
        distance -= slide_to_integral_tile(map, actor, distance);
        if (custom_code(map, actor, elapsed_ms)) break;
    }
}

void update_actor(struct map_spec* map,
                  struct actor* actor,
                  float elapsed_ms,
                  int (*is_walkable)(struct map_spec* map,
                                     struct actor* actor,
                                     struct tile_pos pos),
                  bool (*custom_code)(struct map_spec* map,
                                      struct actor* actor,
                                      float elapsed_ms))
{
    actor->elapsed_ms_acc += elapsed_ms;
    if (actor->elapsed_ms_acc > actor->speed) {
        int left = actor->speed > 0
                   ? (int)actor->elapsed_ms_acc % (int)actor->speed
                   : 0;
        if (actor->intent_mode.state == ACTOR_MOVING) {
            actor->current_speed = actor->speed;
            update_actor_walk(map, actor, actor->elapsed_ms_acc - left,
                              is_walkable, custom_code);
        }
        if (actor->intent_mode.state == ACTOR_STILL) {
            actor->old_mode.state = actor->active_mode.state;
            actor->active_mode.state = actor->intent_mode.state;
        }
        actor->elapsed_ms_acc = left;
    }
}
