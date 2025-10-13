#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_
#include <vector>
#include <string>

class FileSystem;

class Command {

public:

	virtual ~Command() = default;
	virtual void execute(FileSystem& fs, std::vector<std::string>& args) = 0;

	virtual std::string name() const = 0;

};


#endif