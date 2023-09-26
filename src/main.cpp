#include <utils.hpp>

#include <iostream>

int main(const int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <graph file>" << std::endl;
        return EXIT_FAILURE;
    }

    Graph g;

    try
    {
        g = ReadGraphMtx(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "Number of vertices: " << boost::num_vertices(g) << std::endl;
    std::cout << "Number of edges: " << boost::num_edges(g) << std::endl;

    return EXIT_SUCCESS;
}