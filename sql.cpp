#include "sql.h"

sql::sql(){
			
}

std::string sql::get_password(std::string name){	
	try
	{
		std::string request;		
	
		std::string command = "SELECT password FROM users WHERE name = '" + name + "';";
		pqxx::connection connectionObject(config.c_str());
		pqxx::work worker(connectionObject);
		pqxx::result response = worker.exec(command.c_str());
		
		
	
		for (auto row : response) {
			request = row[0].as<std::string>();
		}

		connectionObject.disconnect();

		return request;

	}
	
	catch (const std::exception& e){
		std::cerr << e.what() << std::endl;
		return "";
    	}
}

/*
	void insert(std::string config, std::list<One> &one, std::string command){
		try
		{
			pqxx::connection connectionObject(config.c_str());
			pqxx::work worker(connectionObject);
			pqxx::result response = worker.exec(command.c_str());

			worker.commit();

			connectionObject.disconnect();
		}

	    	catch (const std::exception& e)
	    	{
	       		std::cerr << e.what() << std::endl;
	    	}
	}

	void update(std::string config, std::list<One> &one, std::string command){
		try
		{
			pqxx::connection connectionObject(config.c_str());
			pqxx::work worker(connectionObject);
			pqxx::result response = worker.exec(command.c_str());


		}

	    	catch (const std::exception& e)
	    	{
	       		std::cerr << e.what() << std::endl;
	    	}
	}
*/

