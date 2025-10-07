#include "Parser.hpp"

std::vector<std::string> Parser::split(const std::string& str)
{
    std::vector<std::string> argv;
    if (str.empty()) return {};  

    std::string word;
    for (char c : str) {
        if (c != ' ') {
            word += c;
        }
        else if (!word.empty()) {
            argv.push_back(word);
            word.clear();
        }
    }

    if (!word.empty())  
        argv.push_back(word);

    return argv;
}

