.. image:: images/cage.png
    :align: right

Welcome to Cage
===============
Cage is an educational game development library. 
It is designed and developed to help teach 2D game development using the C programming language.
Cage prefers readability over flexibility and ease-of-use over features, in the spirit of
**less is more**.

Cage is designed to make it easy for poeple with very little
game or graphics development experience to jump right in. 

Internally, Cage contains (and restraints) SDL2, the Simple Direct-media Library.
Apart of knowing it is in there, you will not have to deal with SDL directly.
However, Cage is completely transparent, so you can "reach in" and work
with SDL directly, should you want to.


The short version
-----------------

Here is one of the shortest and most boring game you can write using Cage:

.. highlight:: c

::

    void* prepare( void )
    {
        return (void*)create_font( "font.png" );
    }

    void update( void* data, float elapsed_ms )
    {
        draw_text( (font*)data, "Hello, World", xy( 0, 0 ) );
    }

    void teardown( void* data )
    {
        destroy_font( (font*)data );
    }

    int main(int argc, char ** argv)
    {
        return game_loop( prepare, update, teardown );
    }

Now, if you want the full picture all at once, jump over to :doc:`wizard`.
Or, follow along with the docs and learn Cage "bar by bar". 

.. toctree::
   :hidden:

   start
   game
   image
   font
   sprite
   animate
   timeline
   sound 
   state_sample
   image_sample
   sprite_sample
   timeline_sample
   wizard


