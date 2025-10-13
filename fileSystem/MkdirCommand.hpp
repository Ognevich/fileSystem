#ifndef _MKDIRCOMMAND_HPP_
#define _MKDIRCOMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class MkdirCommand : public Command {
public:	

    // DIVIDE EXECUTE ONTO SMALLER FUNCTIONS

	std::string name() const override { return "mkdir"; }

	void execute(FileSystem& fs, std::vector<std::string>& args) override {


        if (args.empty())
        {
            std::cout << "no argument specified" << "\n";
            return;
        }

        std::string path = args[0];

        Directory* startDir = (path[0] == SLASH_DIVIDER) ? fs.getRoot() : fs.getCurrentDir();
        std::vector<std::string> directories = fs.getParser()->split(path, SLASH_DIVIDER);

        if (directories.empty()) {
            return;
        }

        std::string newFolderName = directories.back();

        directories.pop_back();

        for (const auto& name : directories) {

            if (name == "..") {
                if (startDir->getParent() != nullptr) {
                    startDir = startDir->getParent();
                    continue;
                }
            }

            if (startDir->isSubdirectoryExists(name)) {
                startDir = startDir->getSubdirectory(name);
            }
            else {
                return;
            }
        }

        Directory* dir = new Directory(newFolderName, startDir);

        startDir->addDirectory(dir);

	}

};

#endif
