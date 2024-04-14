# C++ Renderer for LLM Chat Templates

Implements a subset of [Jinja](https://jinja.palletsprojects.com/en/3.1.x/templates/). Just enough to process a [`tokenizer.chat_template`](https://huggingface.co/docs/transformers/chat_templating).

- `lexer.cpp` produces a vector of strings.
- `parser.cpp` builds a vector of nodes representing template logic.
- `renderer.cpp` iterates through the node logic while applying variables.

## Notes

- Templates are simple enough that an AST feels overkill — a flat vector of nodes can describe simple control structures.
- Lexer and parser could potentially be combined, since many nodes are easily identified on the first pass. Not sure if all of them can, however.
