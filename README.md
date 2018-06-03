![CAGE](https://raw.githubusercontent.com/rlofc/rlofc.github.com/master/cage/_images/cage.png) (CAGE Ain't a Game Engine)
=============================================================================================

CAGE is an elementary game development library, written in the spirit of less is more (or
worse is better). CAGE favors readability over flexibility and
ease-of-use over a rich set of features (read: it's barely
usable).

![CAGE Screenshots](https://github.com/rlofc/rlofc.github.com/raw/master/cage/_images/cage-samples.png)

CAGE makes it easier to write 2D games using C by
adding a very thin layer on top of SDL2.
CAGE has just enough to help you build your game faster,
but if you want to, it lets you to reach inside and hack anything you need.

I initially wrote CAGE to help me teach my kids game development using
C. I wanted to have a native library by which I can introduce them
to the nuts and bolts of software engineering.
While still trying to do so, I'm now also using the library
to write actual games, the first being
[Spy Game Over](https://forums.tigsource.com/index.php?topic=52287.0).

### Highlights

* Plain C - No abstractions, no distractions.
* Easy to learn - Simple, readable and well documented code.
* Useful samples - Code you can learn from and use in your own games.
* It's just a library - You are in control. Hack, mix-in,
  and bring your own libraries. It's your code.
* SDL2 inside - Runs on **Windows**, **Linux**, **Mac/OSX**, **iOS** and **Android**, can potentially do anything SDL can

### Library Features

* Sprite animation - Animate sequences of frames in image files.
* Timelines - Sequence Time-driven event callbacks for story-telling and effects.
* Game states - Helps your game have a scalable internal structure.
* Bitmap fonts, sound playback, file reading and
  writing, yada yada.

### Getting Started

First, clone the repo:

    git clone https://github.com/rlofc/cage.git

To use CAGE you will need SDL2, SDL2_Image and SDL2_Mixer.

For **Windows**, run `getSDL2.bat` inside the `3rdparty` folder.

If you're using **Mac OS/X**, you can use brew:

    brew install SDL2 SDL2_Image SDL2_Mixer

In **Arch Linux**, use pacman:

    sudo pacman -S sdl2 sdl2_image sdl2_mixer


Once you have SDL2, SDL2_Mixer and SDL2_Image, you can build CAGE and run the
Wizard sample.

In **Windows**, open the Visual Studio 2013 project inside the `vc` folder of CAGE
and build the solution. You will find the Wizard executable inside `vc\Debug` or `vc\Release`.

In **Mac OS/X** or **Linux**, simply:

    cd cage && make
    

### Documentation

The docs are still work-in-progress:

[http://rlofc.github.io/cage/docs](http://rlofc.github.io/cage/)

All samples are written using using literate programming.

For a not-so-basic example, check out the Wizard sample code:
[http://rlofc.github.io/cage/wizard.html](http://rlofc.github.io/cage/wizard.html)

### License

CAGE is licensed under the **zlib license**.
