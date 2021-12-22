#ifndef FTRANSFER_H
#define FTRANSFER_H

#include <iostream>
#include <fstream>
#include <string>

class ftransfer
{
private: 

public:
	ftransfer();

	void open_file(std::string& buf_s, std::string path);

	void create_file(std::string& buf_s, std::string path, std::string type);
};


#endif