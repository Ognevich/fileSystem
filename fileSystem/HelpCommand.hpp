#ifndef _HELP_COMMAND_HPP_
#define _HELP_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class HelpCommand : public Command {
public:

    std::string name() const override { return "help"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        std::cout << "\n";
        std::cout << "----------------------------------------------------\n";
        std::cout << "pwd:      print working directory\n";
        std::cout << "ls:       list all subdirectories in current directory\n";
        std::cout << "mkdir:    create new directory\n";
        std::cout << "exit:     close program\n";
        std::cout << "clear:    clear console\n";
        std::cout << "cd:       change directory\n";
        std::cout << "----------------------------------------------------\n";
        std::cout << "\n";
    }

};


#endif