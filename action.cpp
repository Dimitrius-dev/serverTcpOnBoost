#include"action.h"
#include<iostream>

action::action(){
}

bool action::log_in_body(std::string &buf_s){	
	mtx.lock();	
	//std::this_thread::sleep_for(std::chrono::seconds(20));
	
	std::ifstream file("files/users.txt");

	if (!file.is_open()){
		mtx.unlock();
		return false;
	}

	std::string line = "";
	while(std::getline(file, line)){
		if(buf_s.find(line) != -1){
			file.close();
			
			int iter = line.find(" ");
			this->login = line.substr(0, iter);
			this->password = line.substr(iter + 1, line.find(" "));
			
			buf_s.clear();
			buf_s.resize(max_length);
			buf_s.insert(0, "success");
			
			mtx.unlock();
			return true;
		}
	}
	file.close();	
	mtx.unlock();
	return false;
}



std::string action::feed_back(std::string buf_s){

	std::string send_s = "";
	send_s.resize(max_length);

//------------------------------------------commands:

	if(!buf_s.find("help")){
		send_s.insert(0, com_help(buf_s));
		return send_s;
	}
	if(!buf_s.find("gvlogn")){
		send_s.insert(0, com_gvlogn(buf_s));
		return send_s;
	}
	if(!buf_s.find("gvpass")){
		send_s.insert(0, com_gvpass(buf_s));
		return send_s;
	}

//------------------------------------------default:
	buf_s = "no command";
	send_s.insert(0, buf_s);
	return send_s;
}




std::string action::com_help(std::string buf_s){
	return "\
		commands:\n\
		1.help - get info\n\
		2.gvlogn - get your login\n\
		3.gvpass - get your password\n";
}

std::string action::com_gvlogn(std::string buf_s){
	return this->login;
}

std::string action::com_gvpass(std::string buf_s){
	return this->password;
}



