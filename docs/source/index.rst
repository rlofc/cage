.. image:: images/cage.png
    :align: right

Welcome to Cage
===============

Cage is an elementary game development library.
It was initially designed and developed to help teach 2D game
development using the C programming language.
Cage prefers readability over flexibility and ease-of-use over
a rich feature set, in the spirit of **less is more**.


.. raw:: html

    <hr/>

    <iframe src="http://ghbtns.com/github-btn.html?user=rlofc&repo=cage&type=watch&count=true&size=large"
      allowtransparency="true" frameborder="0" scrolling="0" width="160px" height="30px"></iframe>

    <iframe src="http://ghbtns.com/github-btn.html?user=rlofc&repo=cage&type=fork&count=true&size=large"
      allowtransparency="true" frameborder="0" scrolling="0" width="156px" height="30px"></iframe>


    <hr/>


As a library, Cage is just a thin layer on top of SDL2,
the Simple Direct-media Library. Cage offers the essential
constructs for developing 2D games. It lets you handle images,
sprites, animations, fonts, sounds and other game-specific
entities using a clear and straighforward API.

The short version
-----------------

Here is one of the shortest and most boring game you can write using Cage:

.. highlight:: c

::

    void* create(void)
    {
        return (void*)create_font("font.png");
    }

    void update(void* data, float elapsed_ms)
    {
        draw_text((font*)data, "Hello, World", xy(0, 0));
    }

    void destroy(void* data)
    {
        destroy_font((font*)data);
    }

    int main(int argc, char ** argv)
    {
        return game_loop(create, update, destroy);
    }


Yes, there are easier ways to write games, and C may not look like
the best choice. There is no `but` here. LÖVE2D, HaxeFlixer and
Cocos2D are fine examples.

However, if you enjoy the beauty of C, if you want minimal cognitive burden
and if you want to have long-living, portable code, then Cage could be
a viable option.

For the full story all at once, jump over to :doc:`wizard`.
Or, follow along with the docs and learn Cage step by step.

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
   keyboard
   mouse
   screen
   state_sample
   image_sample
   sprite_sample
   timeline_sample
   callout_sample
   collisions_sample
   wizard
   android
   advanced
