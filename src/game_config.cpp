#include "game_config.h"
#include "path.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

static int load_int(const char* key, const YAML::Node& node, int def = 0) {
    YAML::Node n = node[key];
    return n.IsScalar() ? n.as<int>() : def;
}

static std::string load_string(const char* key, const YAML::Node& node, const char* def) {
    YAML::Node n = node[key];
    return n.IsScalar() ? n.as<std::string>() : std::string(def);
}

game_config::game_config():
    n(1)
{
    std::ifstream file;
    file.open(path::config);

    if (!file.is_open()) {
        std::cerr
            << "Config file ("
            << path::config
            << ") not found! "
            << "Use defaults"
            << std::endl;

        return;
    }

    YAML::Node config = YAML::Load(file);

    n = load_int("n", config);
    key = load_string("key", config, "none");
}

int game_config::get_n() const {
    return n;
}

const std::string &game_config::get_key() const {
    return key;
}
