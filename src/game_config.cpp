#include "game_config.h"
#include "path.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

static int load_int(const char *key, const YAML::Node &node, int def = 0) {
    YAML::Node n = node[key];
    return n && n.IsScalar() ? n.as<int>() : def;
}

static std::string load_string(const char *key, const YAML::Node &node, const char *def) {
    YAML::Node n = node[key];
    return n && n.IsScalar() ? n.as<std::string>() : std::string(def);
}

const game_config & game_config::get() {
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

    key = load_string("key", config, "none");

    vertex_shader = load_string("vertex_shader", config, "shaders/def.vs.glsl");
    fragment_shader = load_string("fragment_shader", config, "shaders/def.fs.glsl");
}

const std::string &game_config::get_key() const {
    return key;
}

const std::string &game_config::get_vertex_shader() const {
    return vertex_shader;
}

const std::string &game_config::get_fragment_shader() const {
    return fragment_shader;
}
