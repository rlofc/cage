.. Cage documentation master file, created by
   sphinx-quickstart on Tue May 20 18:57:03 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Cage's documentation!
================================
Cage is an educational game development library. 
It is designed and developed to help me teach 2D game dev using the C programming language.
Cage prefers readability and simplicity, in the spirit of
**less is more**.

Cage is minimal and has a naive design so people with almost no 
game or graphics development experience can jump right in. Internally, 
Cage contains and restraints SDL2, the Simple Direct-media Library.
However, apart of knowing it is in there you will not have
to deal with SDL directly.

Ease-of-use instead of Flexibility and Features
Transparency, almost no hidden stuff
Still able to reach in

In short
--------
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


Cage Library
------------
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


