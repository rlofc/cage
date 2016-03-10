#ifndef CAGE_TILES_H_
#define CAGE_TILES_H_

#include <stdbool.h>

struct map_spec {
    int rows;
    int cols;
    int tile_size;
    void* data;
};

enum actor_dir { ACTOR_DOWN,
                 ACTOR_LEFT,
                 ACTOR_RIGHT,
                 ACTOR_UP,
                 _NUM_OF_ACTOR_DIRS };

enum actor_state { ACTOR_STILL,
                   ACTOR_MOVING,
                   ACTOR_INACTIVE,
                   _NUM_OF_ACTOR_STATES };

struct actor_mode {
    enum actor_state state;
    enum actor_dir dir;
};

struct actor {
    point pos;
    float speed;
    struct actor_mode old_mode,
                      active_mode,
                      intent_mode;
    float current_speed;
    float elapsed_ms_acc;
};

struct tile_pos {
    int row;
    int col;
};

void set_actor_mode(struct actor* actor,
                    struct actor_mode intent);

struct tile_pos get_current_tile(struct map_spec* map,
                                 struct actor* actor);

struct tile_pos get_target_tile(struct map_spec* map,
                                struct actor* actor,
                                enum actor_dir intent);

bool is_actor_in_integral_tile(struct map_spec* map,
                               struct actor* actor);

/**
 * @brief update_walk
 * This function will expects the actor to have its
 * intent_dir set to a certain direction and will attempt moving
 * its position in that direction for the distance elapsed_ms/actor->speed.
 * custom_code will be called
 * @param map
 * @param actor
 * @param elapsed_ms
 */
void 
update_actor(struct map_spec* map, struct actor* actor, float elapsed_ms,
                              int (*is_walkable)(struct map_spec* map,
                                                 struct actor* actor,
                                                 struct tile_pos pos),
                              bool (*custom_code)(struct map_spec* map,
                                                  struct actor* actor,
                                                  float elapsed_ms));
#endif
