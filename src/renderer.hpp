#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "node.hpp"

std::string render(const std::vector<Node>& nodes, const std::unordered_map<std::string, std::string>& variables);

#endif