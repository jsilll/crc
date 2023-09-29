#pragma once

#include <graph.hpp>

#include <iostream>

std::vector<std::size_t> KCores(Graph &&g, std::size_t k);

int Driver(const int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <graph file>" << std::endl;
    return EXIT_FAILURE;
  }

  Graph g;

  try {
    g = ReadGraph(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  const auto vertices = KCores(std::move(g), 3);

  for (const auto &v : vertices) {
    std::cout << v << '\n';
  }

  return EXIT_SUCCESS;
}