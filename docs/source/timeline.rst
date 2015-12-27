timeline
========

.. highlight:: c

struct timeline
---------------
.. doxygenstruct:: timeline

struct timeline_event
---------------------
.. doxygenstruct:: timeline_event

create_timeline
---------------
.. doxygenfunction:: create_timeline

destroy_timeline
----------------
.. doxygenfunction:: destroy_timeline

append_event
------------
.. doxygenfunction:: append_event

append_events
-------------
.. doxygenfunction:: append_events

update_timeline
---------------
.. doxygenfunction:: update_timeline

init_timeline
-------------
.. doxygenfunction:: init_timeline

pause_timeline
--------------
.. doxygenfunction:: pause_timeline

reset_timeline
--------------
.. doxygenfunction:: reset_timeline

cleanup_timeline
----------------
.. doxygenfunction:: cleanup_timeline

Easing
------

Using easing interpolation functions you can use the progress
argument in the timeline callbacks to create a factor value for
animation effects such as smoothing the motion of a game title
or even bouncing a ball.

.. doxygenfile:: easing.h
