#include <graph.hpp>

#include <boost/graph/graphviz.hpp>

#include <iostream>

int main(const int argc, const char *argv[]) noexcept {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <graph file>\n";
    return EXIT_FAILURE;
  }

  Graph g;

  try {
    g = ReadGraph(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  boost::write_graphviz(std::cout, g);
}