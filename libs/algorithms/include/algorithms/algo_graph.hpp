#ifndef ALGO_GRAPH_HPP_
#define ALGO_GRAPH_HPP_

#include <unordered_map>
#include <string>
#include <vector>

typedef std::unordered_map<std::string, std::vector<std::string>> AdjacencyList;
namespace algo {
    class Graph {
    private:
        AdjacencyList m_adjacency_list;
        int m_n_nodes;
    public:
        Graph();
        ~Graph();
        void add_edge(std::string src, std::string dst);
        void remove_edge(std::string src, std::string dst);
        AdjacencyList get_edges();
        std::vector<std::string> get_nodes();
    };
}


#endif