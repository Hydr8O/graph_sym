#include <graphics/edge.hpp>

graphics::Edge::Edge() {
    m_body = sf::VertexArray(sf::Lines, 2);
}

void graphics::Edge::set_id(int id) {
    m_id = id;
}

void graphics::Edge::set_src_id(int src_id) {
    m_src_id = src_id;
}


void graphics::Edge::set_dst_id(int dst_id) {
    m_dst_id = dst_id;
}

void graphics::Edge::reset_position() {
    m_body[0].position = {0.0f, 0.0f};
    m_body[1].position = {0.0f, 0.0f};
}

void graphics::Edge::set_src_position(sf::Vector2f src_position) {
    m_body[0].position = src_position;
}

void graphics::Edge::set_dst_position(sf::Vector2f dst_position) {
    m_body[1].position = dst_position;
}

const sf::VertexArray &graphics::Edge::get_body() const {
    return m_body;
}

int graphics::Edge::get_src_id() {
    return m_src_id;
}

int graphics::Edge::get_dst_id() {
    return m_dst_id;
}