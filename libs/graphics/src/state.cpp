#include <graphics/state.hpp>


bool graphics::State::src_vertex_selection() {
    return current_selected == -1 || current_mode == VertexMode;
}

bool graphics::State::dst_vertex_selection() {
    return current_mode == EdgeMode && current_selected != -1 && current_dst == -1;
}

bool graphics::State::edge_connection() {
    return current_selected == -1 && current_dst != -1;
}

bool graphics::State::edge_creation() {
    return current_selected != -1 && current_mode == EdgeMode;
}

bool graphics::State::edge_mode() {
    return current_mode == EdgeMode;
}

bool graphics::State::vertex_mode() {
    return current_mode == VertexMode;
}

bool graphics::State::vertex_creation() {
    return current_selected == -1 && !edge_mode();
}

void graphics::State::set_edge_mode() {
    current_mode = EdgeMode;
}

void graphics::State::set_vertex_mode() {
    current_mode = VertexMode;
}