#ifndef _EXIT_COMMAND_HPP_
#define _EXIT_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class ExitCommand : public Command {
public:

    std::string name() const override { return "exit"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        fs.stopProgram();
    }

};


#endif