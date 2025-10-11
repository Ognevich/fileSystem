#include "FileSystem.hpp"

FileSystem::FileSystem()
	: root(new Directory("root", nullptr)), 
	currentDir(root),
	parser(std::make_shared<Parser>()),
	programState(ProgramState::RUN_PROGRAM)
{
	initCommands();
}

FileSystem::~FileSystem()
{
	delete root;
}


void FileSystem::initCommands()
{
	commands["pwd"] = [this](std::vector<std::string>& args) {pwd(args); };
	commands["ls"] = [this](std::vector<std::string>& args) {ls(args); };
	commands["mkdir"] = [this](std::vector<std::string>& args) {mkdir(args); };
	commands["exit"] = [this](std::vector<std::string>& args) {exit(args); };
	commands["cd"] = [this](std::vector<std::string>& args) {cd(args); };
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
	std::string command = args[0];
	args.erase(args.begin());

	if (commands.contains(command)) {
		commands[command](args);
	}
	else {
		std::cout << "unknown command " << command << "\n";
	}

}

void FileSystem::pwd(std::vector<std::string>& args)
{
	std::cout << currentDir->getName() << std::endl;
}

void FileSystem::ls(std::vector<std::string>& args)
{
	std::vector<Directory*> subdirectories = currentDir->getSubdirectories();

	for (auto it = subdirectories.begin(); it != subdirectories.end(); ++it) {
		std::cout << (*it)->getName() << "\n";
	}
}

void FileSystem::mkdir(std::vector<std::string>& args)
{
	if (args.empty())
	{
		std::cout << "no argument specified" << "\n";
		return;
	}
	
	Directory* dir = new Directory(args[0], currentDir);

	currentDir->addDirectory(dir);
}

void FileSystem::exit(std::vector<std::string>& args)
{
	programState = ProgramState::STOP_PROGRAM;
}

void FileSystem::cd(std::vector<std::string>& args)
{
	if (args.empty())
	{
		std::cout << "no argument specified" << "\n";
		return;
	}
	
	std::vector<std::string> directories = parser->split(args[0], CD_DIVIDER);

	if (directories[0] == "") {
		directories.erase(directories.begin());
	}

	for (auto it = directories.begin(); it != directories.end(); ++it) {
		if (currentDir->isSubdirectoryExists(*it)) {
			currentDir = currentDir->getSubdirectory(*it);
		}
		else {
			std::cout << "path " << args[0] << " didn't exists" << "\n";
			return;
		}
	}

}
