serverTcpOnBoost

commands to compile(Linux):

1.g++ server.cpp -o server -pthread -lboost_system -std=c++17
-----------------
2.g++ *.cpp -o server -pthread -lboost_system -std=c++17
-----------------
3.g++ *.cpp -o server -pthread -lboost_system -lpqxx -lpq -std=c++17  with sql
-----------------
