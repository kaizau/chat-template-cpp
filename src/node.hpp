#ifndef NODE_HPP
#define NODE_HPP

#include <string>

enum class NodeType {
    STRING,
    BLOCK_START,
    BLOCK_END,
    VARIABLE_START,
    VARIABLE_END,
    OPERATOR,
    KEYWORD,
    IDENTIFIER,
};

struct NodeFlags {
    bool inside_for_loop;
    bool inside_if_true;
    bool inside_if_false;
};

struct Node {
    NodeType type;
    std::string value;
    NodeFlags flags;
};

#endif