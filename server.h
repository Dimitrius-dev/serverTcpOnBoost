#ifndef SERVER_H
#define SERVER_H

#include "session.h"
//#include <list>
#include "context.h"

using boost::asio::ip::tcp;

class server
{
public:
  server(boost::asio::io_service& io_service, short port);

private:
  void do_accept();

  tcp::acceptor acceptor_;
  tcp::socket socket_;

  boost::asio::io_service& io_service_;

  context context_; 
};


#endif