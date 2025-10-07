#include "FileSystem.hpp"

FileSystem::FileSystem()
	: root(new Directory("root", nullptr)), 
	currentDir(root)
{
}

FileSystem::~FileSystem()
{
	delete root;
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
	std::vector<std::string> args = parser.split(command);
	for (auto it = args.begin(); it != args.end(); ++it) {
		std::cout << *it << std::endl;
	}
}
