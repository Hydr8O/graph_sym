#include <graphics/node.hpp>
#include <cmath>
#include <iostream>

Node::Node() {

}

Node::~Node() {

}

void Node::init_position_origin(const std::string& text, const sf::Font& font, sf::Text& text_elem) {
    text_elem.setFont(font);
    text_elem.setString(text);
    sf::FloatRect text_rect = text_elem.getGlobalBounds();
    sf::Vector2f center = {text_rect.width / 2.f, text_rect.height / 2.f};
    sf::Vector2f local_bounds_position = {text_elem.getLocalBounds().left, text_elem.getLocalBounds().top};
    text_elem.setOrigin(center + local_bounds_position);
}

void Node::set_text(const std::string& text, const sf::Font& font) {
    init_position_origin(text, font, m_text);
}

void Node::set_distance(const std::string &distance, const sf::Font &font) {
    init_position_origin(distance, font, m_distance);
}

void Node::set_body(float radius) {
    m_body.setRadius(radius);
    m_body.setOrigin(radius, radius);
}

void Node::set_id(int id) {
    m_id = id;
}

void Node::set_color(sf::Color color) {
    m_body.setFillColor(color);
}

void Node::set_position(float x, float y) {
    m_body.setPosition(x, y);
    m_text.setPosition(x, y);
    sf::FloatRect text_rect = m_text.getGlobalBounds();
    float offset = text_rect.height + m_body.getRadius();
    std::cout << text_rect.height << std::endl;
    m_distance.setPosition(x, y - offset);
}

void Node::init_text_style() {
    m_text.setCharacterSize(35);
    m_text.setFillColor(sf::Color::Red);
    m_distance.setCharacterSize(30);
    m_distance.setFillColor(sf::Color::Green);
}

sf::Text Node::get_text() const {
    return m_text;
}

sf::Text Node::get_distance_text() const {
    return m_distance;
}

sf::CircleShape Node::get_body() const {
    return m_body;
}

int Node::get_id() const {
    return m_id;
}

bool Node::clicked(float x, float y) {
    float distance = hypot((x - m_body.getPosition().x), (y - m_body.getPosition().y));
    if (distance <= m_body.getRadius()) {
        return true;
    }
    return false;
}