#pragma once

#include <string>
#include <fstream>
#include <cstdint>

#include <boost/graph/adjacency_list.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

Graph ReadGraph(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open the GMJ file.");
    }

    std::size_t n_vertices, n_edges;
    file >> n_vertices >> n_edges;

    Graph g;
    g.m_vertices.reserve(n_vertices);

    for (std::size_t i = 0; i < n_edges; ++i)
    {
        std::size_t source, target;
        file >> source >> target;
        boost::add_edge(source - 1, target - 1, g);
    }

    file.close();
    return g;
}