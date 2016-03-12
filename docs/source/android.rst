CAGE on Android
===============

Pre-requisites
--------------
Before we begin building our SDL2 and libcage project,
make sure you have the Android SDK and NDK
environment properly set up. You should be able
to run ``ndk-build`` and ``adb``,
and you should also have the latest Android SDK
installed using the ``android`` application. [#f1]_


If you want to use a real device to test your game (you probably should),
make sure you can see it using ``adb devices``.

This tutorial also assumes you're running in Linux (Mac OS should
work similar) and optionally, that you can edit and build C files 
using ``make`` ``gcc`` or ``clang``. We will create a Linux build
of our game as well.

Setting up the project
----------------------
Begin by creating your project folders:

.. code-block:: bash

    mkdir my-game && cd my-game; mkdir src deps res build build/android build/linux

Note ``build/android`` and ``build/linux``. You can use the Linux build for
on-going development and the Android build when you want to test the game
on a real device.

Now we will get **SDL2**, **SDL2_image**, **SDL2_mixer** and **CAGE**. We need
everything in its source form to build it using the NDK.

.. code-block:: bash

    hg clone http://hg.libsdl.org/SDL deps/SDL2
    hg clone http://hg.libsdl.org/SDL_image deps/SDL2_image
    hg clone http://hg.libsdl.org/SDL_mixer deps/SDL2_mixer 
    git clone https://github.com/rlofc/cage deps/cage


Coding a basic game
-------------------
Create and edit ``src/game.c``

.. code-block:: c

    #include "cage.h"

    static void* create_game(void)
    {
        screen_color(color_from_RGB(255, 255, 255));
        return create_font("res/font.png", 32, 4);
    }

    static void update_game(void* data, float elapsed_ms)
    {
        draw_text(data, "hello, world", 10, 10);
        UNUSED(elapsed_ms);
    }

    static void destroy_game(void* data)
    {
        destroy_font(data);
    }

    int main(int argc, char* argv[])
    {
        return game_loop(create_game, update_game, destroy_game);
    }

You will also need to put this bitmap font in your game
resources folder, ``my-game/res/``.

.. image:: ../../samples/state/res/font.png
    :width: 128px

(Use right-click and save link as to
download and save the bitmap file)



Building for Android
--------------------

Bootstrapping the build project
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
SDL2 come with a handy build script that we can use to bootstrap
our Android project, but before we can use it, we need to let it know
which Android SDK version to target. This should be the same API version
you chose to install using the ``android`` command and you can run it again
just to make sure.

Now, edit ``deps/SDL2/build-scripts/androidbuild.sh`` and change

.. code-block:: bash

    $ANDROID update project --path $BUILDPATH

to:

.. code-block:: bash

    $ANDROID update project --path $BUILDPATH --target android-{API version}
    
To keep things clean, let's also change the ``BUILDPATH``
to our project's build folder:

.. code-block:: bash

    BUILDPATH="$SDLPATH/build/$APP"

to

.. code-block:: bash

    BUILDPATH="$SDLPATH/../../build/android/$APP"

The script is now ready to bootstrap your build
environment using the SDL2 Android project template files:

.. code-block:: bash

    cd deps/SDL2/build-scripts/
    ./androidbuild.sh com.your.game /dev/null
    cd -

Your game's build project is now in ``my-game/build/android/com.your.game``
and we can now inject the rest of the dependencies into it.

Injecting the dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^
To inject the rest of our build project dependencies, create symbolic files
links for SDL2_image, SDL2_mixer, CAGE, your source file
and your game resources folder:

.. code-block:: bash

    ln -s $(pwd)/deps/SDL2_image build/android/com.your.game/jni/
    ln -s $(pwd)/deps/SDL2_mixer build/android/com.your.game/jni/
    ln -s $(pwd)/deps/cage build/android/com.your.game/jni/
    ln -s $(pwd)/src/game.c build/android/com.your.game/jni/src/
    mkdir build/android/com.your.game/assets
    ln -s $(pwd)/res build/android/com.your.game/assets

This will allow NDK to build everything we need, but we will still need
to tweak the build files.

Tweaking the NDK build files
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Just a few required tweaks before we can run a succesful build.

Edit ``build/android/com.your.game/jni/Android.mk`` and add the following
lines to the beginning of the file:

.. code-block:: bash

    SUPPORT_MOD_MODPLUG := false
    SUPPORT_MOD_MIKMOD := false
    SUPPORT_MP3_SMPEG := false
    SUPPORT_WEBP := false
    include $(call all-subdir-makefiles)

Now edit ``build/android/com.your.game/jni/src/Android.mk`` and make sure
you have the needed ``LOCAL_C_INCLUDES`` added:

.. code-block:: bash

    LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
            $(LOCAL_PATH)/../SDL2_image \
            $(LOCAL_PATH)/../SDL2_mixer \
            $(LOCAL_PATH)/../cage/src

Your game.c files added to ``LOCAL_SRC_FILES``:

.. code-block:: bash

    # Add your application source files here...
    LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
             game.c

And the needed libraries added to ``LOCAL_SHARED_LIBRARIES``:


.. code-block:: bash

    LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer cage


Build and Run
^^^^^^^^^^^^^
Here we go! time to build and install your game on your Android device:

.. code-block:: bash

    cd build/android/com.your.game/jni
    ndk-build -j$(nproc)
    cd ..
    ant debug install


Optional - Build your game for Linux
------------------------------------
To have a smoother workflow, you will probably want to use your
Linux build for on-going development.

Begin by building and installing your project's SDL2 SDL2_image and SDL2_mixer.
**Note: this will replace any previously installed SDL in your system. 
If you already have SDL2, SDL2_image and SDL2_mixer installed and you do not
want to change these, you may skip this step.**
You will still need the source files for the Android build though.

.. code-block:: bash

    for lib in SDL2 SDL2_mixer SDL2_image; do \
        cd deps/$lib; ./autogen.sh && ./configure && \
        make && sudo make install; cd -; done;

**Running autotools will change some files in the SDL2 include folder.
This has to be reverted before you try to build for Android again, otherwise
the NDK build will fail.**

Run:

.. code-block:: bash

    cd deps/SDL2
    hg revert deps/SDL2/include/**
    cd -


Build CAGE:

.. code-block:: bash

    cd deps/cage; make; cd -

If everything went well, you should now have SDL2 and CAGE ready
for Linux game development.

Let's create a simple Makefile:

.. code-block:: makefile

    GAME_BUILD_PATH = build/linux
    GAME_BINARY = game
    include deps/cage/linux.mk


Now ``make`` and try your shiny new game:

.. code-block:: bash

    make && cd build/linux; ./game; cd -


.. rubric:: Footnotes

.. [#f1] You can follow the Pre-requisites instructions in 
         https://wiki.libsdl.org/Android or your platform specific guidelines.
