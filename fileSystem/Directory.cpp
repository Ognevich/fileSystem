#include "Directory.hpp"

Directory::Directory(std::string name, Directory* parent)
{
	this->name = name;
	this->parent = parent;
}

Directory::~Directory()
{
	for (Directory* dir : subdirectories) {
		delete dir;
	}
	for (File* file : files) {
		delete file;

		}

}

void Directory::setName(std::string name)
{
	this->name = name;
}

void Directory::setParent(Directory* parent)
{
	this->parent = parent;
}

void Directory::addFile(File* file)
{
	files.push_back(file);
}

void Directory::addDirectory(Directory* dir)
{
	subdirectories.push_back(dir);
}

std::vector<Directory*> Directory::getSubdirectories()
{
	return this->subdirectories;
}

Directory* Directory::getSubdirectory(std::string name)
{
	for (Directory* dir : subdirectories) {
		if (dir->name == name) {
			return dir;
		}
	}		
	return nullptr;
}

Directory* Directory::getParent()
{
	return this->parent;
}

std::string Directory::getName() {
	return this->name;
}

std::string Directory::getPath()
{
	if (parent == nullptr) {
		return "/" + name;
	}

	return parent->getPath() + "/" + name;

}

bool Directory::isSubdirectoryExists(std::string name)
{
	for (auto it = subdirectories.begin(); it != subdirectories.end(); ++it) {
		if ((*it)->getName() == name)
			return true;
	}
	return false;
}

bool Directory::removeFile(std::string name)
{
	for (auto it = files.begin(); it != files.end(); ++it) {
		if ((*it)->getName() == name) {
			delete* it;
			files.erase(it);
			return true;
		}
	}
	return false;
}

