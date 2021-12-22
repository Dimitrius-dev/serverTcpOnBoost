#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>

class context
{
private:
	std::string buf; 

public:
	context();

	std::string getBuf();
};


#endif