#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <SFML/Graphics.hpp>
#include <math.h>

namespace graphics {
    class Edge {
    private:
        sf::VertexArray m_body;
        int m_id;
        int m_src_id;
        int m_dst_id;
        sf::CircleShape m_direction_shape;
    public:
        Edge();
        void set_src_position(sf::Vector2f src_position);
        void set_dst_position(sf::Vector2f dst_position);
        void set_src_id(int src_id);
        void set_dst_id(int dst_id);
        void set_id(int id);
        bool clicked(float x, float y);
        void reset_position();
        const sf::VertexArray& get_body() const;
        const sf::CircleShape& get_direction_shape() const;

        int get_src_id();
        int get_dst_id();
    };
}


#endif