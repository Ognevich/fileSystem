#ifndef _FILE_SYSTEM_HPP_
#define _FILE_SYSTEM_HPP_
#include "File.hpp"
#include "Directory.hpp"

class FileSystem {
private:

	Directory* root;
	Directory* currentDir;

public:
	FileSystem();
	~FileSystem();

	void run();
	void update();
};
#endif

