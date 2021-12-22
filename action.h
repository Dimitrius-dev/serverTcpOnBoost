#ifndef ACTION_H
#define ACTION_H

#include<string>
#include<mutex>
#include<chrono>
#include<thread>
#include<fstream>
//#include<algorithm>

#include "sql.h"
#include "ftransfer.h"

class action
{
protected:
	action();

	bool log_in_action(std::string &buf_s);//?

	int log_from_bd(std::string& buf_s);

	int feed_back(std::string& buf_s);

	int file_send(std::string& buf_s);

protected:
	std::string login = "";
	std::string password = "";	
	
	//commands:
	std::string com_help(std::string buf_s);
	std::string com_gvpass(std::string buf_s);
	std::string com_gvlogn(std::string buf_s);

	std::mutex mtx;

	enum mode{
		LOGIN = 0,
		COMMAND,
		FILE,
		DISCONNECT
	};

	int next_mode = LOGIN; 
};


#endif