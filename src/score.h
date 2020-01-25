#pragma once

#include <sstream>

#include "path.h"
#include "engine/files.h"

struct score {
    score() = delete;

    static size_t load() {
        if (engine::files::is_exists(path::score)) {
            std::stringstream ss(engine::files::read_file(path::score));
            size_t value = 0;
            ss >> value;
            return value;
        } else {
            return 0;
        }
    }

    static void save(size_t value) {
        std::stringstream ss;
        ss << value;
        engine::files::write_file(path::score, ss.str());
    }
};
