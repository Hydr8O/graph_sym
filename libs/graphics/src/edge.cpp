#include <graphics/edge.hpp>
#include <iostream>
graphics::Edge::Edge() {
    m_body = sf::VertexArray(sf::Lines, 2);
    float direction_shape_radius = 15.f;
    m_direction_shape = sf::CircleShape(direction_shape_radius, 3);
    m_direction_shape.setOrigin(direction_shape_radius, direction_shape_radius);    
}

void graphics::Edge::set_id(int id) {
    m_id = id;
}

void graphics::Edge::set_weight(float weight) {
    m_weight = weight;
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
    sf::Vector2f move_dir = dst_position - m_body[0].position;
    m_direction_shape.setPosition(dst_position - move_dir * 0.5f);
    float angle = atan2(dst_position.y - m_direction_shape.getPosition().y, dst_position.x - m_direction_shape.getPosition().x) * 180 / M_PI;
    m_direction_shape.setRotation(angle - 30.f);
    
}

void graphics::Edge::set_color(const sf::Color& color) {
    m_body[0].color = color;
    m_body[1].color = color;
}

const sf::VertexArray &graphics::Edge::get_body() const {
    return m_body;
}

const sf::CircleShape &graphics::Edge::get_direction_shape() const {
    return m_direction_shape;
}

bool graphics::Edge::clicked(float x, float y) {
    int x1 = m_body[0].position.x;
    int y1 = m_body[0].position.y;
    int x2 = m_body[1].position.x;
    int y2 = m_body[1].position.y;
    float numerator = std::abs((x2 - x1) * (y - y1) - (x - x1) * (y2 - y1));
    float denominator = sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    float distance = numerator / denominator;
    std::cout << distance << std::endl;
    if (distance < 15.f) {
        return true;
    }
    return false;
}

int graphics::Edge::get_src_id() {
    return m_src_id;
}

int graphics::Edge::get_id() {
    return m_id;
}

int graphics::Edge::get_dst_id() {
    return m_dst_id;
}

float graphics::Edge::get_weight() {
    return m_weight;
}