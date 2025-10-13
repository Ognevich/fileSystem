#ifndef _LS_COMMAND_HPP_
#define _LS_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class LsCommand : public Command {
public:

    std::string name() const override { return "ls"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {

		std::vector<Directory*> subdirectories = fs.getCurrentDir()->getSubdirectories();

		for (auto it = subdirectories.begin(); it != subdirectories.end(); ++it) {
			std::cout << (*it)->getName() << "\t";
		}
		std::cout << "\n";
    }

};


#endif