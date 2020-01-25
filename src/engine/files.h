#pragma once

#include <fstream>
#include <string>
#include <stdexcept>

namespace engine {
    struct files {
        static bool is_exists(const char *file) {
            std::ifstream ifs(file);
            return static_cast<bool>(ifs);
        }

        static void check_existence(const char *file) {
            std::ifstream ifs(file);
            check_existence(ifs, file);
        }

        static void check_existence(const std::ifstream &ifs, const char *file) {
            if (!ifs) {
                std::string message("file '");
                message.append(file);
                message.append("' not found!");

                throw std::runtime_error(message);
            }
        }

        static std::string read_file(const char *file) {
            std::ifstream ifs(file);

            check_existence(ifs, file);

            return std::string(
                    (std::istreambuf_iterator<char>(ifs)),
                    (std::istreambuf_iterator<char>())
            );
        }

        static void write_file(const char *file, const std::string &text) {
            std::ofstream ofs(file);
            ofs << text;
        }
    };
}
