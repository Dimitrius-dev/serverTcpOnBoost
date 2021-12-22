#ifndef SQL_H
#define SQL_H

#include <string>
#include <iostream>
#include <pqxx/pqxx>

class sql{

protected:

	std::string config = "host=localhost port=5432 dbname = server user = machine password = d013579b";

public:
	sql();

	std::string get_password(std::string name);
};


#endif