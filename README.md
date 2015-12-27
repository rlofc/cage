![Cage](https://raw.githubusercontent.com/rlofc/rlofc.github.com/master/cage/_images/cage.png) (Cage Ain't a Game Engine)
=============================================================================================

Cage is an elementary game development library.
Cage is minimalist in the spirit of less is more (or
worse is better). It favors readability over flexibility and
ease-of-use over a rich set of features (read: it's barely
usable).

![Cage Screenshots](https://raw.githubusercontent.com/rlofc/rlofc.github.com/master/cage/_images/cage-samples.png) 
Cage should work well for simple, old-school 2D
games. It contains (and constrains) SDL2. This helps beginner
game developers avoid dealing with SDL directly.
However, cage implementation is transparent, so you can still
reach in and hack anything you need.

I initially wrote Cage to help me teach my kids game programming using
C. I wanted to have a native C library so I can introduce them
to the nuts and bolts of software engineering.
So far, that didn't work as well as I hoped it would, but Cage
did prove to be useful in, well, writing games.

### Highlights

* Plain C - No abstractions, no distractions
* Easy to learn - A simple, highly readable programming interface
* Sprites - Animate sequence of frames in image files
* Timelines - Sequence events for animation, story-telling and effects
* Game States - Promotes scalable internal game design
* Bitmap Fonts, Sound playback, yada yada 
* SDL2 inside - Runs on **Windows**, **Linux**, **Mac/OSX**, **iOS** and **Android**, can potentially do anything SDL can

### Getting Started

First, clone the repo:

    git clone https://github.com/rlofc/cage.git

To use Cage you will need SDL2, SDL2_Image and SDL2_Mixer.

For **Windows**, run `getSDL2.bat` inside the `3rdparty` folder.

If you're using **Mac OS/X**, you can use brew:

    brew install SDL2 SDL2_Image SDL2_Mixer

In **Arch Linux**, use pacman:

    sudo pacman -S sdl2 sdl2_image sdl2_mixer


Once you have SDL2, SDL2_Mixer and SDL2_Image, you can build Cage and run the
Wizard sample.

In **Windows**, open the Visual Studio 2013 project inside the `vc` folder of Cage
and build the solution. You will find the Wizard executable inside `vc\Debug` or `vc\Release`.

In **Mac OS/X** or **Linux**, simply:

    cd cage && make
    

### Documentation

The docs are still work-in-progress:

[http://rlofc.github.io/cage/](http://rlofc.github.io/cage/)

Review the (evolving) Wizard sample code (literate
programming style):
[http://rlofc.github.io/cage/wizard.html](http://rlofc.github.io/cage/wizard.html)

### License

Cage is licensed under the **zlib license**.
