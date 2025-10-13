#include "FileSystem.hpp"
#include "MkdirCommand.hpp"
#include "pwdCommand.hpp"
#include "RmdirCommand.hpp"
#include "LsCommand.hpp"
#include "HelpCommand.hpp"
#include "ClearCommand.hpp"
#include "CdCommand.hpp"
#include "ExitCommand.hpp"

FileSystem::FileSystem()
	: root(new Directory("root", nullptr)), 
	currentDir(root),
	parser(std::make_shared<Parser>()),
	programState(ProgramState::RUN_PROGRAM)
{
    util.startMsg();
	initCommands();
}

FileSystem::~FileSystem()
{
	delete root;
}


void FileSystem::initCommands()
{
    registerCommand(std::make_unique<MkdirCommand>());
    registerCommand(std::make_unique<PwdCommand>());
    registerCommand(std::make_unique<RmdirCommand>());
    registerCommand(std::make_unique<LsCommand>());
    registerCommand(std::make_unique<HelpCommand>());
    registerCommand(std::make_unique<ClearCommand>());
	registerCommand(std::make_unique<CDCommand>());
	registerCommand(std::make_unique<ExitCommand>());
}

void FileSystem::run()
{
	while (programState != ProgramState::STOP_PROGRAM) {
		update();
	}
}

void FileSystem::update()
{
	std::string line;
	std::cout << currentDir->getPath() << "> ";
	std::getline(std::cin, line);

	std::vector<std::string> args = parser->split(line, ARG_DIVIDER);
	if (args.empty()) {
		return;
	}
	std::string command = args[0];
	args.erase(args.begin());

	if (commands.contains(command)) {
		commands[command]->execute(*this,args);
	}
	else {
		std::cout << "unknown command " << command << "\n";
	}

}

Directory* FileSystem::getRoot()
{
    return root;
}

std::shared_ptr<Parser> FileSystem::getParser()
{
    return parser;
}

Directory* FileSystem::getCurrentDir()
{
    return currentDir;
}

FileSystem::ProgramState FileSystem::getProgramState() {
	return programState;
}

void FileSystem::setCurrentDir(Directory* dir)
{
    currentDir = dir;
}

void FileSystem::stopProgram()
{
	this->programState = ProgramState::STOP_PROGRAM;
}

void FileSystem::registerCommand(std::unique_ptr<Command> cmd)
{
    commands[cmd->name()] = std::move(cmd);
}
