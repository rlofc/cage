.. highlight:: c

samples / chipmunk.c
======================

This sample demonstrates how to integrate Chipmunk2D with
CAGE. We will draw a set of dynamic tiles on the screen,
allowing the user to select and push any tile using the
mouse and generate 2D collisions.



::

	#include "cage.h"
	#include "chipmunk.h"
Sample setup
------------

For this demo we will use a makeshift tilemap and turn each
tile into a Chipmunk2D body.


::

	
	static const char tile_map[] =
	    "############  ############  ############  ############"
	    "############  ############  ############  ############"
	    "############  ############  ############  ############"
	    "############  ############  ############  ############"
	    "####          ####    ####  ####          ####        "
	    "####          ####    ####  ####          ####        "
	    "####          ####    ####  ####  ######  ############"
	    "####          ############  ####  ######  ############"
	    "####          ############  ####  ######  ############"
	    "####          ############  ####  ######  ############"
	    "####          ############  ####     ###  ####        "
	    "####          ####    ####  ####     ###  ####        "
	    "############  ####    ####  ############  ############"
	    "############  ####    ####  ############  ############"
	    "############  ####    ####  ############  ############"
	    "############  ####    ####  ############  ############";
	#define MAX_TILES (sizeof tile_map / sizeof tile_map[0])
Each tile will hold an a Chipmunk2D body and shape that
we'll need to create individually.
We will also use is_active to indicate the the tile
is one of the # tiles that we need to simulate and draw.


::

	struct tile {
	    cpBody* body;
	    cpShape* shape;
	    bool is_active;
	};
The game state is the top-level data-structure in this sample.
It holds the tiles array, the tile image and the basic
Chipmunk2D entities we'll use, primarily the space entity.


::

	#define N_WALLS 4
	struct state {
	    struct tile tiles[MAX_TILES];
	    struct image* tile_img;
	    cpSpace* space;
	    cpBody* mouse_body;
	    cpConstraint* mouse_joint;
	    cpShape* walls[N_WALLS];
	};
	
	#define GRABBABLE_MASK_BIT (1 << 31)
	cpShapeFilter GRAB_FILTER = { CP_NO_GROUP, GRABBABLE_MASK_BIT,
	                              GRABBABLE_MASK_BIT };
	cpShapeFilter NOT_GRABBABLE_FILTER = { CP_NO_GROUP, ~GRABBABLE_MASK_BIT,
	                                       ~GRABBABLE_MASK_BIT };
	
Preparing the tiles
-------------------

We traverse the tilemap string, detecting any "lit" tile
using the character #. For each "lit" tile, we create a
Chipmunk2D body and position it in screen coordinates.


::

	static void init_tiles(struct state* state)
	{
	    cpFloat radius = state->tile_img->width / 2;
	    cpFloat mass = 1;
	    cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
	    for (unsigned int i = 0; i < strlen(tile_map); i++) {
	        if (tile_map[i] == '#') {
	            state->tiles[i].is_active = true;
	            state->tiles[i].body =
	                cpSpaceAddBody(state->space, cpBodyNew(mass, moment));
	            state->tiles[i].shape = cpSpaceAddShape(
	                state->space,
	                cpCircleShapeNew(state->tiles[i].body, radius, cpvzero));
	            cpShapeSetFriction(state->tiles[i].shape, 0.7);
	            cpVect pp = cpv((i % 54) * 6 + 4, (i / 54) * 6 + 40);
	            cpBodySetPosition(state->tiles[i].body, pp);
	        } else
	            state->tiles[i].is_active = false;
	    }
	}
	
A matching cleanup_tiles function to make sure
we free the chipmunk resources we allocated during
init_tiles(). Remember - Chipmunk2D is not doing any
garbage collection and any time we call one of the New
functions we need to match it with a corresponding Free
call when we're done.


::

	static void cleanup_tiles(struct state* state)
	{
	    for (size_t i = 0; i < MAX_TILES; i++) {
	        if (state->tiles[i].is_active) {
	            cpShapeFree(state->tiles[i].shape);
	            cpBodyFree(state->tiles[i].body);
	        }
	    }
	}
	
Preparing the walls
-------------------
We use 4 lines as walls at the extreme ends of the screen.
Each line becomes a Chipmunk2D static_body.


::

	static void init_walls(struct state* state)
	{
	    int w, h;
	    get_screen_size(&w, &h);
	    cpBody* static_body = cpSpaceGetStaticBody(state->space);
	    cpVect walls[N_WALLS][2] = {{cpv(0, h), cpv(w, h)},
	                                {cpv(0, 0), cpv(0, h)},
	                                {cpv(w, 0), cpv(w, h)},
	                                {cpv(0, 0), cpv(w, 0)}};
	
	    for (int j = 0; j < N_WALLS; j++) {
	        state->walls[j] =
	            cpSegmentShapeNew(static_body, walls[j][0], walls[j][1], 0);
	        cpShapeSetFriction(state->walls[j], 1);
	        cpSpaceAddShape(state->space, state->walls[j]);
	    }
	}
	
We also need to cleanup the walls we created.


::

	static void cleanup_walls(struct state* state)
	{
	    for (int j = 0; j < N_WALLS; j++) {
	        cpShapeFree(state->walls[j]);
	    }
	}
	
create_sample is our game state's initialization function
and will return a fully ready instance of struct state for us
to work with in each frame.


::

	static void* create_sample(void)
	{
	    struct state* state = malloc(sizeof(struct state));
	    state->space = cpSpaceNew();
	    state->tile_img = create_image("res/particle.png");
	    state->mouse_body = cpBodyNewKinematic();
	    init_tiles(state);
	    init_walls(state);
	    return state;
	}
	
Mouse handling is a bit tricky. We want the user to move
tiles using the mouse but because tiles are dynamic bodies
managed by Chipmunk2D, we cannot directly control them.
This is resolved by creating a pivot joint between an
invisible mouse body that we can control and the tile body
that we cannot directly control.


::

	static void apply_mouse_motion(struct state* state)
	{
	    struct mouse m;
	    update_mouse(&m);
	    int w, h;
	    get_screen_size(&w, &h);
	    int x = m.x_position * w;
	    int y = m.y_position * h;
	    cpVect mouse_pos = cpv(x, y);
	    cpVect new_point =
	        cpvlerp(cpBodyGetPosition(state->mouse_body), mouse_pos, 0.25f);
	    cpBodySetVelocity(
	        state->mouse_body,
	        cpvmult(cpvsub(new_point, cpBodyGetPosition(state->mouse_body)),
	                60.0f));
	    cpBodySetPosition(state->mouse_body, new_point);
	    if (m.left_click && state->mouse_joint == NULL) {
	        cpFloat radius = 5.0;
	        cpPointQueryInfo info = { 0 };
	        cpShape* shape = cpSpacePointQueryNearest(state->space, mouse_pos,
	                                                  radius, GRAB_FILTER, &info);
	        if (shape && cpBodyGetMass(cpShapeGetBody(shape)) < INFINITY) {
	            cpVect nearest = (info.distance > 0.0f ? info.point : mouse_pos);
	            cpBody* body = cpShapeGetBody(shape);
	            state->mouse_joint =
	                cpPivotJointNew2(state->mouse_body, body, cpvzero,
	                                 cpBodyWorldToLocal(body, nearest));
	            cpConstraintSetMaxForce(state->mouse_joint, 5000000.0f);
	            cpConstraintSetErrorBias(state->mouse_joint,
	                                     cpfpow(1.0f - 0.15f, 60.0f));
	            cpSpaceAddConstraint(state->space, state->mouse_joint);
	        }
	    }
	    if (m.left_click == false && state->mouse_joint != NULL) {
	        cpSpaceRemoveConstraint(state->space, state->mouse_joint);                                                 
	        cpConstraintFree(state->mouse_joint);                                                               
	        state->mouse_joint = NULL;  
	    }
	}
	
Updating each frame
-------------------

Updating and drawing a frame takes stepping the Chipmunk2D
simulation by the 1/1000s fration of a second passed and
then drawing any active tile using its up-to-date
position.
We then delegate any mouse actions to apply_mouse_motion().


::

	static void update_sample(void* data, float elapsed_ms)
	{
	    struct state* state = data;
	    cpFloat timeStep = elapsed_ms / 1000.0;
	    cpSpaceStep(state->space, timeStep);
	    screen_color(color_from_RGB(244, 244, 244));
	    for (size_t i = 0; i < MAX_TILES; i++) {
	        if (state->tiles[i].is_active) {
	            cpVect pos = cpBodyGetPosition(state->tiles[i].body);
	            draw_image(state->tile_img, pos.x - state->tile_img->width / 2,
	                       pos.y - state->tile_img->height / 2, NULL, 0);
	        }
	    }
	    apply_mouse_motion(state);
	}
	
Cleanup
-------

Clean up is simple enough. Just destroy the tile
image and free the state structure memory.


::

	static void destroy_sample(void* data)
	{
	    struct state* state = data;
	    cleanup_walls(state);
	    cleanup_tiles(state);
	    destroy_image(state->tile_img);
	    cpBodyFree(state->mouse_body);
	    cpSpaceFree(state->space);
	    free(data);
	}
	
Main
----

The usual game_loop call, using the usual state
functions.


::

	int main(void)
	{
	    return game_loop(create_sample, update_sample, destroy_sample);
	}
