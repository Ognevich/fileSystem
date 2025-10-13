#ifndef _CD_COMMAND_HPP_
#define _CD_COMMAND_HPP_
#include "Command.hpp"
#include "FileSystem.hpp"
#include "Directory.hpp"
#include <iostream>

class CDCommand : public Command {
public:

    std::string name() const override { return "cd"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        if (args.empty()) {
            std::cerr << "cd: missing argument\n";
            return;
        }

        const std::string& path = args[0];

        if (path == "/") {
            fs.setCurrentDir(fs.getRoot());
            return;
        }

        if (path == "..") {
            if (fs.getCurrentDir() != fs.getRoot()) {
                fs.setCurrentDir(fs.getCurrentDir()->getParent());
            }
            return;
        }

        Directory* startDir = (path[0] == SLASH_DIVIDER) ? fs.getRoot() : fs.getCurrentDir();

        std::vector<std::string> directories = fs.getParser()->split(path, SLASH_DIVIDER);
        if (directories.empty()) {
            return;
        }
        Directory* targetDir = navigatePath(startDir, directories);
        if (targetDir != nullptr) {
            fs.setCurrentDir(targetDir);
        }
        else {
            std::cerr << "cd: no such file or directory: " << path << "\n";
        }
    }

    Directory* navigatePath(Directory* startDir, const std::vector<std::string>& directories);

};


#endif