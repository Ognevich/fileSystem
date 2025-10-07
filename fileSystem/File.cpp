#include "File.hpp"

File::File(std::string name, std::string content)
{
	this->name = name;
	this->content = content;
}

std::string File::getName()
{
	return name;
}

void File::write(std::string content)
{
	this->content = content;
}

void File::read()
{
	std::cout << content << "\n";
}
