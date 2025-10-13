#ifndef _RMDIR_COMMAND_HPP_
#define _RMDIR_COMMAND_HPP_

#include "Command.hpp"
#include "FileSystem.hpp"
#include <iostream>

class RmdirCommand : public Command {
public:
    std::string name() const override { return "rmdir"; }

    void execute(FileSystem& fs, std::vector<std::string>& args) override {
        if (!validateArgs(args)) return;

        const std::string& path = args[0];
        if (isRootPath(path)) return;

        Directory* startDir = getStartDirectory(fs, path);
        std::vector<std::string> directories = fs.getParser()->split(path, SLASH_DIVIDER);

        if (directories.empty()) return;

        std::string targetName = directories.back();
        directories.pop_back();

        Directory* targetParent = navigatePath(startDir, directories);
        if (!targetParent) return;

        deleteTarget(targetParent, targetName);
    }

private:
    bool validateArgs(const std::vector<std::string>& args) {
        if (args.empty()) {
            std::cout << "no argument specified\n";
            return false;
        }
        return true;
    }

    bool isRootPath(const std::string& path) {
        if (path == "root" || path == "/") {
            std::cout << "you can't delete root directory\n";
            return true;
        }
        return false;
    }

    Directory* getStartDirectory(FileSystem& fs, const std::string& path) {
        return (path[0] == SLASH_DIVIDER) ? fs.getRoot() : fs.getCurrentDir();
    }

    Directory* navigatePath(Directory* startDir, const std::vector<std::string>& directories) {
        Directory* current = startDir;
        for (const std::string& name : directories) {
            if (name.empty() || name == ".") continue;

            if (name == "..") {
                if (current->getParent()) current = current->getParent();
                continue;
            }

            if (!current->isSubdirectoryExists(name)) {
                std::cout << "rmdir: no such directory: " << name << "\n";
                return nullptr;
            }

            current = current->getSubdirectory(name);
        }
        return current;
    }

    void deleteTarget(Directory* parent, const std::string& name) {
        if (!parent->isSubdirectoryExists(name)) {
            std::cout << "rmdir: no such directory: " << name << "\n";
            return;
        }

        if (parent->deleteDirectory(name)) {
            std::cout << "directory '" << name << "' deleted successfully\n";
        }
        else {
            std::cout << "rmdir error";
        }
    }
};

#endif
