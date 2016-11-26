#ifndef CCAGE_HH_INCLUDED
#define CCAGE_HH_INCLUDED

#include <functional>
#include <stdexcept>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "cage.h"

namespace cage {

using rectangle = cage_rectangle;

//----------------------------------------------------------------------------
// Color wrapper
class color {
  public:
    static cage_color rgb(int r, int g, int b);
};

//----------------------------------------------------------------------------
// Image wrapper
class image {
  private:
    cage_image *_image;

  public:
    image(std::string filename);
    image(int width, int height, cage_color color);
    virtual ~image();
    operator cage_image *() const;
    void set_blend_mode(cage_blend_mode blend_mode);
    void clear(cage_color color);
    void draw_on();
    void draw(int x, int y, cage_rectangle *clip, float angle);
};

//----------------------------------------------------------------------------
// Animation wrapper
class animation {
  private:
    cage_animation *_animation;

  public:
    animation();
    virtual ~animation();
    animation &add_frame(int index_in_sprite, int duration, void *user_data);
    animation &loop(int from, int to);
    animation &mode(cage_animation_mode m);
    operator cage_animation *() const;
    cage_animation *impl() const;
};

//----------------------------------------------------------------------------
// Sprite wrapper
class sprite {
  private:
    cage_sprite *_sprite;

  public:
    sprite(const image &image, int w, int h);
    void draw(int x, int y);
    void *animate(uint32_t elapsed);
    void play(const animation &animation);
    operator cage_sprite *() const;
    cage_sprite *impl() const;
};

//----------------------------------------------------------------------------
// State wrapper
class state {
  public:
    virtual void update(float elapsed) = 0;
    template <typename S>
    void handoff() {
        cage_game_state(
            []() -> void * { return new S(); },
            [](void *d, float e) { static_cast<state *>(d)->update(e); },
            [](void *d) { delete static_cast<state *>(d); });
    }
};

//----------------------------------------------------------------------------
// Timeline wrapper
class timeline {
  private:
    cage_timeline *_timeline;
    static std::unordered_map<cage_timeline *,
                              std::vector<std::function<void(float, float)>>>
        _callbacks;

  public:
    timeline();

    static void *global_timeline_callback(void *data,
                                          float elapsed,
                                          float progress);
    timeline &append_event(uint32_t wait,
                           uint32_t duration,
                           std::function<void(float, float)>
                               callback);
    void update(float elapsed_ms);
    virtual ~timeline();
};

//----------------------------------------------------------------------------
// Sound wrapper
class sound {
  private:
    cage_sound *_sound;

  public:
    sound(std::string filename);
    virtual ~sound();
    void play(int loops);
    void stop();
    void set_volume(float volume);
    bool is_playing();
};

//----------------------------------------------------------------------------
// Font wrapper
class font {
  private:
    cage_font *_font;

  public:
    font(std::string filename, int cols, int rows);
    virtual ~font();
    void draw_text(std::string text, int x, int y);
    void measure_text(std::string text, int *x, int *y);
};

//----------------------------------------------------------------------------
// Screen wrapper
class screen {
  public:
    static void draw_on();
    static void shake(float elapsed_ms);
    static void relax(float elapsed_ms);
};

//----------------------------------------------------------------------------
// Game wrapper
class game {
  public:
    template <typename S>
    static int start() {
        return cage_game_loop(
            []() -> void * { return new S(); },
            [](void *d, float e) { static_cast<state *>(d)->update(e); },
            [](void *d) { delete static_cast<state *>(d); });
    }
};
}

#endif  // CCAGE_HH_INCLUDED
