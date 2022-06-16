#ifndef STATE_HPP_
#define STATE_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <graphics/edge.hpp>

namespace graphics {
    enum Mode {
        VertexMode, EdgeMode
    };

    class State {
    private:
        
    public:
        Mode current_mode = VertexMode;
        int current_selected = -1;
        int current_dst = -1;
        bool creation_finished = false;
        bool running_bfs = false;
        bool running_dfs = false;
        bool animation = false;
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