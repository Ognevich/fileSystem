#ifndef _FILE_SYSTEM_HPP_
#define _FILE_SYSTEM_HPP_
#include <map>
#include <string>
#include <memory>
#include <functional>
#include "Util.hpp"
#include "Config.hpp"
#include "File.hpp"
#include "Directory.hpp"
#include "Parser.hpp"

class FileSystem {
private:
	enum class ProgramState {
		RUN_PROGRAM,
		STOP_PROGRAM
	};

	Directory* root;
	Directory* currentDir;
	std::map < std::string, std::function<void(std::vector<std::string>&) >> commands;

	std::shared_ptr<Parser> parser;
	Util util;
	ProgramState programState;

public:
	FileSystem();
	~FileSystem();

	void initCommands();
	void run();
	void update();

	// COMMANDS
	void pwd(std::vector<std::string>& args);
	void ls(std::vector<std::string>& args);
	void mkdir(std::vector<std::string>& args);
	void rmdir(std::vector<std::string>& args);
	void exit(std::vector<std::string>& args);
	void clear(std::vector<std::string>& args);
	void help(std::vector<std::string>& args);
	void cd(std::vector<std::string>& args);
	Directory* navigatePath(Directory* startDir, const std::vector<std::string>& directories);
};
#endif

