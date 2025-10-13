#ifndef _PWD_COMMAND_HPP_
#define _PWD_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class PwdCommand : public Command {
public:

	std::string name() const override { return "pwd"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        std::cout << fs.getCurrentDir()->getName() << std::endl;
    }

};


#endif