#include "parser.hpp"

void strip_previous_whitespace(std::vector<Node> &nodes, std::size_t i) {
    if (i == 0) {
        return;
    }
    Node &node = nodes[i - 1];
    if (node.type != NodeType::STRING) {
        return;
    }
    while (node.value.back() == ' ') {
        node.value.pop_back();
    }
}

std::vector<Node> parse(const std::vector<std::string> &tokens) {
    std::vector<Node> nodes;
    bool inside_block = false;
    bool inside_variable = false;

    for (std::size_t i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];
        if (token == "{%-") {
            inside_block = true;
            strip_previous_whitespace(nodes, i);
            nodes.push_back({NodeType::BLOCK_START, token});
        } else if (token == "{%") {
            inside_block = true;
            nodes.push_back({NodeType::BLOCK_START, token});
        } else {
            nodes.push_back({NodeType::STRING, token});
        }
    }

    return nodes;
}