#include "session.h"

session::session(tcp::socket socket, boost::asio::io_service& io_service_, context& context_)
    : socket_(std::move(socket)), deadline_(io_service_), context_use(context_)//, deadline_(socket_.get_io_service())
  {
	timeout = 120;//120 seconds
  }

void session::start()
  {
	//std::cout<<"special message: "<<context_use.getBuf()<<'\n';
	
	//log_in_header();

/*
	std::cout<<"debug-----\n";
	std::cout<<"data_: "<<data_<<"\n";
	std::cout<<"data_s: "<<data_s<<"\n";
	std::cout<<"----------\n";	
*/
	memset(data_,' ', msg_length);

	do_read();
  }

void session::check_deadline()
  {
    if (deadline_.expires_at() <= boost::asio::deadline_timer::traits_type::now())
    {
	data_s.clear();	
	
	std::cout<<"socket delete\n";
      	socket_.close();
      //deadline_.expires_at(boost::posix_time::pos_infin);//
    }

    // Put the actor back to sleep.
    //deadline_.async_wait(boost::bind(&client::check_deadline, this));
  }


//-----------------------------------------------------


void session::do_read()
  {
	deadline_.expires_from_now(boost::posix_time::seconds(timeout));
	deadline_.async_wait(boost::bind(&session::check_deadline, this));

	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_, msg_length),//, max_length
	        [this, self](boost::system::error_code ec, std::size_t){

		deadline_.cancel();
		if (!ec){
			//editable part begin
			
			std::string buf_s = "";
			
			buf_s.assign(data_, msg_length);
			memset(data_,' ', msg_length);	
	
			data_s.append(buf_s);


			if(buf_s.find(flag_stop) != std::string::npos){

				norm_buf(data_s);				
				
				std::cout<<"message: !"<<data_s<<"!\n";
				std::cout<<"length of message: !"<<data_s.length()<<"!\n";
				
				std::cout<<"end\n";//-------------------------fesfsef

				switch(next_mode){
					default:
						break;
					case LOGIN:
						next_mode = log_from_bd(data_s);
						break;
					case COMMAND:
						next_mode = feed_back(data_s);
						break;
					case FILE:
						next_mode = file_send(data_s);
						break;
				}
				
				if(next_mode != DISCONNECT){
					do_write(data_s.c_str(), data_s.length());
				}
				else{
					std::cout<<"3exit\n";				
				}
		
			}
			else{ 
				do_read();
			}			

			//editable part end
		}
		else{
			std::cout<<"exit\n";	
		}
        });
}


void session::norm_buf(std::string& data_s){
	if( (data_s[data_s.length() - 1] != ' ') && (data_s[data_s.length() - 1] != '\n') && (data_s[data_s.length() - 1] != '\r') ){
		data_s.append(" ");
	}

	int st = 0;
	int end = 0;
	bool first = true;
	for(int i = 0; i<data_s.length(); i++){
		
		if( (data_s[i] == ' ') || (data_s[i] == '\n') || (data_s[i] == '\r') ){			
			if(first){
				st = i;
				first = false;
			}
			if( i != (data_s.length() - 1) ){
				continue;
			}		
		}
		if(!first){
			end = i;
			if((end - st) > 1){
				std::cout<<"st = "<<st<<" end = "<<end<<'\n';
				data_s.erase(data_s.begin() + st, data_s.begin() + end);
			}
			first = true;	
		}
	}
}


void session::stop()
  {
    boost::system::error_code ignored_ec;
    socket_.close(ignored_ec);
    deadline_.cancel();
    std::cout<<"socket delete\n";
  }



void session::log_in()//maybe useless
  {
	deadline_.expires_from_now(boost::posix_time::seconds(timeout));////////////////////////
	deadline_.async_wait(boost::bind(&session::check_deadline, this));

	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_),//, max_length
		[this, self](boost::system::error_code ec, std::size_t)
		{
		  deadline_.cancel();
		  if (!ec)
		  {
			//editable part begin
			std::string buf_s(data_);
			if(log_in_action(buf_s)){
				do_write(buf_s.c_str(), buf_s.length());
			}
			else{
				std::cout<<"exit\n";
			}
			//editable part end
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
		//editable part begin
		data_s.clear();
		do_read();

		//editable part end
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