#include "ccage.hh"
namespace cage {

//----------------------------------------------------------------------------
// Color wrapper implementation
cage_color color::rgb(int r, int g, int b) {
    return cage_color_from_RGB(r, g, b);
}

//----------------------------------------------------------------------------
// Image wrapper implementation
image::image(std::string filename) {
    _image = cage_create_image(filename.c_str());
    if (_image == 0) throw std::runtime_error(cage_get_error_msgs());
}
image::image(int width, int height, cage_color color) {
    _image = cage_create_target_image(width, height, color);
}
image::~image() {
    cage_destroy_image(_image);
}
image::operator cage_image *() const {
    return _image;
}
void image::set_blend_mode(cage_blend_mode blend_mode) {
    cage_set_blend_mode(_image, blend_mode);
}
void image::clear(cage_color color) {
    cage_clear_image(_image, color);
}
void image::draw_on() {
    cage_draw_on_image(_image);
}
void image::draw(int x, int y, cage_rectangle *clip, float angle) {
    cage_draw_image(_image, x, y, clip, angle);
}

//----------------------------------------------------------------------------
// Animation wrapper implementation
animation::animation() {
    _animation = cage_create_animation();
}
animation::~animation() {
    cage_destroy_animation(_animation);
}
animation &animation::add_frame(int index_in_sprite,
                                int duration,
                                void *user_data) {
    cage_add_frame(_animation, index_in_sprite, duration, user_data);
    return *this;
}
animation &animation::loop(int from, int to) {
    _animation->loop_from = from;
    _animation->loop_to = to;
    return *this;
}
animation &animation::mode(cage_animation_mode m) {
    _animation->mode = m;
    return *this;
}
animation::operator cage_animation *() const {
    return _animation;
}
cage_animation *animation::impl() const {
    return _animation;
}

//----------------------------------------------------------------------------
// Sprite wrapper implementation
sprite::sprite(const image &image, int w, int h) {
    _sprite = cage_create_sprite(image, w, h);
}
void sprite::draw(int x, int y) {
    cage_draw_sprite(_sprite, x, y);
}
void *sprite::animate(uint32_t elapsed) {
    return cage_animate_sprite(_sprite, elapsed);
}
void sprite::play(const animation &animation) {
    cage_play_animation(_sprite, animation);
}
sprite::operator cage_sprite *() const {
    return _sprite;
}
cage_sprite *sprite::impl() const {
    return _sprite;
}

//----------------------------------------------------------------------------
// Timeline wrapper implementation
timeline::timeline() {
    _timeline = cage_create_timeline();
}
void *timeline::global_timeline_callback(void *data,
                                         float elapsed,
                                         float progress) {
    timeline *t = static_cast<timeline *>(data);
    auto callback =
        timeline::_callbacks[t->_timeline][t->_timeline->curr_event];
    callback(elapsed, progress);
}
timeline &timeline::append_event(uint32_t wait,
                                 uint32_t duration,
                                 std::function<void(float, float)>
                                     callback) {
    cage_append_event(
        _timeline, wait, duration, timeline::global_timeline_callback);
    timeline::_callbacks[_timeline].push_back(callback);
    return *this;
}
void timeline::update(float elapsed_ms) {
    cage_update_timeline(_timeline, this, elapsed_ms);
}
timeline::~timeline() {
    cage_destroy_timeline(_timeline);
}
std::unordered_map<cage_timeline *,
                   std::vector<std::function<void(float, float)>>>
    timeline::_callbacks;

//----------------------------------------------------------------------------
// Sound wrapper implementation
sound::sound(std::string filename) {
    _sound = cage_create_sound(filename.c_str());
}
sound::~sound() {
    cage_destroy_sound(_sound);
}
void sound::play(int loops) {
    cage_play_sound(_sound, loops);
}
void sound::stop() {
    cage_stop_sound(_sound);
}
void sound::set_volume(float volume) {
    cage_set_volume(_sound, volume);
}
bool sound::is_playing() {
    return cage_is_playing(_sound);
}

//----------------------------------------------------------------------------
// Font wrapper implementation
font::font(std::string filename, int cols, int rows) {
    _font = cage_create_font(filename.c_str(), cols, rows);
}
font::~font() {
    cage_destroy_font(_font);
}
void font::draw_text(std::string text, int x, int y) {
    cage_draw_text(_font, text.c_str(), x, y);
}
void font::measure_text(std::string text, int *x, int *y) {
    cage_measure_text(_font, text.c_str(), x, y);
}

//----------------------------------------------------------------------------
// Screen wrapper implementation
void screen::draw_on() {
    cage_draw_on_screen();
}
void screen::shake(float elapsed_ms) {
    cage_shake_screen(elapsed_ms);
}
void screen::relax(float elapsed_ms) {
    cage_relax_screen(elapsed_ms);
}
}
