#ifndef NODE_HPP_
#define NODE_HPP_

#include <SFML/Graphics.hpp>
#include <string>

class Node {
private:
    sf::Text m_text;
    sf::CircleShape m_body;
    int m_id;

public:
    Node();
    ~Node();

    void set_text(const std::string& text, const sf::Font& font);
    void set_body(float radius);
    void set_color(sf::Color color);
    void set_position(float x, float y);
    void set_id(int id);

    sf::Text get_text() const;
    sf::CircleShape get_body() const;
    int get_id() const;
    bool clicked(float x, float y);

    
};

#endif