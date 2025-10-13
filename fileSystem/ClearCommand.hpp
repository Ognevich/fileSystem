#ifndef _CLEAR_COMMAND_HPP_
#define _CLEAR_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class ClearCommand : public Command {
public:

    std::string name() const override { return "clear"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        std::cout << "\033[2J\033[H";
    }

};


#endif