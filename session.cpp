#include "session.h"

session::session(tcp::socket socket, boost::asio::io_service& io_service_)
    : socket_(std::move(socket)), deadline_(io_service_)//, deadline_(socket_.get_io_service())
  {
	timeout = 120;
  }

void session::start()
  {
	log_in();
  }

void session::check_deadline()
  {
    if (deadline_.expires_at() <= boost::asio::deadline_timer::traits_type::now())
    {
	std::cout<<"socket delete\n";
      	socket_.close();
      //deadline_.expires_at(boost::posix_time::pos_infin);//
    }

    // Put the actor back to sleep.
    //deadline_.async_wait(boost::bind(&client::check_deadline, this));
  }

void session::do_read()
  {
	deadline_.expires_from_now(boost::posix_time::seconds(timeout));
	deadline_.async_wait(boost::bind(&session::check_deadline, this));

    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),//, max_length
        [this, self](boost::system::error_code ec, std::size_t length)
        {
	  deadline_.cancel();
          if (!ec)
          {
		std::string buf_s(data_);
	
		buf_s = feed_back(buf_s);
		do_write(buf_s.c_str(), buf_s.length());
		//feed_back();
            	//do_write(max_length);//length);
          }
	else{
		std::cout<<"exit\n";	
	}
        });
  }


void session::stop()
  {
    boost::system::error_code ignored_ec;
    socket_.close(ignored_ec);
    deadline_.cancel();
    std::cout<<"socket delete\n";
  }



void session::log_in()
  {
	deadline_.expires_from_now(boost::posix_time::seconds(timeout));
	deadline_.async_wait(boost::bind(&session::check_deadline, this));

	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_),//, max_length
		[this, self](boost::system::error_code ec, std::size_t length)
		{
		  deadline_.cancel();
		  if (!ec)
		  {
			std::string buf_s(data_);
			if(log_in_body(buf_s)){
				do_write(buf_s.c_str(), buf_s.length());
			}
			else{
				std::cout<<"exit\n";
			}
			/*

			std::string bufS(data_);
			if(bufS.find("root 1234") == 0){
				int iter = bufS.find(" ");
				login = bufS.substr(0, iter);
				password = bufS.substr(iter + 1, bufS.find(" "));

				std::cout<<"login:"<<login<<"\npassword:"<<password<<"\n";	
				
				do_write();
				//do_read();
				//feed_back();
			}
			else{
							
			}
			*/
			
		    	//do_write(max_length);//length);
		  }
		else{
			std::cout<<"2exit\n";	
		}
		
		});
  }

  void session::do_write(const char *data_send, std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_send, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
		do_read();
          }
	else{
		std::cout<<"exit\n";
	}
		
        });
  }

/*
void session::feed_back(){
	std::string bufS(data_), sendS = "";
	sendS.resize(max_length);
	if(bufS.find("help") != -1){
		bufS = "\
		commands\n\
		1.help\n\
		2.exit\n\
		3.get login\n\
		4.get password\n";

		sendS.insert(0, bufS);
		do_write(sendS.c_str(), max_length);//
		return;
	}
	if(bufS.find("get login") != -1){
		bufS = this->login;
		sendS.insert(0, bufS);
		do_write(sendS.c_str(), max_length);//
		return;
	}
	if(bufS.find("get password") != -1){
		bufS = this->password;
		sendS.insert(0, bufS);
		do_write(sendS.c_str(), max_length);//
		return;
	}

	if(bufS.find("exit") != -1){
		stop();
		return;
	}
	bufS = "no command\n";
	sendS.insert(0, bufS);
	do_write(sendS.c_str(), max_length);
}
*/