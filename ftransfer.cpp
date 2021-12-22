
#include "ftransfer.h"

ftransfer::ftransfer(){
}

void ftransfer::open_file(std::string& buf_s, std::string path){
	buf_s.clear();

	//std::string path1 = "file.jpg";

	std::ifstream fin;
	fin.open(path, std::ios::binary );
	if(!fin.is_open()){
		std::cout<<"error1\n";	
	}
	else{
		char ch;
		while(fin.get(ch)){
				//std::cout<<(unsigned int)ch;
				buf_s.push_back(ch);
				buf_s.push_back(' ');
		}
	}

	fin.close();
}

void ftransfer::create_file(std::string& buf_s, std::string path, std::string type){
	srand( time(0) );

	
	std::ofstream fout;
	//std::string path2 = "output/fileOut.jpg";
	
	std::string path_final = path + std::to_string(rand()) + type; 

	fout.open(path_final, std::ios::binary );
	if(!fout.is_open()){
		std::cout<<"error2\n";	
	}
	else{
		std::string number = "";
		for(int i = 0;i<buf_s.size();i++){
			if(buf_s[i] == ' '){
				fout<<(char)(std::atoi(number.c_str()));
				number.clear();
			}
			else{
				number.push_back(buf_s[i]);
			}
		}
	}

	fout.close();
}

/*
int main(){
	
	std::string buf_s = "";

	open_file(buf_s, "file.jpg");

	create_file(buf_s, "output/", ".jpg");

	return 0;
}
*/