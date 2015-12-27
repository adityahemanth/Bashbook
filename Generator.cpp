#include "Generator.h"
#include <fstream>
#include <iostream>
#include <string>

Generator::Generator(){

	std::string filename = "./db/namer.txt";
	std::ifstream database;
	database.open(filename);

	if(!database.is_open()){
	   std::cout << "Cannot open file, "
	   		<< "Check if it exists" << std::endl;
	}

	std::string line;
	while( std::getline(database, line) ) {
		names.push_back(line);
	}

	database.close();

}

std::string Generator::getUserName() {

	srand(clock());
	int first = rand() % names.size();
	std::string str = names[first] + std::to_string(rand() % 100);
	return str;
}

std::string Generator::getRealName(){

	srand(clock());
	int first = rand() % names.size();
	int last  = rand() % names.size();

	std::string str = names[first];
	str = str + " " + names[last];
	return str;
}