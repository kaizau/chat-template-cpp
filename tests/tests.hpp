#include <iostream>
#include <string>
#include <vector>

#include "../src/node.hpp"

struct Test {
    std::string name;
    std::string content;
    std::vector<std::string> expected;
};

std::string node_to_string(NodeType nodeType) {
    switch (nodeType) {
    case NodeType::STRING:
        return "String";
    case NodeType::BLOCK_START:
        return "BlockStart";
    case NodeType::BLOCK_END:
        return "BlockEnd";
    case NodeType::VARIABLE_START:
        return "VariableStart";
    case NodeType::VARIABLE_END:
        return "VariableEnd";
    case NodeType::OPERATOR:
        return "Operator";
    case NodeType::KEYWORD:
        return "Keyword";
    case NodeType::IDENTIFIER:
        return "Identifier";
    default:
        return "Unknown";
    }
}

std::vector<Test> tests = {
    {"Variable Interpolation",
     "Hello {{ variable }}",
     {"Hello", " ", "{{", " ", "vxariable", " ", "}}"}},

    {"Block Tag", "{% block %}", {"{%", " ", "block", " ", "%}"}},

    {"For Loop",
     "{% for item in sequence %}",
     {"{%", " ", "for", " ", "item", " ", "in", " ", "sequence", " ", "%}"}},

    {"Endfor Tag", "{% endfor %}", {"{%", " ", "endfor", " ", "%}"}},

    {"Conditional If",
     "{% if condition %}",
     {"{%", " ", "if", " ", "condition", " ", "%}"}},

    {"Endif Tag", "{% endif %}", {"{%", " ", "endif", " ", "%}"}},

    {"Else Tag", "{% else %}", {"{%", " ", "else", " ", "%}"}},

    {"Elif Tag",
     "{% elif condition %}",
     {"{%", " ", "elif", " ", "condition", " ", "%}"}},

    {"Whitespace Control",
     "{{- variable -}}",
     {"{{-", " ", "variable", " ", "-}}"}},

    {"Multiple Statements",
     "{% if condition %}{{ variable }}{% endif %}",
     {"{%", " ", "if", " ", "condition", " ", "%}", "{{", " ", "variable", " ",
      "}}", "{%", " ", "endif", " ", "%}"}},

    {"Nested Control Structures",
     "{% if condition %}{% for item in sequence %}{{ item }}{% endfor %}{% "
     "endif %}",
     {"{%", " ",        "if",    " ",  "condition", " ", "%}",
      "{%", " ",        "for",   " ",  "item",      " ", "in",
      " ",  "sequence", " ",     "%}", "{{",        " ", "item",
      " ",  "}}",       "{%",    " ",  "endfor",    " ", "%}",
      "{%", " ",        "endif", " ",  "%}"}},

    {"String with Special Characters",
     "{{ 'String with special characters: %^&*()' }}",
     {"{{", " ", "'String with special characters: %^&*()'", " ", "}}"}},

    {"Escape Backslash in Single Quoted String",
     R"({{ 'One \n backslash in single' }})",
     {"{{", " ", "'One \\n backslash in single'", " ", "}}"}},

    {"Escape Backslash in Double Quoted String",
     "{{ \"One \n backslash in double\" }}",
     {"{{", " ", "\"One \n backslash in double\"", " ", "}}"}},

    {"Assignment",
     "{% set var = 'value' %}",
     {"{%", " ", "set", " ", "var", " ", "=", " ", "'value'", " ", "%}"}},

    {"Dictionary Access",
     "{{ messages[0]['role'] }}",
     {"{{", " ", "messages", "[0]", "['role']", " ", "}}"}},

    {"Namespace Creation",
     "{% namespace(found=false) %}",
     {"{%", " ", "namespace", "(found=false)", " ", "%}"}},

    {"Namespace Access",
     "{% set ns.found = true %}",
     {"{%", " ", "set", " ", "ns.found", " ", "=", " ", "true", " ", "%}"}},

    // TODO Slicing [1:]

    // TODO
    // {"Arithmetic Operations",
    //  "{{ 4 + 5 * (6 / 3) }}",
    //  {"{{", " ", "4", " ", "+", " ", "5", " ", "*", " ", "(", "6", " ",
    //  "/",
    //   " ", "3", ")", " ", "}}"}},

    //
    // Unsupported
    //

    // {"Escaped Braces",
    //  "This is a string with \\{{ escaped braces \\}}",
    //  {"This is a string with \\{{ escaped braces \\}}"}},

    // {"Variable with Filter",
    //  "{{ variable|filter }}",
    //  {"{{", " ", "variable", "|", "filter", " ", "}}"}},

    // {"Comment Tag",
    //  "{# This is a comment #}",
    //  {"{#", " ", "This is a comment", " ", "#}"}},

    // {"Raw Tag",
    //  "{% raw %}Data{% endraw %}",
    //  {"{%", " ", "raw", " ", "%}", "Data", "{%", " ", "endraw", " ",
    //  "%}"}},

    // {"Include Tag",
    //  "{% include 'template.html' %}",
    //  {"{%", " ", "include", " ", "'template.html'", " ", "%}"}},

    // {"Macro Definition",
    //  "{% macro input(name, value='', type='text') -%}",
    //  {"{%", " ",  "macro", " ", "input", "(", "name",   ",", " ",
    //  "value",
    //   "=",  "''", ",",     " ", "type",  "=", "'text'", ")", " ",
    //   "-%}"}},

    // {"Macro Import",
    //  "{% import 'forms.html' as forms %}",
    //  {"{%", " ", "import", " ", "'forms.html'", " ", "as", " ", "forms",
    //   " ", "%}"}},

    // {"Using Macro from Import",
    //  "{{ forms.input('username') }}",
    //  {"{{", " ", "forms", ".", "input", "(", "'username'", ")", " ",
    //  "}}"}}

    //
    // Real Templates
    //

    // // teknium/OpenHermes-2.5-Mistral-7B
    // "{% for message in messages %}{{'<|im_start|>' + message['role'] +
    // '\\n' + message['content'] + '<|im_end|>' + '\\n'}}{% endfor %}{% if
    // add_generation_prompt %}{{ '<|im_start|>assistant\\n' }}{% endif %}",
    // // mistralai/Mistral-7B-Instruct-v0.2
    // "{{ bos_token }}{% for message in messages %}{% if (message['role']
    // == 'user') != (loop.index0 % 2 == 0) %}{{
    // raise_exception('Conversation roles must alternate
    // user/assistant/user/assistant/...') }}{% endif
    // %}{% if message['role'] == 'user' %}{{ '[INST] ' + message['content']
    // + ' [/INST]' }}{% elif message['role'] == 'assistant' %}{{
    // message['content'] + eos_token}}{% else %}{{ raise_exception('Only
    // user and assistant roles are supported!') }}{% endif %}{% endfor %}",
    // // TheBloke/FusionNet_34Bx2_MoE-AWQ
    // "{%- for idx in range(0, messages|length) -%}\\n{%- if
    // messages[idx]['role'] == 'user' -%}\\n{%- if idx > 1 -%}\\n{{-
    // bos_token + '[INST] ' + messages[idx]['content'] + ' [/INST]'
    // -}}\\n{%- else -%}\\n{{- messages[idx]['content'] + ' [/INST]'
    // -}}\\n{%- endif
    // -%}\\n{% elif messages[idx]['role'] == 'system' %}\\n{{- '[INST]
    // <<SYS>>\\\\n' + messages[idx]['content'] + '\\\\n<</SYS>>\\\\n\\\\n'
    // -}}\\n{%- elif messages[idx]['role'] == 'assistant' -%}\\n{{- ' '  +
    // messages[idx]['content'] + ' ' + eos_token -}}\\n{% endif %}\\n{%
    // endfor %}",
    // // bofenghuang/vigogne-2-70b-chat
    // "{{ bos_token }}{% if messages[0]['role'] == 'system' %}{% set
    // loop_messages = messages[1:] %}{% set system_message =
    // messages[0]['content'] %}{% elif true == true and not '<<SYS>>' in
    // messages[0]['content'] %}{% set loop_messages = messages %}{% set
    // system_message = 'Vous êtes Vigogne, un assistant IA créé par Zaion
    // Lab. Vous suivez extrêmement bien les instructions. Aidez autant que
    // vous le pouvez.' %}{% else %}{% set loop_messages = messages %}{% set
    // system_message = false %}{% endif %}{% for message in loop_messages
    // %}{% if (message['role'] == 'user') != (loop.index0 % 2 == 0) %}{{
    // raise_exception('Conversation roles must alternate
    // user/assistant/user/assistant/...') }}{% endif %}{% if loop.index0 ==
    // 0 and system_message != false %}{% set content = '<<SYS>>\\\\n' +
    // system_message + '\\\\n<</SYS>>\\\\n\\\\n' + message['content'] %}{%
    // else %}{% set content = message['content'] %}{% endif %}{% if
    // message['role'] == 'user' %}{{ '[INST] ' + content.strip() + '
    // [/INST]'
    // }}{% elif message['role'] == 'system' %}{{ '<<SYS>>\\\\n' +
    // content.strip() + '\\\\n<</SYS>>\\\\n\\\\n' }}{% elif message['role']
    // == 'assistant' %}{{ ' '  + content.strip() + ' ' + eos_token }}{%
    // endif
    // %}{% endfor %}",
    // // mlabonne/AlphaMonarch-7B
    // "{% for message in messages %}{{bos_token + message['role'] + '\\n' +
    // message['content'] + eos_token + '\\n'}}{% endfor %}{% if
    // add_generation_prompt %}{{ bos_token + 'assistant\\n' }}{% endif %}",
    // // google/gemma-7b-it
    // "{% if messages[0]['role'] == 'system' %}{{ raise_exception('System
    // role not supported') }}{% endif %}{% for message in messages %}{% if
    // (message['role'] == 'user') != (loop.index0 % 2 == 0) %}{{
    // raise_exception('Conversation roles must alternate
    // user/assistant/user/assistant/...') }}{% endif %}{% if
    // (message['role']
    // == 'assistant') %}{% set role = 'model' %}{% else %}{% set role =
    // message['role'] %}{% endif %}{{ '<start_of_turn>' + role + '\\n' +
    // message['content'] | trim + '<end_of_turn>\\n' }}{% endfor %}{% if
    // add_generation_prompt %}{{'<start_of_turn>model\\n'}}{% endif %}",
    // // OrionStarAI/Orion-14B-Chat
    // "{% for message in messages %}{% if loop.first %}{{ bos_token }}{%
    // endif %}{% if message['role'] == 'user' %}{{ 'Human: ' +
    // message['content'] + '\\n\\nAssistant: ' + eos_token }}{% elif
    // message['role'] == 'assistant' %}{{ message['content'] + eos_token
    // }}{% endif %}{% endfor %}",
    // // openchat/openchat-3.5-0106
    // "{{ bos_token }}{% for message in messages %}{{ 'GPT4 Correct ' +
    // message['role'].title() + ': ' + message['content'] +
    // '<|end_of_turn|>'}}{% endfor %}{% if add_generation_prompt %}{{ 'GPT4
    // Correct Assistant:' }}{% endif %}",
    // // deepseek-ai/deepseek-coder-33b-instruct
    // "{% if not add_generation_prompt is defined %}\n{% set
    // add_generation_prompt = false %}\n{% endif %}\n{%- set ns =
    // namespace(found=false) -%}\n{%- for message in messages -%}\n    {%-
    // if message['role'] == 'system' -%}\n        {%- set ns.found = true
    // -%}\n
    // {%- endif -%}\n{%- endfor -%}\n{{bos_token}}{%- if not ns.found
    // -%}\n{{'You are an AI programming assistant, utilizing the Deepseek
    // Coder model, developed by Deepseek Company, and you only answer
    // questions related to computer science. For politically sensitive
    // questions, security and privacy issues, and other non-computer
    // science questions, you will refuse to answer\\n'}}\n{%- endif %}\n{%-
    // for message in messages %}\n    {%- if message['role'] == 'system'
    // %}\n{{ message['content'] }}\n    {%- else %}\n        {%- if
    // message['role']
    // == 'user' %}\n{{'### Instruction:\\n' + message['content'] +
    // '\\n'}}\n
    // {%- else %}\n{{'### Response:\\n' + message['content'] +
    // '\\n<|EOT|>\\n'}}\n        {%- endif %}\n    {%- endif %}\n{%- endfor
    // %}\n{% if add_generation_prompt %}\n{{'### Response:'}}\n{% endif
    // %}",
};