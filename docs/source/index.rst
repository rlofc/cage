.. image:: images/cage.png
    :align: right

Welcome to Cage
===============

Cage is an elementary game development library.
It is designed and developed to help teach 2D game development using the C programming language.
Cage prefers readability over flexibility and ease-of-use over a rich feature set, in the spirit of
**less is more**.


.. raw:: html

    <hr/>

    <iframe src="http://ghbtns.com/github-btn.html?user=rlofc&repo=cage&type=watch&count=true&size=large"
      allowtransparency="true" frameborder="0" scrolling="0" width="160px" height="30px"></iframe>

    <iframe src="http://ghbtns.com/github-btn.html?user=rlofc&repo=cage&type=fork&count=true&size=large"
      allowtransparency="true" frameborder="0" scrolling="0" width="156px" height="30px"></iframe>


    <hr/>


Cage aims to make it easier for beginner game developers to write games in C,
emphasizing **beginner** and **C**.

Internally, Cage contains (and restraints) SDL2, the Simple Direct-media Library.
Apart of knowing it is in there, you will not have to deal with SDL directly.
However, Cage is completely transparent, so you can "reach in" and work
with SDL directly, should you want to.


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


Granted, there are far better ways to write actual games.
If C gives you the shivers, Lua and Haxe are excellent
alternatives that have great game development toolkits. If
you are not a beginner, you may want to work with SDL2
(or Allegro) directly, with no "bars" between you and the raw toolkit.

However, if you enjoy the beauty of C and want minimal cognitive burden
than Cage is a viable option.

For the full picture all at once, jump over to :doc:`wizard`.
Or, follow along with the docs and learn Cage, bar by bar (pun intended).

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
   state_sample
   image_sample
   sprite_sample
   timeline_sample
   callout_sample
   collisions_sample
   wizard
   advanced


