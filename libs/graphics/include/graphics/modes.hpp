#ifndef MODES_HPP_
#define MODES_HPP_

#include <unordered_map>
#include <string>

namespace graphics {
    enum Mode {
        VertexMode, EdgeMode
    };

    struct Modes {
        Modes();
        std::unordered_map<Mode, std::string> modes;
    };
}

#endif