#include "game_config.h"
#include "path.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <stdexcept>
#include <iostream>

static int load_int(const char *key, const YAML::Node &node, int def = 0) {
    YAML::Node n = node[key];
    return n && n.IsScalar() ? n.as<int>() : def;
}

static float load_float(const char *key, const YAML::Node &node, float def = 0.0f) {
    YAML::Node n = node[key];
    return n && n.IsScalar() ? n.as<float>() : def;
}

static bool load_bool(const char *key, const YAML::Node &node, bool def = false) {
    YAML::Node n = node[key];
    return n && n.IsScalar() ? n.as<bool>() : def;
}

static std::string load_string(const char *key, const YAML::Node &node, const char *def = "") {
    YAML::Node n = node[key];
    return n && n.IsScalar() ? n.as<std::string>() : std::string(def);
}

const game_config &game_config::get() {
    static game_config instance;
    return instance;
}

game_config::game_config() {
    std::ifstream file;
    file.open(path::config);

    if (!file.is_open()) {
        std::cerr
                << "Config file ("
                << path::config
                << ") not found! "
                << "Used defaults"
                << std::endl;

        return;
    }

    YAML::Node config = YAML::Load(file);

    vertex_shader = load_string("vertex_shader", config, "shaders/def.vs.glsl");
    fragment_shader = load_string("fragment_shader", config, "shaders/def.fs.glsl");
    font = load_string("font", config, "data/font/0.png");

    YAML::Node button_textures = config["button_textures"];
    if (button_textures) {
        buttons = {
                load_string("normal", button_textures, "data/button_normal.png"),
                load_string("hover", button_textures, "data/button_hover.png"),
                load_string("active", button_textures, "data/button_active.png")
        };
    }

    YAML::Node sprites = config["sprites"];
    if (sprites) {
        bird = load_string("bird", sprites);
        back = load_string("back", sprites);
        tube = load_string("tube", sprites);
    }

    show_colliders = load_bool("show_colliders", config);

    YAML::Node text = config["text"];
    if (text) {
        title = load_string("title", text, "Flappy Bird");
        game_over = load_string("game_over", text, "GAME OVER!");
        congratulations = load_string("congratulations", text, "CONGRATULATIONS!");
        about = load_string("about", text, "created by nano");
    }

    tube_step = load_float("tube_step", config, 200.0f);
    bird_speed = load_float("bird_speed", config, 100.0f);
    jump_power = load_float("jump_power", config, 9.5f);
    gravity = load_float("gravity", config, 10.0f);
    distance_range = load_float("distance_range", config, 160.0f);

    std::string font_file_path = load_string("font_config", config, "data/font/font.yaml");
    std::ifstream font_file;
    font_file.open(font_file_path);

    if (!font_file.is_open()) {
        std::cerr
                << "Font file ("
                << font_file_path
                << ") not found! "
                << "Used defaults"
                << std::endl;

        return;
    }

    YAML::Node font_config_data = YAML::Load(font_file);

    font_data = {
            load_int("width", font_config_data),
            load_int("height", font_config_data),
            load_float("size", font_config_data),
            load_float("indent", font_config_data)
    };

    if (font_data.width <= 0) {
        throw std::runtime_error("font width must be greater than 0");
    }

    if (font_data.height <= 0) {
        throw std::runtime_error("font height must be greater than 0");
    }
}

const std::string &game_config::get_vertex_shader() const {
    return vertex_shader;
}

const std::string &game_config::get_fragment_shader() const {
    return fragment_shader;
}

const std::string &game_config::get_font() const {
    return font;
}

const font_config &game_config::get_font_config() const {
    return font_data;
}

const button_textures &game_config::get_button_textures() const {
    return buttons;
}

const std::string &game_config::get_bird() const {
    return bird;
}

const std::string &game_config::get_back() const {
    return back;
}

const std::string &game_config::get_tube() const {
    return tube;
}

bool game_config::get_show_colliders() const {
    return show_colliders;
}

const std::string &game_config::get_title() const {
    return title;
}

const std::string &game_config::get_game_over() const {
    return game_over;
}

const std::string &game_config::get_congratulations() const {
    return congratulations;
}

const std::string &game_config::get_about() const {
    return about;
}

float game_config::get_tube_step() const {
    return tube_step;
}

float game_config::get_bird_speed() const {
    return bird_speed;
}

float game_config::get_jump_power() const {
    return jump_power;
}

float game_config::get_gravity() const {
    return gravity;
}

float game_config::get_distance_range() const {
    return distance_range;
}
