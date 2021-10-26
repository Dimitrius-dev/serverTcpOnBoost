#include "action.h"

action::action(){
}

bool action::log_in_body(std::string &buf_s){	
	
	int iter = buf_s.find(" ");

	this->login = buf_s.substr(0, iter);
	this->password = buf_s.substr(iter + 1, buf_s.find(" "));
	
	if( (this->login == "root")&&(this->password == "1234") ){
		buf_s.clear();
		buf_s.resize(max_length);
		buf_s.insert(0, "success");
		return true;	
	}
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

