#include <graph.hpp>

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
        g = ReadGraph(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}