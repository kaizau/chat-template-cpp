#include "../src/lexer.hpp"

#include "tests.hpp"

std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::string> &vec) {
    os << "    {";
    for (const auto &element : vec) {
        os << "\"" << element << "\", ";
    }
    os << "}" << std::endl;
    return os;
}

int main(void) {
    for (const Test &test : tests) {
        std::cout << test.name << std::endl;

        std::vector<std::string> tokens = lex(test.content);

        if (tokens != test.expected) {
            std::cout << "  \033[1;31m"
                      << "FAILED\n"
                      << "\033[0m"
                      << "  expected:\n"
                      << test.expected << "  got:\n"
                      << tokens << std::endl;
            return 1;
        }
    }

    std::cout << "\033[1;32m"
              << "All tests passed!"
              << "\033[0m" << std::endl;

    return 0;
}
