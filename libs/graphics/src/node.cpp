#include <graphics/node.hpp>
#include <cmath>

Node::Node() {

}

Node::~Node() {

}

void Node::set_text(const std::string& text, const sf::Font& font) {
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(35);
    m_text.setFillColor(sf::Color::Red);
    sf::FloatRect text_rect = m_text.getGlobalBounds();
    sf::Vector2f center = {text_rect.width / 2.f, text_rect.height / 2.f};
    sf::Vector2f local_bounds_position = {m_text.getLocalBounds().left, m_text.getLocalBounds().top};
    m_text.setOrigin(center + local_bounds_position);
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
}

sf::Text Node::get_text() const {
    return m_text;
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