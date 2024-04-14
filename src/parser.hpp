#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "node.hpp"

std::vector<Node> parse(const std::vector<std::string>& tokens);

#endif