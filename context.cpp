#include"context.h"

context::context(){
	buf = "hello";
}	

std::string context::getBuf(){
	return buf;	
}