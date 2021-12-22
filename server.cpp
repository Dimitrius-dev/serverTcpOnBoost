#include "server.h"

server::server(boost::asio::io_service& io_service, short port)
	: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), socket_(io_service), io_service_(io_service)
  {
	do_accept();
  }

void server::do_accept()
{
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {

		std::cout<<"connected\n";
            std::make_shared<session>(std::move(socket_), io_service_, context_)->start();
          }

          do_accept();
        });
}


