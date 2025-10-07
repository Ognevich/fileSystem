#ifndef _FILE_HPP_
#define _FILE_HPP_
#include <iostream>
#include <string>

class File {
private:

	std::string name;
	std::string content;

public:

	File(std::string name, std::string content = "");
	
	std::string getName();

	void write(std::string content);
	void read();

};

#endif