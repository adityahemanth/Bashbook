/* Author : Hemanth Aditya
 * Date   : 13 - 5 - 2015
 * File   : Usernetwork.cpp 
 * 
 * Contains the impelentation of the member funtions defined by 
 * UserNetwork.h
 *
 * Fuction: Saves the list of users and lets us setup a network
 * (list) of users by reading from a file, and save all the user
 * data by writing to a file. Has other fuctions that let us find
 * users by name
 */

#include "UserNetwork.h"
#include "User.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string DATABASE  = "./db/Userdata.txt"; 
const string DELIMITER = "<d>";

UserNetwork::UserNetwork(){
	cachedUser = "";
}

UserNetwork::~UserNetwork(){
}

// takes user object as an object and 
// adds it to the list
bool UserNetwork::addUser(User& user){

	if(userList.find(user.getUserName()) == userList.end() ) {
		std::map<std::string, User>::iterator itr = userList.begin();
		userList.insert(itr, std::pair<std::string,User>(user.getUserName(),user));
		return true;
	}

	return false;
	
}

// searches the list by name and deletes the user
void UserNetwork::deleteUser(string username){

	if(userList.find(username) != userList.end()) {
		userList.erase(userList.find(username));
	}

	else {
		cout << "No user with " << username 
		<< " username" << endl;
	}
}

// returns a string of user separation data
std::string UserNetwork::separation(std::string source, std::string destination) {

		std::map<std::string, User>::iterator itr = userList.begin();
		for( ; itr != userList.end(); itr++){
			(itr -> second).setVisited(false);
			(itr -> second).setDistance(-1);
			(itr -> second).setParent("");
		}


		std::map<std::string, User>::iterator itr2;
		userList[source].setDistance(0);
		bool found = false;

		 for( int currDist = 0; currDist < userList.size(); currDist++ ){
		 	for(itr = userList.begin(); itr != userList.end(); itr++){
		 		if((itr->second).getVisited() == false && (itr -> second).getDistance() == currDist) {
		 			(itr -> second).setVisited(true);
	 
		 			for(itr2 = userList.begin(); itr2 != userList.end(); itr2++){
		 				 if((itr -> second).isFriend((itr2 -> second).getUserName())
		 				 	&& (itr2 -> second).getDistance() == -1 ){

		 				 	(itr2 -> second).setDistance(currDist + 1);
		 				 	(itr2 -> second).setParent((itr -> second).getUserName());
		 				 	if((itr2 -> second).getUserName() == destination){
	 				 			found = true;
	 				 			break;
	 				 		}

		 				 }

		 			}

		 		}

		 		if(found)
	 			break;
		 	}

		 	if(found)
	 			break;
		 }



	 std::string str;
	 std::string user;

	 if(userList[destination].getParent() != ""){
	 	str = destination;
	 	user = userList[destination].getParent();

	 	while(user != userList[source].getUserName()){
	 		str = user + " -> " + str;
	 		user = userList[user].getParent();
	 	}

	 	str = source + " -> " + str;
	 }

	 else{

	 	str = "No path from " + source + " to " + destination; 
	 	
	 }

	 return str;

}

std::string UserNetwork::distance3(std::string source){


std::map<std::string, User>::iterator itr = userList.begin();

	for( ; itr != userList.end(); itr++){
		(itr -> second).setVisited(false);
		(itr -> second).setDistance(-1);
		(itr -> second).setParent("");
	}

	std::map<std::string, User>::iterator itr2;
	userList[source].setDistance(0);
	bool found = false;

	 for( int currDist = 0; currDist < userList.size(); currDist++ ){
	 	for(itr = userList.begin(); itr != userList.end(); itr++){
	 		if((itr->second).getVisited() == false && (itr -> second).getDistance() == currDist) {
	 			(itr -> second).setVisited(true);
 
	 			for(itr2 = userList.begin(); itr2 != userList.end(); itr2++){
	 				 if((itr -> second).isFriend((itr2 -> second).getUserName())
	 				 	&& (itr2 -> second).getDistance() == -1 ){

	 				 	(itr2 -> second).setDistance(currDist + 1);
	 				 	(itr2 -> second).setParent((itr -> second).getUserName());
	 				 	if(currDist == 3){
	 				 		found = true;
	 				 		break;
	 				 	}

	 				 }

	 			}

	 		}

	 		if(found)
	 			break;
	 	}

	 	if(found)
	 			break;
	 }

	 cachedUser = source;

	std::string str = "";

	for (itr = userList.begin(); itr != userList.end(); itr++){
		if((itr -> second).getDistance() == 3){
			str = (itr -> second).getUserName() + "\n" + str;
		}
	}

	return str;

}

// reads from the file and sets the network up
void UserNetwork::setup(){

	std::ifstream database;
	database.open(DATABASE);

	if(!database.is_open()){
	   cout << "Cannot open file, "
	   		<< "Check if it exists" << endl;
	}

	string line;
	while( std::getline(database, line) ) {
		User *user = new User(line);
	    addUser(*user);

	}

}

// sends a friend request to the reciever from the sender.
void UserNetwork::sendRequest(string sender, string receiver){
	if(userList.find(receiver)!= userList.end()){

		User rcvr = userList.find(receiver) -> second;
		rcvr.setRequest(sender);
	}

	else
		cout << "No such user exists" << endl;
}

User* UserNetwork::findUser(std::string username) {
	std::map<std::string,User>::iterator itr = userList.find(username);

	if(itr != userList.end()){
		User *user = &( itr -> second);
		return user;
	}

	else {

		User *user = new User();
		return user;
	}
}


std::list<User>  UserNetwork::search(std::string key){

	toLower(key);

	std::list<User> *results = new std::list<User>;
	std::map<std::string, User>::iterator itr = userList.begin();
	std::string temp1;
	std::string temp2;

	for( ; itr != userList.end() ; itr++ ){

		temp1 = (itr -> second).getUserName();
		toLower(temp1);
		temp2 = (itr -> second).getRealName();
		toLower(temp2);

		if(temp1.find(key) != std::string::npos) {
			results -> push_back(itr -> second);
		} 

		else if (temp2.find(key) != std::string::npos){
			results -> push_back(itr -> second);
		}
	}

	return *results;
}


// void UserNetwork::deleteUser(std::string username){
// 	Node<User>* user = findUser(username);
// }


// saves all the user data by writing to a file
// File Format : username <d> password <d> realname <d> city
void UserNetwork::save(){

	std::ofstream database;
	database.open(DATABASE, std::fstream::out);

	if(database.is_open()){
		std::map<std::string,User>::iterator itr = userList.begin();
		while(itr != userList.end()){

			database << (itr -> second).getUserName() << DELIMITER 
					 << (itr -> second).getPassword() << DELIMITER
					 << (itr -> second).getRealName() << DELIMITER
					 << (itr -> second).getCity() << endl;
			itr++;
		}

		database.close();
	}

	else {
		cout << "Cannot open file\n";
	}
}

// void UserNetwork::print(){

// 	LinkedList<User>::iterator i = userList.begin();
// 	while(++i != userList.end()){
// 		cout << (*i).getRealName() << endl;
// 	}
// }

void UserNetwork::toLower(std::string & input){

	for (std::string::size_type i = 0; i < input.length(); ++i)
    	input[i] = tolower(input[i]);
    
}

void UserNetwork::printWalls(){
	std::map<std::string,User>::iterator itr =  userList.begin();
	for( ; itr != userList.end() ; itr++){
		(itr -> second).showWall();
	}
}

void UserNetwork::unfriend(std::string user1, std::string user2){
	User ptr1 = userList.find(user1) -> second;
	ptr1.deleteFriend(user2);

	User ptr2 = userList.find(user2) -> second;
	ptr2.deleteFriend(user1);
}

std::map<std::string, User>::iterator UserNetwork::begin(){
	return userList.begin();
}

std::map<std::string, User>::iterator UserNetwork::end() {
	return userList.end();
}


