#include "lexer.hpp"

std::vector<std::string> lex(const std::string &input) {
    std::vector<std::string> tokens;
    std::string token;
    std::string::const_iterator it = input.begin();
    char previousType = 0;

    while (it != input.end()) {
        char currentType;

        // Open tags
        if (*it == '{' && it + 1 != input.end()) {
            std::string t;

            // TODO Consider discarding comment tags here

            if (*(it + 1) == '{') {
                t = "{{";
            } else if (*(it + 1) == '%') {
                t = "{%";
            } else if (*(it + 1) == '#') {
                t = "{#";
            }
            if (*(it + 2) == '-') {
                t += "-";
            };
            if (!t.empty()) {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
                it += t.size();
                tokens.push_back(t);
                previousType = 0;
                continue;
            }
        }

        // Close tags
        if ((*it == '}' || *it == '%' || *it == '#') && *(it + 1) == '}') {
            std::string t;

            if (*it == '}') {
                t = "}}";
            } else if (*it == '%') {
                t = "%}";
            } else if (*it == '#') {
                t = "#}";
            }
            if (!t.empty()) {
                it += 2;
                // Absorb whitespace control character, if present
                if (!token.empty() && token != "-") {
                    tokens.push_back(token);
                    token.clear();
                }
                token += t;
                tokens.push_back(token);
                token.clear();
                previousType = 0;
                continue;
            }
        }

        // Greedy symbols
        // TODO Add tests for edge cases (ex: escaped quote, unclosed parens)
        if (*it == '[' || *it == '(' || *it == '"' || *it == '\'') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }

            char match;
            if (*it == '[') {
                match = ']';
            } else if (*it == '(') {
                match = ')';
            } else if (*it == '"') {
                match = '"';
            } else if (*it == '\'') {
                match = '\'';
            }

            token += *it++;
            while (it != input.end() && *it != match) {
                token += *it++;
            }
            if (it != input.end()) {
                token += *it++;
            }

            tokens.push_back(token);
            token.clear();
            previousType = 0;
            continue;
        }

        // Escaped newline
        // TODO Support other escaped chars?
        if (*it == '\\' && *(it + 1) == 'n') {
            it += 2;
            token += '\n';
            previousType = ' ';
            continue;
        }

        // Group everything else by type
        if (std::isalnum(*it) ||
            (previousType == 'a' && (*it == '_' || *it == '-' || *it == '.'))) {
            currentType = 'a'; // alphanumeric
        } else if (std::ispunct(*it)) {
            currentType = 's'; // punct
        } else {
            // TODO Consider erroring on unexpected? Or choosing a different
            // final condition.
            currentType = ' '; // whitespace
        }
        bool isNewType = previousType != currentType;

        if (isNewType && !token.empty()) {
            tokens.push_back(token);
            token.clear();
        }

        token += *it;
        previousType = currentType;
        ++it;
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}