#ifndef STATE_HPP_
#define STATE_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <graphics/edge.hpp>
#include <graphics/modes.hpp>

namespace graphics {

    struct AnimationState {
        int current_animating_node = 0;
        bool animation = false;
        int red = 255, green = 255;
        sf::Color animation_color;
        float duration;
    };

    struct AlgorithmState {
        std::string starting_vertex = "1";
    };

    class State {
    private:
        
    public:
        AnimationState animation_state;
        AlgorithmState algorithm_state;
        int current_selected = -1;
        graphics::Mode current_mode = VertexMode;
        int current_dst = -1;
        bool creation_finished = false;
        bool running_algorithm = false;
        bool ready_to_run_algorithms = false;
        std::shared_ptr<graphics::Edge> current_edge = nullptr; 
        bool src_vertex_selection();
        bool dst_vertex_selection();
        bool edge_connection();
        bool edge_creation();
        bool edge_mode();
        bool vertex_creation();
        bool vertex_mode();
        void set_edge_mode();
        void set_vertex_mode();
    };
}
#endif