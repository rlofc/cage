.. highlight:: c

Game essentials
===============

The heart of almost every game is the game loop. The game
loop processes events, runs the game logic and generates the
game visuals and sounds.  

.. image:: images/cage-callbacks.png
    :align: center

game_loop
---------
.. doxygenfunction:: game_loop

To run its game loop, Cage must have a game state. The
game state is built using three pointers to three functions:

preparation function
--------------------
.. doxygentypedef:: prepare_func_t


update function
--------------------
.. doxygentypedef:: update_func_t


teardown function
--------------------
.. doxygentypedef:: teardown_func_t



The state functions share a common feature - the user data
argument.  The preparation function is reponsible for
populating the user data pointer. The common pattern is to
have a dedicated struct per state that holds all required
state assets. 

The update function will get the same user data pointer
back, so it is able to use it to update and draw the game.

The teardown function will also get the same user data
pointer, this time it will usually use it to clean any
allocated assets.

Games will usually have different levels, menus, high score
displays and the likes. These are represented as different
game states.

.. image:: images/cage-gamestates.png
    :align: center

Transitioning between different states allow you
to have a more complex game structure. Use game_state() to change
the active game state using a new set of state functions:

game_state
----------
.. doxygenfunction:: game_state


For example:

::

     // These are the level state functions
     void* prepare_level( void )
     {
         // Put any level setup and preparation code here...
         return 0
     }

     void update_level( void* data, float elapsed_ms )
     {
         // Update and draw your game
     }

     void teardown_level( void* data )
     {
         // Put any cleanup code here...
     }

     // These are the game menu state functions
     void* prepare_menu( void )
     {
         // Put any menu setup and preparation code here...
         return 0
     }

     void update_menu( void* data, float elapsed_ms )
     {
         // Handle the menu behavior.
         // When ready, switch to the level game state:
         game_state( prepare_leve, update_level, teardown_level );
     }

     void teardown_menu( void* data )
     {
         // Put any cleamup code here...
     }

     // This is your game!
     int main(int argc, char ** argv)
     {
         // Set up the initial game state
         return game_loop( prepare_menu, update_menu, teardown_menu );
     }



