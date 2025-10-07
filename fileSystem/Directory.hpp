#ifndef _DIRECTORY_HPP_
#define _DIRECTORY_HPP_
#include <string>
#include <vector>
#include "File.hpp"

class Directory {
private:
	std::string name;
	Directory* parent;
	std::vector<Directory*> subdirectories;
	std::vector<File*> files;

public:

	Directory(std::string name, Directory* parent = nullptr);
	~Directory();

	void setName(std::string name);
	void setParent(Directory* parent = nullptr);

	void addFile(File * file);
	void addDirectory(Directory* dir);

	Directory* getSubdirectory(std::string name);
	Directory* getParent();
	std::string getName();
	std::string getPath();


	bool removeFile(std::string name);
};

#endif