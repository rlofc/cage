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
    static cage_color rgba(int r, int g, int b, int a);
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
    void draw_off();
    void draw(int x, int y, cage_rectangle *clip, float angle);
    void draw(int x, int y);
    void blend();
    void multiply();
    void add();
    void none();
    int width() const { return _image->width; }
    int height() const { return _image->height; }
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
    animation &freeze_last_frame();

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
    int draw(int x, int y) const;
    void draw_frame(int x, int y, int frame) const;
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
    void reset();
    void pause();
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
    static void get_size(int * w, int * h);
    static void set_blend_mode(cage_blend_mode blend_mode);
};

//----------------------------------------------------------------------------
// Game wrapper
class game {
  public:
    template <typename S>
    static int start() {
        try {
        return cage_game_loop(
            []() -> void * { return new S(); },
            [](void *d, float e) { static_cast<state *>(d)->update(e); },
            [](void *d) { delete static_cast<state *>(d); });
        }
        catch (const std::exception & e) {
            cage_message_box("CAGE", e.what());
        }
    }
};
}

#endif  // CCAGE_HH_INCLUDED
