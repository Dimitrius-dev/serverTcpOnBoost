#ifndef SESSION_H
#define SESSION_H

#include "libs.h"
#include "action.h"
#include "context.h"
#include "iostream"

class session : public std::enable_shared_from_this<session>, public action
{
public:
  session(tcp::socket socket, boost::asio::io_service& io_service_, context& context_);

	void start();

private:
	boost::asio::deadline_timer deadline_;

	context context_use;

	void check_deadline();

	void do_read();

	void log_in();

	void do_write(const char *data_send, std::size_t length);

	void stop();

  	tcp::socket socket_;

	enum { msg_length = 512 };

	char data_[msg_length];
	std::string data_s = "";



	std::string login = "";
	std::string password = ""; 
  	
	
	int timeout;

	std::string flag_stop = "\r\n\r\n";

private:
	void norm_buf(std::string& data_s);

	
};

#endif