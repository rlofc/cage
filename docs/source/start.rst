Getting Started
===============


Install
-------

First, clone the repo:

::

    git clone https://github.com/rlofc/cage.git

To use Cage you will need **SDL2**, **SDL2_Image** and **SDL2_Mixer**.

For **Windows**, run ``getSDL2.bat`` inside the ``3rdparty`` folder.

If you're using **Mac OS/X**, you can use brew:

::

    brew install SDL2 SDL2_Image SDL2_Mixer

In **Arch Linux**, use pacman:

::

    sudo pacman -S sdl2 sdl2_image sdl2_mixer

Build
-----

Once you have **SDL2**, **SDL2_Mixer** and **SDL2_Image**, you can build Cage and run the
samples.

In **Windows**, open the Visual Studio 2013 project inside the ``vc`` folder of Cage
and build the solution. You will find the samples executable inside ``vc\Debug`` or ``vc\Release``.

In **Mac OS/X** or **Linux**, simply:

::

    cd cage && make

New Games
---------

To start a new game project, clone **cage-bp** (Cage
Boilerplate):

::

    git clone https://github.com/rlofc/cage-bp.git my_game

By default, the boilerplate project is configured to find cage
side-by-side relative to its location, but you can edit the Makefile to change
this.
