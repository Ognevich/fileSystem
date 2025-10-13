#include "FileSystem.hpp"

FileSystem::FileSystem()
	: root(new Directory("root", nullptr)), 
	currentDir(root),
	parser(std::make_shared<Parser>()),
	programState(ProgramState::RUN_PROGRAM)
{
    util.startMsg();
	initCommands();
}

FileSystem::~FileSystem()
{
	delete root;
}


void FileSystem::initCommands()
{
	commands["pwd"] = [this](std::vector<std::string>& args) {pwd(args); };
	commands["ls"] = [this](std::vector<std::string>& args) {ls(args); };
	commands["mkdir"] = [this](std::vector<std::string>& args) {mkdir(args); };
    commands["rmdir"] = [this](std::vector<std::string>& args) {rmdir(args); };
	commands["exit"] = [this](std::vector<std::string>& args) {exit(args); };
	commands["cd"] = [this](std::vector<std::string>& args) {cd(args); };
    commands["clear"] = [this](std::vector<std::string>& args) {clear(args); };
    commands["help"] = [this](std::vector<std::string>& args) {help(args); };
}

void FileSystem::run()
{
	while (programState != ProgramState::STOP_PROGRAM) {
		update();
	}
}

void FileSystem::update()
{
	std::string line;
	std::cout << currentDir->getPath() << "> ";
	std::getline(std::cin, line);

	std::vector<std::string> args = parser->split(line, ARG_DIVIDER);
	if (args.empty()) {
		return;
	}
	std::string command = args[0];
	args.erase(args.begin());

	if (commands.contains(command)) {
		commands[command](args);
	}
	else {
		std::cout << "unknown command " << command << "\n";
	}

}

// ADD ABSOLUTE PATH INSTEAD OF RELATIVE
void FileSystem::pwd(std::vector<std::string>& args)
{
	std::cout << currentDir->getName() << std::endl;
}

void FileSystem::ls(std::vector<std::string>& args)
{
	std::vector<Directory*> subdirectories = currentDir->getSubdirectories();

	for (auto it = subdirectories.begin(); it != subdirectories.end(); ++it) {
		std::cout << (*it)->getName() << "\t";
	}
	std::cout << "\n";
}

void FileSystem::mkdir(std::vector<std::string>& args)
{

	if (args.empty())
	{
		std::cout << "no argument specified" << "\n";
		return;
	}
	
    std::string path = args[0];

    Directory* startDir = (path[0] == SLASH_DIVIDER) ? root : currentDir;
    std::vector<std::string> directories = parser->split(path, SLASH_DIVIDER);

    if (directories.empty()) {
        return;
    }

    std::string newFolderName = directories.back();
    directories.pop_back();

    for (const auto& name : directories) {
        if (startDir->isSubdirectoryExists(name)) {
            startDir = startDir->getSubdirectory(name);
        }
    }


	Directory* dir = new Directory(newFolderName, startDir);

    startDir->addDirectory(dir);
}

void FileSystem::rmdir(std::vector<std::string>& args)
{
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

void FileSystem::exit(std::vector<std::string>& args)
{
	programState = ProgramState::STOP_PROGRAM;
}

void FileSystem::clear(std::vector<std::string>& args)
{
    std::cout << "\033[2J\033[H";
}

void FileSystem::help(std::vector<std::string>& args)
{
    std::cout << "\n";
    std::cout << "----------------------------------------------------\n";
    std::cout << "pwd:      print working directory\n";
    std::cout << "ls:       list all subdirectories in current directory\n";
    std::cout << "mkdir:    create new directory\n";
    std::cout << "exit:     close program\n" ;
    std::cout << "clear:    clear console\n";
    std::cout << "cd:       change directory\n" ;
    std::cout << "----------------------------------------------------\n";
    std::cout << "\n";
}

void FileSystem::cd(std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "cd: missing argument\n";
        return;
    }

    const std::string& path = args[0];

    if (path == "/") {
        currentDir = root;
        return;
    }

    if (path == "..") {
        if (currentDir != root) {
            currentDir = currentDir->getParent();
        }
        return;
    }

    Directory* startDir = (path[0] == SLASH_DIVIDER) ? root : currentDir;

    std::vector<std::string> directories = parser->split(path, SLASH_DIVIDER);
    if (directories.empty()) {
        return;
    }
    Directory* targetDir = navigatePath(startDir, directories);
    if (targetDir != nullptr) {
        currentDir = targetDir;
    }
    else {
        std::cerr << "cd: no such file or directory: " << path << "\n";
    }
}

Directory* FileSystem::navigatePath(Directory* startDir, const std::vector<std::string>& directories) {
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

