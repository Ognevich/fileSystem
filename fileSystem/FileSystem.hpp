#ifndef _FILE_SYSTEM_HPP_
#define _FILE_SYSTEM_HPP_
#include "File.hpp"
#include "Directory.hpp"
#include "Parser.hpp"

class FileSystem {
private:

	Directory* root;
	Directory* currentDir;
	Parser parser;

public:
	FileSystem();
	~FileSystem();

	void run();
	void update();
};
#endif

