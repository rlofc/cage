/* Copyright (c) 2014, 2015 Ithai Levi @RLofC
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */
#ifndef EASING_H_FES178TS
#define EASING_H_FES178TS

/**
 * Interpolate two values using an easing function
 * @param from start value
 * @param to end value
 * @param amount a value from 0 to 1
 * @param easing one of the following easing functions
 *
 * @return interpolated value
 */
float interpolate(float from, float to, float amount, float (*easing)(float));

/**
 * Function Graph:
 *
 *     |                      _.-'
 *     |                 _,,-'
 *     |             _.-'
 *     |         ,,-'
 *     |    _,-''
 *     |,.-'
 *     +---------------------------
 *
 */
float linear_interpolation(float p);

/**
 * Function Graph:
 *
 *     |                          '
 *     |                        ,'
 *     |                      ,'
 *     |                   _,'
 *     |              _,.-'
 *     | .........--''
 *     +---------------------------
 *
 */
float quadratic_ease_in(float p);

/**
 * Function Graph:
 *
 *     |            _..,----''''---
 *     |        ,,-'
 *     |     ,-'
 *     |   ,'
 *     | ,'
 *     |<
 *     +---------------------------
 *
 */
float quadratic_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                   _,,..--
 *     |                ,-'
 *     |              ,'
 *     |             '
 *     |          _,'
 *     |--....,-''
 *     +---------------------------
 *
 */
float quadratic_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                          '
 *     |                        ,'
 *     |                      ,'
 *     |                   _,'
 *     |              _,.-'
 *     | .........--''
 *     +---------------------------
 *
 */
float cubic_ease_in(float p);

/**
 * Function Graph:
 *
 *     |            _..,----''''---
 *     |        ,,-'
 *     |     ,-'
 *     |   ,'
 *     | ,'
 *     |<
 *     +---------------------------
 *
 */
float cubic_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                   _,,..--
 *     |                ,-'
 *     |              ,'
 *     |             '
 *     |          _,'
 *     |--....,-''
 *     +---------------------------
 *
 */
float cubic_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                          /
 *     |                         /
 *     |                        /
 *     |                      ,'
 *     |                  _,-'
 *     |...________,,..--'
 *     +---------------------------
 *
 */
float quartic_ease_in(float p);

/**
 * Function Graph:
 *
 *     |          _,..,---------...
 *     |     ,,-''
 *     |   ,'
 *     |  /
 *     | /
 *     |`
 *     +---------------------------
 *
 */
float quartic_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                  _..------
 *     |                ,'
 *     |              .-
 *     |              +
 *     |            _/
 *     |..____,,.--'
 *     +---------------------------
 *
 */
float quartic_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                           |
 *     |                           |
 *     |                          /
 *     |                        ,'
 *     |                   _,.-'
 *     |..............--'''
 *     +---------------------------
 *
 */
float quintic_ease_in(float p);

/**
 * Function Graph:
 *
 *     |        __..--'''''''''''--
 *     |    ,-''
 *     |  ,'
 *     | /
 *     ||
 *     ||
 *     +---------------------------
 *
 */
float quintic_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                 _..-------
 *     |               ,'
 *     |              |
 *     |              '
 *     |             /
 *     |..__,,....--'
 *     +---------------------------
 *
 */
float quintic_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                         _,
 *     |                       ,'
 *     |                     ,'
 *     |                 _.-'
 *     |             _.-'
 *     |..._,,..,--''
 *     +---------------------------
 *
 */
float sine_ease_in(float p);

/**
 * Function Graph:
 *
 *     |                  __...----
 *     |            _,.-''
 *     |         ,,'
 *     |     _.-'
 *     |  ,-'
 *     |-'
 *     +---------------------------
 *
 */
float sine_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                      ___..
 *     |                  ,-''
 *     |               ,-'
 *     |             ,-
 *     |        __.-'
 *     |.,----''
 *     +---------------------------
 *
 */
float sine_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                          |
 *     |                         ,'
 *     |                      _,'
 *     |                  _,-'
 *     |          _,.--'''
 *     |__...---''
 *     +---------------------------
 *
 */
float circular_ease_in(float p);

/**
 * Function Graph:
 *
 *     |                 _,,.....,-
 *     |        _,,.---''
 *     |    _,-'
 *     |  ,'
 *     |,'
 *     |/
 *     +---------------------------
 *
 */
float circular_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                  _,..-----
 *     |              ,-''
 *     |             '.
 *     |             ]
 *     |        _,,.-
 *     |_,.---''
 *     +---------------------------
 *
 */
float circular_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                           .
 *     |                           |
 *     |                           |
 *     |                         ,'
 *     |                     _,-'
 *     |..._________.....--''
 *     +---------------------------
 *
 */
float exponential_ease_in(float p);

/**
 * Function Graph:
 *
 *     |       _,.--''''''''''`----
 *     |    ,,'
 *     |  ,'
 *     | /
 *     |.'
 *     ||
 *     +---------------------------
 *
 */
float exponential_ease_out(float p);

/**
 * Function Graph:
 *
 *     1               _,,--'''''--
 *     |              /
 *     |             |
 *     |             |
 *     |            ,'
 *     |..._,,....--
 *     +---------------------------
 *
 */
float exponential_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     1                          )
 *     |                         .'
 *     |                         |
 *     |                         |
 *     |                _..     |
 *     |__...----.   ,--   ;    /
 *     +----------`''-------+--+---
 *     |                    `-
 */
float elastic_ease_in(float p);

/**
 * Function Graph:
 *
 *     | ,--
 *     1 |   `.   <''`.__
 *     | |    :_ ,'      `'------'
 *     | |      '
 *     ||
 *     ||
 *     ||
 *     +---------------------------
 *
 */
float elastic_ease_out(float p);

/**
 * Function Graph:
 *
 *     |             _,\      _.._
 *     1             /   `._,''
 *     |            .'
 *     |            |
 *     |           |
 *     |          .'
 *     |_,,-'';   '
 *     +-------`=+-----------------
 *
 */
float elastic_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     1                          ,
 *     |                        ,'
 *     |                       /
 *     |                     ,'
 *     |                   ,'
 *     |._               ,'
 *     +--`..=------=,,-'----------
 *     |     `'''''
 */
float back_ease_in(float p);

/**
 * Function Graph:
 *
 *     |        _,.------...__
 *     1      ,-'              `--.
 *     |    ,'
 *     |   /
 *     |  /
 *     | /
 *     |/
 *     +---------------------------
 *
 */
float back_ease_out(float p);

/**
 * Function Graph:
 *
 *     |               _,----..
 *     1               /        `-.
 *     |              /
 *     |             |
 *     |             '
 *     |            /
 *     |_          /
 *     +-`.=-----,'----------------
 *     |   ``-''
 */
float back_ease_in_out(float p);

/**
 * Function Graph:
 *
 *     |                        _,.
 *     |                     ,-'
 *     |                    /
 *     |              _    .'
 *     | _._ ,-'-. ,-' `-. |
 *     |-   '     '       '
 *     +---------------------------
 *
 */
float bounce_ease_in(float p);

/**
 * Function Graph:
 *
 *     |         \     `.   ,'. _.
 *     |        | `-.-'  `-'   '
 *     |        /
 *     |       /
 *     |     ,'
 *     |..--'
 *     +---------------------------
 *
 */
float bounce_ease_out(float p);

/**
 * Function Graph:
 *
 *     |                 /\   '_,'/
 *     |                ,' `-'
 *     |              ,'
 *     |          ,'-'
 *     |     .--.|
 *     |,-`.'   '|
 *     +---------------------------
 *
 */
float bounce_ease_in_out(float p);

#endif /* end of include guard: EASING_H_FES178TS */
