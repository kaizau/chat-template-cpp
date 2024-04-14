// TODO Including lexer for now
#include "../src/lexer.hpp"
#include "../src/parser.hpp"

#include "tests.hpp"

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "  " << node_to_string(node.type) << " { value: " << node.value
       << ", flags: TODO"
       << " }";
    return os;
}

int main(void) {
    for (const Test &test : tests) {
        std::cout << test.name << std::endl;

        std::vector<std::string> tokens = lex(test.content);

        std::vector<Node> nodes = parse(tokens);

        for (const auto &node : nodes) {
            std::cout << node << std::endl;
        }

        // if (tokens != test.expected) {
        //     std::cout << "  \033[1;31m"
        //               << "FAILED"
        //               << "\033[0m" << std::endl;
        //     std::cout << "  expected:" << std::endl;
        //     printVector(test.expected);
        //     std::cout << "  got:" << std::endl;
        //     printVector(tokens);

        //     return 1;
        // }
    }

    // std::cout << "\033[1;32m"
    //           << "All tests passed!"
    //           << "\033[0m" << std::endl;

    return 0;
}