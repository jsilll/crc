#include <algo1.hpp>

#include <iostream>

int main(const int argc, const char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <graph file> <k>\n";
    return EXIT_FAILURE;
  }

  Graph g;

  try {
    g = ReadGraph(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  std::size_t k = 0;
  try {
    k = std::stoul(argv[2]);
  } catch (const std::exception &e) {
    std::cerr << "Invalid k value: " << argv[2] << '\n';
    return EXIT_FAILURE;
  }

  if (k == 0) {
    std::cerr << "k must be greater than 0\n";
    return EXIT_FAILURE;
  }

  const auto vertices = Algo1(std::move(g), k);

  for (const auto &v : vertices) {
    std::cout << v << '\n';
  }

  return EXIT_SUCCESS;
}