#include"action.h"
#include<iostream>

action::action(){
}

bool action::log_in_action(std::string& buf_s){	
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
			
			buf_s = "success\n";
			
			mtx.unlock();
			return true;
		}
	}
	file.close();	
	mtx.unlock();
	return false;
}

int action::log_from_bd(std::string& buf_s){
	sql sql_;
	std::string name = "";
	std::string password = "";
	
	int iter = buf_s.find(" ");
	name = buf_s.substr(0,iter);	
	password = buf_s.substr(iter+1, buf_s.length()-9);
	
	//std::cout<<"name: "<<name<<" password: "<<password<<"=\n";
	
	//std::cout<<"sql_password"<<sql_.get_password(name);

	if( password == sql_.get_password(name) ){
		buf_s = "success\n";
		return COMMAND;
	}
	else{
		return DISCONNECT;	
	}
}



int action::feed_back(std::string& buf_s){

	//std::string send_s = "";
	//send_s.resize(max_length);

//------------------------------------------commands:

	if(buf_s.find("help") != std::string::npos){
		buf_s =  com_help(buf_s);
		return COMMAND;
	}
	if(buf_s.find("gvlogn") != std::string::npos){
		buf_s = com_gvlogn(buf_s);
		return COMMAND;
	}
	if(buf_s.find("gvpass") != std::string::npos){
		buf_s = com_gvpass(buf_s);
		return COMMAND;
	}

//------------------------------------------default:
	buf_s = "no command\n";
	return COMMAND;
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



