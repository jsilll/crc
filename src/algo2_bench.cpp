#include <algo2.hpp>

#include <chrono>
#include <iostream>

int main(const int argc, const char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <graph file> <max k>\n";
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

  std::cout << "k, time\n";
  for (std::size_t i = 1; i <= k; ++i) {
    auto new_g = g;
    const auto start = std::chrono::high_resolution_clock::now();
    const auto vertices = Algo2(std::move(new_g), i);
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << i << ", "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << "ms\n";
    std::cerr << "k = " << i << " done\n";
  }

  return EXIT_SUCCESS;
}