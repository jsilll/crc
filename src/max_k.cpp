#include <algo1.hpp>

#include <iostream>

int main(const int argc, const char *argv[]) {
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

  std::size_t right = 0;
  for (auto v : boost::make_iterator_range(boost::vertices(g))) {
    right = std::max(right, boost::degree(v, g));
  }

  std::size_t left = 1;
  while (left + 1 < right) {
    auto new_g = g;
    std::size_t k = (left + right) / 2;
    const auto cores = Algo1(std::move(new_g), k);
    if (cores.empty()) {
      std::cout << "k = " << k << " is too large\n";
      right = k;
    } else {
      std::cout << "k = " << k << " is good\n";
      left = k;
    }
  }

  std::cout << "k = " << left << " is the answer\n";

  return EXIT_SUCCESS;
}