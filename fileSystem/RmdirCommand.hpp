#ifndef _RMDIR_COMMAND_HPP_
#define _RMDIR_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class RmdirCommand : public Command {
public:

    std::string name() const override { return "rmdir"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        if (args.empty())
        {
            std::cout << "no argument specified" << "\n";
            return;
        }
        if (args[0] == "root") {
            std::cout << "you can't delete root directory" << "\n";
            return;
        }
    }

};


#endif