#ifndef NODE_HPP_
#define NODE_HPP_

#include <SFML/Graphics.hpp>
#include <string>

class Node {
private:
    sf::Text m_text;
    sf::Text m_distance;
    sf::CircleShape m_body;
    int m_id;
    float m_shortest_path;

public:
    Node();
    ~Node();

    void set_text(const std::string& text, const sf::Font& font);
    void set_distance(const std::string& distance, const sf::Font& font);
    void set_body(float radius);
    void set_color(sf::Color color);
    void set_position(float x, float y);
    void set_id(int id);
    void init_position_origin(const std::string &text, const sf::Font &font, sf::Text &text_elem);
    void init_text_style();

    sf::Text get_text() const;
    sf::Text get_distance_text() const;
    sf::CircleShape get_body() const;
    int get_id() const;
    bool clicked(float x, float y);

    
};

#endif