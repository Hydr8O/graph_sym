#ifndef GRAPH_EVENT_HANDLER_HPP_
#define GRAPH_EVENT_HANDLER_HPP_
#include <memory>
#include <vector>

#include <SFML/Window.hpp>

#include <graphics/graphics_graph.hpp>
#include <graphics/state.hpp>
#include <graphics/edge.hpp>

namespace graphics {
    class GraphEventHandler {
    private:
        graphics::Graph& m_graph;

    public:
        GraphEventHandler(graphics::Graph& graph) 
        : m_graph(graph) {

        };
        void handle_vertex_creation(const sf::Event& event, graphics::State& state, const sf::Font& font, std::unordered_map<int, std::string>& input_fields);
        void handle_src_vertex_selection(const sf::Event& event, graphics::State& state);
        void handle_dst_vertex_selection(const sf::Event& event, graphics::State& state);
        void handle_vertex_deletion(const sf::Event& event, graphics::State& state, std::unordered_map<int, std::string>& input_fields);
        void handle_edge_deletion(const sf::Event& event, graphics::State& state);
        void handle_edge_connection(const sf::Event& event, graphics::State& state, std::unordered_map<int, float>& weight_input_fields);
        void handle_edge_creation(const sf::Event& event, graphics::State& state, const sf::RenderWindow& window);

    };
}



#endif