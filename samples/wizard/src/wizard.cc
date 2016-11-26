/* samples / wizard.cc
 * ===================
 */
#include "ccage.hh"

/* This is the C++14 version of the Wizard sample for
 * CAGE, demonstrating how the C API version can be
 * translated to its C++ counterpart.
 * In the C++ version the writer did not have
 * to deal with allocating and freeing resources,
 * as this is done declaratively.
 * The code is also shorted and has some nice
 * modern C++ syntactic sugar.
 */
class title {
  private:
    cage::image _mask{192, 108, cage::color::rgb(50, 50, 50)};
    cage::image _spot{"res/spot.png"};
    cage::image _sprite_map{"res/title.png"};
    cage::sprite _sprite{_sprite_map, 70, 15};
    cage::animation _bling;

  public:
    title() {
        _mask.set_blend_mode(CAGE_MULTIPLY);
        _spot.set_blend_mode(CAGE_ADD);
        _bling.add_frame(0, 500, nullptr)
            .add_frame(5, 100, nullptr)
            .add_frame(4, 100, nullptr)
            .add_frame(3, 100, nullptr)
            .add_frame(2, 100, nullptr)
            .add_frame(1, 100, nullptr)
            .mode(CAGE_FREEZE_LAST_FRAME);
    }
    void slide_in(float progress) {
        cage::rectangle c{0, 0, 192, 108};
        cage::rectangle r{0, 0, 64, 64};
        _mask.clear(cage::color::rgb(255 * progress, 255 * progress,
                                        255 * progress));
        _mask.draw_on();
        _spot.draw(-15, 40, &r, 0);
        cage::screen::draw_on();
        _mask.draw(0, 0, &c, 0);
        _sprite.draw(
            cage_interpolate(-100, 20, progress, cage_circular_ease_out), 10);
    }
    void bling(float elapsed_ms, float progress) {
        _sprite.draw(20, 10);
        if (progress < 0.1) _sprite.play(_bling);
        _sprite.animate(elapsed_ms);
    }
    void slide_out(float progress) {
        _sprite.draw(cage_interpolate(20, 200, progress, cage_circular_ease_in),
                     10);
    }
};

class wizard {
  private:
    cage::image _sprite_map{"res/wizard.png"};
    cage::sprite _sprite{_sprite_map, 32, 32};
    cage::animation _walk_right, _walk_left, _stand, _cast;
    point _pos{0, 57};
    float _speed{0};

  public:
    wizard() {
        static float NO_SPEED = 0;
        static float BRAKE_SPEED_R = 0.1f;
        static float PREP_SPEED_R = 0.25f;
        static float NORMAL_SPEED_R = 0.5f;
        static float BRAKE_SPEED_L = -0.1f;
        static float PREP_SPEED_L = -0.25f;
        static float NORMAL_SPEED_L = -0.5f;

        _walk_right.add_frame(4, 200, &PREP_SPEED_R)
            .add_frame(0, 200, &NORMAL_SPEED_R)
            .add_frame(1, 200, &NORMAL_SPEED_R)
            .add_frame(2, 200, &NORMAL_SPEED_R)
            .add_frame(3, 200, &NORMAL_SPEED_R)
            .add_frame(4, 200, &BRAKE_SPEED_R)
            .loop(1, 4);
        _walk_left.add_frame(15, 200, &PREP_SPEED_L)
            .add_frame(11, 200, &NORMAL_SPEED_L)
            .add_frame(10, 200, &NORMAL_SPEED_L)
            .add_frame(9, 200, &NORMAL_SPEED_L)
            .add_frame(8, 200, &NORMAL_SPEED_L)
            .add_frame(15, 200, &BRAKE_SPEED_L)
            .loop(1, 4);
        _stand.add_frame(5, 100, &NO_SPEED).mode(CAGE_FREEZE_LAST_FRAME);
        _cast.add_frame(5, 200, &NO_SPEED)
            .add_frame(6, 200, &NO_SPEED)
            .add_frame(7, 100, &NO_SPEED)
            .add_frame(6, 200, &NO_SPEED)
            .loop(2, 2);
        _sprite.play(_stand);
    }

    void walk_left() { _sprite.play(_walk_left); }

    void walk_right() { _sprite.play(_walk_right); }

    void stand() { _sprite.play(_stand); }

    void cast() { _sprite.play(_cast); }

    bool is_casting() {
        return _sprite.impl()->active_animation == _cast &&
               _sprite.impl()->current_frame > 1;
    }

    void update(float elapsed) {
        if (cage_key_down(KB_SPACE)) {
            cast();
        } else if (cage_key_down(KB_RIGHT)) {
            walk_right();
        } else if (cage_key_down(KB_LEFT)) {
            walk_left();
        } else {
            stand();
        }
        const void* px = _sprite.animate(elapsed);
        if (px != nullptr) {
            _speed = *((const float*)px);
        }
        _pos.x += _speed;
        _sprite.draw(_pos.x, _pos.y);
    }
};
static const char* LEVEL =
    "             "
    "             "
    "             "
    "             "
    "             "
    "-------------"
    ".............";

class tree {
  private:
    cage::image _sprite_map{"res/tree.png"};
    cage::sprite _sprite{_sprite_map, 32, 32};
    cage::animation _windblow;

  public:
    tree() {
        _windblow.add_frame(0, 1000, nullptr)
            .add_frame(1, 1000, nullptr)
            .loop(0, 1);
        _sprite.play(_windblow);
    }
    void draw(float elapsed_ms) {
        _sprite.animate(elapsed_ms);
        _sprite.draw(100, 56);
    }
};

class my_level : public cage::state {
  private:

    title _title;
    tree _tree;
    wizard _wizard;

    cage::image    _grass_tile;
    cage::image    _earth_tile;
    cage::timeline _intro_timeline;
    cage::sound    _music{"res/wizard.ogg"};
    cage::font     _font{"res/font.png", 32, 4};

  public:
    my_level():
          _grass_tile("res/grass_tile.png"),
          _earth_tile("res/earth_tile.png") {
        _intro_timeline
            .append_event(0, 1000,
                          [this](float e, float p) { _title.slide_in(0); })
            .append_event(0, 1000,
                          [this](float e, float p) { _title.slide_in(p); })
            .append_event(0, 4000,
                          [this](float e, float p) { _title.bling(e, p); })
            .append_event(0, 1000, [this](float e, float p) {
                _title.slide_out(p);
                _music.set_volume(clamp(1.0f - p, 0.2f, 1.0f));
            });
        cage_screen_color(cage::color::rgb(170, 210, 250));
        _music.play(-1);
    }

    void update(float elapsed) override {
        cage::rectangle tile_size = {0, 0, 16, 16};
        for (int i = 0; i < strlen(LEVEL); i++) {
            if (LEVEL[i] != ' ') {
                int x = 16 * (i % 13);
                int y = 16 * (i / 13);
                if (LEVEL[i] == '-') _grass_tile.draw(x, y, &tile_size, 0);
                if (LEVEL[i] == '.') _earth_tile.draw(x, y, &tile_size, 0);
            }
        }
        _tree.draw(elapsed);
        _wizard.update(elapsed);
        if (_wizard.is_casting()) {
            cage::screen::shake(elapsed);
        } else {
            cage::screen::relax(elapsed);
        }
        _intro_timeline.update(elapsed);
        char fps[10];
        sprintf(fps, "FPS:%02.0f", 1000 / elapsed);
        _font.draw_text(fps, 75, 3);

    }
};

int main() {
    return cage::game::start<my_level>();
}
