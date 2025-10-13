#include "CdCommand.hpp"

Directory* CDCommand::navigatePath(Directory* startDir, const std::vector<std::string>& directories)
{
    Directory* dir = startDir;

    for (const auto& name : directories) {
        if (name.empty() || name == ".") {
            continue;
        }

        if (name == "..") {
            if (dir->getParent() != nullptr) {
                dir = dir->getParent();
            }
            continue;
        }

        if (dir->isSubdirectoryExists(name)) {
            dir = dir->getSubdirectory(name);
        }
        else {
            return nullptr;
        }
    }

    return dir;
}
