(More) Advanced
===============


Memory Management
-----------------

Cage lets you decide how to manage your game's memory.
Resources such as image, sprite and animation
will usually have a set of **create** and **destroy**
functions you can use, releasing you from explicitly allocating and freeing memory.

Alternatively, you can allocate and free structure memory by yourself
but you will have to initialize and cleanup the resource
internal state.

For example, you can easily create and destroy images like so:

::

    struct image* image;
    image = create_image("res/image.png");

    if (image!=NULL) {
        destroy_image(image);
    }

Or, if you want, you can do:

::

    struct image image;
    // this will work on already allocated image structs
    if (load_image(&image, "res/image.png") == -1) {
        // something went wrong
    }
    // clean up any internally allocated resources
    cleanup_image(&image);


Coding Style
------------
Cage uses a slightly modified version of the Linux kernel
coding style. The main differences are:

* Indentation size is 4 spaces.
* Pointer '*' sign is adjacent to the type and not to the
  variable.
