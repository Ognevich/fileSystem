#ifndef _FILE_SYSTEM_HPP_
#define _FILE_SYSTEM_HPP_
#include <map>
#include <string>
#include <functional>
#include "File.hpp"
#include "Directory.hpp"
#include "Parser.hpp"


class FileSystem {
private:

	Directory* root;
	Directory* currentDir;
	Parser parser;
	std::map<std::string, std::function<void()>> commands;

public:
	FileSystem();
	~FileSystem();

	void initCommands();
	void run();
	void update();

	void pwd();
};
#endif

