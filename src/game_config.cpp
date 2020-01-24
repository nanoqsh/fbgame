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

static std::string load_string(const char *key, const YAML::Node &node, const char *def) {
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
