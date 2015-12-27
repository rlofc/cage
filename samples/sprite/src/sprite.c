/* samples / sprite.c
 * ==================
 *
 * In this example we create a wizard sprite and a walk cycle
 * animation. We then animate the sprite and draw it on screen.
 */
#include "cage.h"

/* The sprite struct
 * -----------------
 *
 * This is our wizard struct. It holds the wizard
 * sprite resource and the walk cycle animation resource.
 * In this sample, we use a static variable instead of dynamically
 * allocating an instance.
 */
static struct wizard {
    struct sprite* sprite;
    struct animation* walk_cycle;
} wizard = { NULL, NULL };
static void* create_sample(void);
static void destroy_sample(void* data);

/* Prepare the sprite
 * ------------------
 *
 * We use the game state create() function to create the sprite
 * using an image resource, as well as the animation resource
 * for the walk cycle.
 * If no errors are encountered, we proceed to add frames to
 * the walk cycle animation.
 * Finally, we play the animation, making it active for the
 * sprite.
 * Notice the way we use a static variable to hold the wizard
 * struct and use its pointer as the create() function return
 * value.
 */
static void* create_sample(void)
{
    wizard.sprite = create_sprite(create_image("res/wizard.png"), 32, 32);
    if (wizard.sprite == NULL) goto error;
    wizard.walk_cycle = create_animation();
    if (wizard.walk_cycle == NULL)
        goto error;
    else {
        struct frame frames[] = { { 0, 300, NULL },
                                  { 1, 300, NULL },
                                  { 2, 300, NULL },
                                  { 3, 300, NULL } };
        add_frames(wizard.walk_cycle, 4, frames);
        wizard.walk_cycle->loop_from = 0;
        wizard.walk_cycle->loop_to = 3;
    }
    play_animation(wizard.sprite, wizard.walk_cycle);
    return &wizard;
error:
    destroy_sample(&wizard);
    return NULL;
}

/* Animate & draw
 * --------------
 *
 * During the game, the update function uses the wizard
 * data to animate and draw the sprite. The elapsed_ms
 * argument is used by the animate_sprite() function so it
 * can track how long to play each animation frame.
 */
static void update_sample(void* data, float elapsed_ms)
{
    struct wizard* w = data;
    animate_sprite(w->sprite, elapsed_ms);
    draw_sprite(w->sprite, 10, 10);
}

/* Clean-up
 * --------
 *
 * Before exiting a state (or the game), Cage
 * will call the destroy function. Having allocated 3 resources
 * earlier in the create function, now is the time to clean up
 * by matching each create with a destory call.
 */
static void destroy_sample(void* data)
{
    struct wizard* w = data;
    destroy_image(w->sprite->image);
    destroy_sprite(w->sprite);
    destroy_animation(w->walk_cycle);
}

/* Main
 * ----
 *
 * Finally, the game's main function delegates the
 * execution to the game_loop() function together with
 * the 3 state functions we wrote.
 */
int main(void)
{
    return game_loop(create_sample, update_sample, destroy_sample);
}
