game
================================
Games will usually have different levels, menus, high score
displays and the likes. These are represented as different
gamestate entities.

.. image:: images/cage-gamestates.png
    :align: center

A composition of alternating gamestates make for a complete
game.

.. image:: images/cage-callbacks.png
    :align: center


.. highlight:: c

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
         change_state( prepare_leve, update_level, teardown_level );
     }

     void teardown_menu( void* data )
     {
         // Put any cleamup code here...
     }

     // This is your game!
     int main(int argc, char ** argv)
     {
         // Set up the initial game state
         return gameloop( prepare_menu, update_menu, teardown_menu );
     }

game_loop
---------
.. doxygenfunction:: game_loop

game_state
----------
.. doxygenfunction:: game_state

preparation function
--------------------
.. doxygentypedef:: update_func_t

update function
--------------------
.. doxygentypedef:: teardown_func_t

teardown function
--------------------
.. doxygentypedef:: prepare_func_t

