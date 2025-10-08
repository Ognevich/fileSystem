#include "FileSystem.hpp"

FileSystem::FileSystem()
	: root(new Directory("root", nullptr)), 
	currentDir(root)
{
	initCommands();
}

FileSystem::~FileSystem()
{
	delete root;
}


void FileSystem::initCommands()
{
	commands["pwd"] = [this]() {pwd(); };
}

void FileSystem::run()
{
	while (true) {
		update();
	}
}

void FileSystem::update()
{
	std::string command;
	std::cout << currentDir->getPath() << "> ";
	std::getline(std::cin, command);

	if (commands.contains(command)) {
		commands[command]();
	}
	else {
		std::cout << "unknown command " << command << "\n";
	}

}

void FileSystem::pwd()
{
	std::cout << currentDir->getName() << std::endl;
}
