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
	std::cin >> command;
	Directory* dir = new Directory("dir1", root);
	currentDir->addDirectory(dir);
}
