.. highlight:: c

samples / tiled.c
==================


::

	#include "cage.h"
	#include "tiled_actor.h"
	#include "tmx.h"
	
The tile size we'll use for this sample is exactly 16 pixels.


::

	#define TILE_SIZE 16
	
The hero struct is used to animate and manage our main actor.
It contains an actor struct that in turn, makes sure the hero
moves properly inside our tilemap.
We use a 2x2 array to store the different animations for the
hero using the actor valid states and directions as dimension
sizes.


::

	struct hero {
	    struct sprite* sprite;
	    struct sprite* mask;
	    struct animation* mode_anims[_NUM_OF_ACTOR_STATES][_NUM_OF_ACTOR_DIRS];
	    struct actor actor;
	};
	
We assume having exactly 4 layers in our Tiled file.
BASE is mostly our background layer - meaning anything
that is drawn behind our hero.
FEATURES is used for things that obscure our actors.
OVERLAY is used for things we blend onto our actors,
such as grass or shadows.
OBJECTS is used for shapes. In this sample it is
used only to indicate our hero origin tile.


::

	enum map_layer { BASE, FEATURES, OVERLAY, OBJECTS, _NUM_OF_LAYERS };
	
The game struct holds everything we need to run the main
game state, including our hero,  the Tiled layers we need
and the tiles spritemaps.


::

	struct game {
	    int screen_width;
	    int screen_height;
	    point camera;
	    struct hero hero;
	    struct sprite* tiles;
	    struct sprite* grass;
	    struct sprite* shadows;
	    struct image* actor_effects;
	    struct map_spec map_spec;
	    tmx_layer* layers[_NUM_OF_LAYERS];
	};
	
We use a straightforward approach to read the Tiled
tilemap using libtmx. We assume the existance of
exactly 4 layers and we make sure to populate
all 4 of them, otherwise we indicate an error
by returning -1.


::

	static int read_map(struct game* game, tmx_map* m)
	{
	    game->map_spec.rows = m->height;
	    game->map_spec.cols = m->width;
	    game->map_spec.tile_size = TILE_SIZE;
	    game->map_spec.data = m;
	    tmx_layer* l = (l = game->layers[BASE] = m->ly_head) ?
	                   (l = game->layers[FEATURES] = l->next) ?
	                   (l = game->layers[OVERLAY] = l->next) ?
	                   (l = game->layers[OBJECTS] = l->next) : NULL : NULL : NULL;
	    return l == NULL ? -1 : 0;
	}
	
get_tile_id makes it easier to get the int gid value from libtmx
for a specific tile_pos.


::

	static int get_tile_id(tmx_map* m, tmx_layer* l, struct tile_pos tp)
	{
	    return l->content.gids[tp.row * m->width + tp.col] & TMX_FLIP_BITS_REMOVAL;
	}
	
We use libtmx to load our game's Tiled file and
then call read_map to store our required tilemap
layers.


::

	static int build_tilemap(struct game* game)
	{
	    tmx_map* m;
	    m = tmx_load("res/game.tmx");
	    if (m == NULL) {
	        printf("Error reading tmx file.");
	        goto error;
	    } else {
	        if (read_map(game, m) == -1) goto error;
	    }
	    return 0;
	error:
	    return -1;
	}
	
	#define CHECK(S,E) if ((S) == NULL) { \
	        ERROR(#E" when trying "#S); \
	        goto E; \
	    }
	
Drawing all the actors. For now, this is just
our hero.


::

	static int draw_actors(struct game* game)
	{
	    return draw_sprite(game->hero.sprite,
	                       game->hero.actor.pos.x - game->camera.x,
	                       game->hero.actor.pos.y - game->camera.y - TILE_SIZE);
	}
	
Our tiles art are stored as spritemaps. Drawing
the tiles means drawing one of the frames in
one of the spritemaps we use for each layer.


::

	static void draw_tile(struct game* game,
	                      struct sprite* tilemap,
	                      enum map_layer layer_name,
	                      struct tile_pos pos)
	{
	    draw_sprite_frame(tilemap,
	                      TILE_SIZE * (pos.col) - game->camera.x,
	                      TILE_SIZE * (pos.row) - game->camera.y,
	                      get_tile_id(game->map_spec.data,
	                                  game->layers[layer_name], pos) - 1);
	}
	
This high-order function will help us apply a function
for each visible tile that we need to draw. It will
help us draw the different layers of our tilemap
with significantly less lines of code.


::

	static void foreach_visible_tile(struct game* game,
	                                 void (*callback)(struct game* game,
	                                                  int r,
	                                                  int c))
	{
	    int base_row = game->camera.y / TILE_SIZE - 1;
	    int base_col = game->camera.x / TILE_SIZE - 1;
	    int max_row = game->screen_height / TILE_SIZE + base_row + 3;
	    int max_col = game->screen_width / TILE_SIZE + base_col + 3;
	    for (int r = base_row; r < max_row; r++) {
	        for (int c = base_col; c < max_col; c++) {
	            if (c >= 0 && r >= 0 && c < game->map_spec.cols &&
	                r < game->map_spec.rows)
	                callback(game, r, c);
	        }
	    }
	}
	
The following set of callback functions are defined for
use with foreach_visible_tile. Each function is designed
to draw one of the layers of our tilemap.


::

	static void draw_background(struct game* game, int r, int c)
	{
	    draw_tile(game, game->tiles, BASE, (struct tile_pos){ r, c });
	}
	
	static void draw_features(struct game* game, int r, int c)
	{
	    draw_tile(game, game->grass, BASE, (struct tile_pos){ r, c });
	    draw_tile(game, game->grass, FEATURES, (struct tile_pos){ r, c });
	}
	
	static void draw_foreground(struct game* game, int r, int c)
	{
	    draw_tile(game, game->tiles, OVERLAY, (struct tile_pos){ r, c });
	}
	
	static void draw_shadows(struct game* game, int r, int c)
	{
	    draw_tile(game, game->shadows, FEATURES, (struct tile_pos){ r, c });
	}
	
The main drawing function carefully draws all the layers
of the tilemap and our hero using a nice scheme to help
up have shadows and grass overlay effects.


::

	static void draw_game(void* data, float elapsed_ms)
	{
	    struct game* game = data;
	    foreach_visible_tile(game, draw_background);
	    int f = draw_actors(game);
	    foreach_visible_tile(game, draw_features);
	    /** Creating an overlay image for the actors sprite effects
	     * such as grass transparency and shadows.
	     */
	    set_blend_mode(game->actor_effects, BLEND);
	    clear_image(game->actor_effects, color_from_RGBA(0, 0, 0, 0));
	    draw_on_image(game->actor_effects);
	    draw_sprite_frame(game->hero.mask, game->hero.actor.pos.x - game->camera.x,
	                game->hero.actor.pos.y - game->camera.y - TILE_SIZE, f);
	    set_blend_mode(game->shadows->image, MULTIPLY);
	    foreach_visible_tile(game, draw_shadows);
	    /** Time to render the prepared the effects layer. */
	    draw_on_screen();
	    set_blend_mode(game->actor_effects, BLEND);
	    draw_image(game->actor_effects, 0, 0, NULL, 0);
	    /** Finally, we draw the forground layer, such as tree canopies, bushes,
	     * etc.. */
	    foreach_visible_tile(game, draw_foreground);
	}
	
	static void read_controller(struct game* game, float elapsed_ms)
	{
	    if (game->hero.actor.active_mode.state != ACTOR_INACTIVE) {
	        int intent = key_down(KB_DOWN) ? ACTOR_DOWN :
	                     key_down(KB_LEFT) ? ACTOR_LEFT :
	                     key_down(KB_UP) ? ACTOR_UP :
	                     key_down(KB_RIGHT) ? ACTOR_RIGHT : -1;
	        if (intent != -1) {
	            set_actor_mode(&game->hero.actor, (struct actor_mode){
	                .state = ACTOR_MOVING,
	                .dir = intent});
	        }
	    }
	}
	
	static bool custom_hero_walk(struct map_spec* map,
	                             struct actor* actor,
	                             float elapsed_ms)
	{
	    if (is_actor_in_integral_tile(map, actor)) {
	        /* Add custom movement logic here */
	        return true;
	    }
	    return false;
	}
	
	static int is_tile_walkable(struct map_spec* map_spec,
	                            struct actor* actor,
	                            struct tile_pos pos)
	{
	    tmx_map* map = map_spec->data;
	    int base_tile_id = get_tile_id(map, map->ly_head, pos);
	    int feature_tile_id = get_tile_id(map, map->ly_head->next, pos);
	    return (base_tile_id != 17 && feature_tile_id != 50 &&
	            feature_tile_id != 47);
	}
	
	static void cleanup_hero(struct hero* hero)
	{
	    for (int i = 0; i < _NUM_OF_ACTOR_DIRS; i++) {
	        destroy_animation(hero->mode_anims[ACTOR_MOVING][i]);
	        destroy_animation(hero->mode_anims[ACTOR_STILL][i]);
	    }
	    destroy_image(hero->sprite->image);
	    destroy_sprite(hero->sprite);
	}
	
	#define MS_F 1
	
	static int init_hero(struct hero* hero)
	{
	    CHECK(hero->sprite = create_sprite(create_image("res/sprite.png"),
	                                       TILE_SIZE,
	                                       TILE_SIZE * 2), create_failed);
	    CHECK(hero->mask = create_sprite(create_image("res/spritemask.png"),
	                                     TILE_SIZE, TILE_SIZE * 2), create_failed);
	    for (int i = 0; i < _NUM_OF_ACTOR_DIRS; i++) {
	        CHECK(hero->mode_anims[ACTOR_MOVING][i] = create_animation(),
	              create_failed);
	        int walk_seq[] = {0, 1, 2, 1};
	        for (size_t j = 0; j < (sizeof walk_seq / sizeof walk_seq[0]); j++) {
	            add_frame(hero->mode_anims[ACTOR_MOVING][i],
	                      (i * 3) + walk_seq[j], 200 * MS_F, NULL);
	        }
	        CHECK(hero->mode_anims[ACTOR_STILL][i] = create_animation(),
	              create_failed);
	        add_frame(hero->mode_anims[ACTOR_STILL][i],
	                  (i * 3) + 0, 32 * MS_F, NULL);
	    }
	    hero->actor.speed = 20;
	    return 0;
	create_failed:
	    return -1;
	}
	
	static void update_hero_animation(struct hero* hero, float elapsed_ms)
	{
	    play_animation(hero->sprite,
	                   hero->mode_anims[hero->actor.active_mode.state]
	                                   [hero->actor.active_mode.dir]);
	    animate_sprite(hero->sprite, elapsed_ms);
	}
	
	static void update_hero(struct game* game, float elapsed_ms)
	{
	    read_controller(game, elapsed_ms);
	    update_actor(&game->map_spec, &game->hero.actor, elapsed_ms,
	                 is_tile_walkable, custom_hero_walk);
	    update_hero_animation(&game->hero, elapsed_ms);
	    game->camera.x = game->hero.actor.pos.x - game->screen_width / 2;
	    game->camera.y = game->hero.actor.pos.y - game->screen_height / 2;
	}
	
	static struct sprite* create_tileset(const char* img)
	{
	    return create_sprite(create_image(img), TILE_SIZE, TILE_SIZE);
	}
	
	static void* create_game(void)
	{
	    struct game* game = calloc(1, sizeof(struct game));
	    get_screen_size(&game->screen_width, &game->screen_height);
	    game->actor_effects = create_target_image(game->screen_width,
	                                              game->screen_height,
	                                              color_from_RGBA(0,0,0,0));
	    CHECK(game->tiles = create_tileset("res/tileset.png"), create_failure);
	    CHECK(game->grass = create_tileset("res/overlay.png"), create_failure);
	    CHECK(game->shadows = create_tileset("res/shadowmap.png"), create_failure);
	    if (init_hero(&game->hero) == -1) goto init_hero_error;
	    build_tilemap(game);
	    if (game->layers[OBJECTS]->type != L_OBJGR) goto invalid_layers;
	    tmx_object* obj = game->layers[OBJECTS]->content.objgr->head;
	    if (obj == NULL) goto invalid_layers;
	    game->hero.actor.pos.x = ((int)obj->x / TILE_SIZE) * TILE_SIZE;
	    game->hero.actor.pos.y = ((int)obj->y / TILE_SIZE) * TILE_SIZE;
	all_is_well:
	    return game;
	create_failure:
	invalid_layers:
	init_hero_error:
	    return NULL;
	}
	
	static void update_game(void* data, float elapsed_ms)
	{
	    struct game* game = data;
	    update_hero(game, elapsed_ms);
	    draw_game(data, elapsed_ms);
	}
	
	static void destroy_game(void* data)
	{
	    struct game* game = data;
	    destroy_image(game->tiles->image);
	    destroy_sprite(game->tiles);
	    destroy_image(game->grass->image);
	    destroy_sprite(game->grass);
	    destroy_image(game->shadows->image);
	    destroy_sprite(game->shadows);
	    destroy_image(game->actor_effects);
	    cleanup_hero(&game->hero);
	    tmx_map_free(game->map_spec.data);
	    free(game);
	}
	
	int main(int argc, char* argv[])
	{
	    return game_loop(create_game, update_game, destroy_game);
	}
