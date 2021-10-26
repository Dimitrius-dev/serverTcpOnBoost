#ifndef ACTION_H
#define ACTION_H

#include<string>
#include<mutex>
#include<chrono>
#include<thread>
#include<fstream>

class action
{
protected:
	action();

	bool log_in_body(std::string &buf_s);//?

	std::string feed_back(std::string buf_s);

protected:
	std::string login = "";
	std::string password = "";	
	
	//commands:
	std::string com_help(std::string buf_s);
	std::string com_gvpass(std::string buf_s);
	std::string com_gvlogn(std::string buf_s);

	int max_length = 1024;

	std::mutex mtx;
};


#endif