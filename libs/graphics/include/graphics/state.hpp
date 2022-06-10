#ifndef STATE_HPP_
#define STATE_HPP_

#include <unordered_map>
#include <string>

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