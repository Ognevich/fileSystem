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

#include "Command.hpp"


class FileSystem {
private:
	enum class ProgramState {
		RUN_PROGRAM,
		STOP_PROGRAM
	};

	Directory* root;
	Directory* currentDir;

	std::map<std::string, std::unique_ptr<Command>> commands;

	std::shared_ptr<Parser> parser;
	Util util;
	ProgramState programState;

public:
	FileSystem();
	~FileSystem();

	void initCommands();
	void run();
	void update();

	Directory* getRoot();
	std::shared_ptr<Parser> getParser();
	Directory* getCurrentDir();
	ProgramState getProgramState();
	void setCurrentDir(Directory* dir);
	void stopProgram();

	void registerCommand(std::unique_ptr<Command> cmd);
;
};
#endif

