#ifndef SESSION_H
#define SESSION_H

#include "libs.h"
#include "action.h"

class session : public std::enable_shared_from_this<session>, public action
{
public:
  session(tcp::socket socket, boost::asio::io_service& io_service_);

	void start();

private:
	boost::asio::deadline_timer deadline_;

	void check_deadline();

	void do_read();

	void stop();

	void log_in();

	void do_write(const char *data_send, std::size_t length);

  	tcp::socket socket_;
  	enum { max_length = 1024 };
	std::string login = "";
	std::string password = ""; 
  	char data_[max_length];
	
	int timeout;
};

#endif