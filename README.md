![Cage](https://raw.githubusercontent.com/rlofc/cage/gh-pages/cage.png) (Ain't a Game Engine)
=============================================================================================

Cage is an educational game development library that has a naive and simple design, in the spirit of less is 
more (or worse is better). It favors code readability over features (read: it's barely usable)
and should work well for simple, old-school 2D games.

Cage contains and constraints SDL2 so that a beginner game developer will not have to deal with SDL directly.

I wrote Cage to help me teach my kids game programming using C. Avoiding native languages or keeping 
distance from the machine level is not the proper way to teach programming, even for kids. This is why I 
didn't choose Lua or Haxe, even though these are excellent technologies to write an actual game..

### Install

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
    
### Getting Started

Review the (evolving) Wizard sample code:
[http://rlofc.github.io/cage/samples/wizard/doc/src/wizard.html](http://rlofc.github.io/cage/samples/wizard/doc/src/wizard.html)

### Documentation

The generated docs are here:
[http://rlofc.github.io/cage/](http://rlofc.github.io/cage/)

### License

Cage is licensed under the **zlib license**.

