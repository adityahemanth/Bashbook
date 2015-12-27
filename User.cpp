/* Author : Hemanth Aditya
 * Date   : 12 - 5 - 2015
 * File   : User.cpp 
 * 
 * Contains implementation of the methods defined in User.h
 *
 * Fuction: Implementation of a User class that has a Wall
 * username, password, realname and city as its members. This
 * class is used to store and interface with the data (get & set)
 * of each user.
 */


#include "User.h"
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

const std::string DELIMITER = "<d>";

User::User(){
	userName = "";
	password = "";
	realName = "";
	city     = "";
	wall     = new Wall();

}

User::User(std::string uname, std::string pword)
: userName(uname), password(pword) {
	wall = new Wall();
	wall->setUsername(userName);
}

User::User( const User & rhs ) { 

	userName = rhs.userName;
	password = rhs.password;
	realName = rhs.realName;
	userID   = rhs.userID;
	city  	 = rhs.city;
	wall     = rhs.wall;
	requests = rhs.requests;
	friends  = rhs.friends;

}

User::User(std::string &line) {

	size_t pos = 0;
	std::string token;
	int tcount = 0;

	while ((pos = line.find(DELIMITER)) != std::string::npos) {
	    token = line.substr(0, pos);
	    switch(tcount){
	    	case 0: userName = token; break;
	    	case 1: password = token; break;
	    	case 2: realName = token; break;
	    }
	    line.erase(0, pos + DELIMITER.length());
	    tcount ++;
	}
	city = line;
	wall = new Wall();
	wall->setUsername(userName);
}

User::~User() {}

std::string User::getUserName() const{
	return userName;
}

std::string User::getUserID()const{
	return userID;
}

std::string User::getPassword() const {
	return password;
}

std::string User::getRealName() const {
	return realName;
}

std::string User::getCity() const {
	return city;
}

std::string User::getUserForStore() const {
	std::string str;
	str = userName + DELIMITER + password +
	      DELIMITER + realName + DELIMITER +
	      city;
	return str;
}

bool User::isFriend(std::string user){

	setupFriends();
	std::list<std::string>::iterator itr = friends.begin();
		for( ;itr != friends.end(); itr++) {
			if(*itr == user){
				return true;
			}
		}

		return false;
}


void User::showWall() {

	if(wall != NULL)
		wall -> displayWall();
}

void User::showPost(int index) {

	if(wall != NULL)
		wall -> displayPost(index);
}

void User::savePosts(){
	
	if(wall != NULL)
		wall -> savePosts();
}

void User::setupPosts(){

	if(wall != NULL)
		wall -> createPosts();
}

void User::deletePostfromWall(int pos, std::string user) {
	Wall wallObj(user);
	wallObj.createPosts();
	wallObj.deletePostfromWall(pos,userName);
	wallObj.savePosts();
}

void User::posttoWall(std::string post, std::string user) {

	Wall wallObj(user);
	wallObj.createPosts();

	time_t t = time(0);
	struct tm* now = localtime(&t);

	std::string strIndex = std::to_string( (now -> tm_year) % 10)+
						   std::to_string( now -> tm_mon + 10)  + 
						   std::to_string( now -> tm_mday + 10) + 
						   std::to_string( now -> tm_hour +10)  + 
						   std::to_string( now -> tm_min + 10); 

	long index = stol(strIndex); 
	std::string postDate = std::to_string( now -> tm_mon + 1) + "-" + 
						   std::to_string( now -> tm_mday + 1) + "-" + 
						   std::to_string( now -> tm_year + 1900) + 
						   DELIMITER + 
						   std::to_string( now -> tm_hour) + ":" + 
						   std::to_string( now -> tm_min); 

	WallPost wPost(post, postDate, userName);
	wPost.setIndex(index);
	wallObj.addPost(wPost);
	wallObj.savePosts();
}

void User::replytoWall(std::string post, std::string user, int pos) {

	int count = 1;
	int parent;
	Wall wallObj(user);
	wallObj.createPosts();

	wallObj.displayWall();

	std::cout << "Stage 0" << std::endl;
	std::map<long, WallPost>::iterator itr = wallObj.begin();

	for( ; itr != wallObj.end() ; itr++){
		if(count == pos){
			std::cout << "AT cout " << std::endl;
			parent = (itr -> second).getIndex();
			break;
		}

		count++;
	}

	std::cout << "Stage 1" << std::endl;

	time_t t = time(0);
	struct tm* now = localtime(&t);

	std::string strIndex = std::to_string( (now -> tm_year) % 10)+
						   std::to_string( now -> tm_mon + 10)  + 
						   std::to_string( now -> tm_mday + 10) + 
						   std::to_string( now -> tm_hour +10)  + 
						   std::to_string( now -> tm_min + 10); 

	long index = stol(strIndex); 
	std::string postDate = std::to_string( now -> tm_mon + 1) + "-" + 
						   std::to_string( now -> tm_mday + 1) + "-" + 
						   std::to_string( now -> tm_year + 1900) + 
						   DELIMITER + 
						   std::to_string( now -> tm_hour) + ":" + 
						   std::to_string( now -> tm_min); 

	WallPost wPost(post, postDate, userName);
	wPost.setIndex(index);
	wPost.setParent(parent);
	wallObj.addReply(wPost);
	wallObj.savePosts();
}



void User::post(std::string post) {
	if (wall->getUsername() == "")
		wall->setUsername(userName);

	time_t t = time(0);
	struct tm* now = localtime(&t);

	std::string strIndex = std::to_string( (now -> tm_year) % 10)+
						   std::to_string( now -> tm_mon + 10)  + 
						   std::to_string( now -> tm_mday + 10) + 
						   std::to_string( now -> tm_hour +10)  + 
						   std::to_string( now -> tm_min + 10); 

	long index = stol(strIndex); 
	std::string postDate = std::to_string( now -> tm_mon + 1) + "-" + 
						   std::to_string( now -> tm_mday + 1) + "-" + 
						   std::to_string( now -> tm_year + 1900) + 
						   DELIMITER + 
						   std::to_string( now -> tm_hour) + ":" + 
						   std::to_string( now -> tm_min); 

	WallPost *wPost = new WallPost(post, postDate, userName);
	wPost -> setIndex(index);
	wall -> addPost(*wPost);
}

void User::postReply(std::string username, std::string post, long parent){
	std::string filename = "./db/" + username + ".txt";
	std::ofstream database;
	database.open(filename, std::fstream::app);

	if(!database.is_open()){
		std::cout << "Cannot open file!" << std::endl;
	}

	else {

		time_t t = time(0);
		struct tm* now = localtime(&t);

		std::string strIndex = std::to_string( (now -> tm_year) % 10)+
						   std::to_string( now -> tm_mon + 10)  + 
						   std::to_string( now -> tm_mday + 10) + 
						   std::to_string( now -> tm_hour +10)  + 
						   std::to_string( now -> tm_min + 10); 

		long index = stol(strIndex); 

		std::string postDate = std::to_string( now -> tm_mon + 1) + "-" + 
							   std::to_string( now -> tm_mday + 1) + "-" + 
							   std::to_string( now -> tm_year + 1900) + 
							   DELIMITER + 
							   std::to_string( now -> tm_hour) + ":" + 
							   std::to_string( now -> tm_min); 

		WallPost wPost(post, postDate, username);
		wPost.setIndex(index);
		wPost.setParent(parent);
		database << wPost.getPostForStore() << std::endl;
		database.close();
	}
}

void User::setUserName(std::string username){
	userName = username;
}

void User::setPassword(std::string pword){
	this -> password = pword;
}

void User::setRealName(std::string realName){
	this -> realName = realName;
}

void User::setCity(std::string city){
	this -> city = city;
}


void User::setRequest(std::string name){

	if(name != "") {

		requests.clear();
		setupRequests();

		std::list<std::string>::iterator itr = requests.begin();
		for( ; itr != requests.end() ; itr++)
			if(*itr == name)
				return;

		requests.push_back(name);
		writeRequests();
	}
}

void User::ListRequests(){
	std::list<std::string>::iterator itr = requests.begin();
	int index = 1;
	for( ; itr != requests.end(); itr++){
		std::cout << index << ") ";
		std::cout << *itr << std::endl;
		index++;
	}
}

void User::ListFriends(){

	friends.clear();
	setupFriends();
	std::list<std::string>::iterator itr = friends.begin();
	int index = 1;
	for( ;itr != friends.end(); itr++){
		std::cout << index << ") ";
		std::cout << *itr << std::endl;
		index++;
	}
}

void User::acceptRequest(std::string name){

	if(name != "") {

		requests.clear();
		setupRequests();

		friends.clear();
		setupFriends();

		std::list<std::string>::iterator itr = requests.begin();
		for( ; itr != requests.end(); itr++ ){
			if(*itr == name){
				requests.erase(itr);
				friends.push_back(name);
				writeFriends();
				writeRequests();
				break;
			}
		}

	}
}

void User::deleteFriend(std::string name){
	if(name != "") {
		std::list<std::string>::iterator itr = friends.begin();
		for( ; itr != friends.end() ; itr++){
			if(*itr == name){
				friends.erase(itr);
				writeFriends();
				break;
			}
		}

	}
}

void User::addFriend(std::string name){
	if(name != "") {

		friends.clear();
		setupFriends();
		
		std::list<std::string>::iterator itr = friends.begin();
		for( ; itr != friends.end() ; itr++)
			if(*itr == name)
				return;

		friends.push_back(name);
		writeFriends();
	}
}



void User::setupRequests(){

	std::string filename = "./db/" + userName + "Requests.txt";
	std::ifstream database;
	database.open(filename, std::fstream::in);

	if(!database.is_open()){
		std::cout << "Cannot open File!" << std::endl;
		return;
	}

	std::string line;
	while( std::getline(database, line) ) {
		requests.push_back(line);
	}
	database.close();
}

void User::setupFriends(){

	std::string filename = "./db/" + userName + "Friends.txt";
	std::ifstream database;
	database.open(filename, std::fstream::in);
	
	if(!database.is_open()){
		return;
	}

	std::string line;
	while( std::getline(database, line) ) {
		friends.push_back(line);
	}
	database.close();
}

void User::writeFriends() {

	std::string filename = "./db/" + userName +"Friends.txt";
	std::ofstream database;
	database.open(filename, std::fstream::out);

	friends.sort();
	friends.unique();

	if(!database.is_open()){
		std::cout << "Cannot open file!" << std::endl;
	}
	
	else {
		std::list<std::string>::iterator itr = friends.begin();
		for( ; itr != friends.end() ; itr++){
			database << *itr << std::endl;
 		}
 		database.close();
	}
}

void User::writeRequests(){

	std::string filename = "./db/" + userName +"Requests.txt";
	std::ofstream database;
	database.open(filename, std::fstream::out);

	requests.sort();
	requests.unique();

	if(!database.is_open()){
		std::cout << "Cannot open file!" << std::endl;
	}
	
	else {

		std::list<std::string>::iterator itr = requests.begin();
		for( ; itr != requests.end() ; itr++){
			database << *itr << std::endl;
 		}
 		database.close();
	}
}

void User::deletePost(int pos) {

	wall -> deletePost(pos);	
}

void User::deleteReply(int pos, long parent) {

	wall -> deleteReply(pos,parent);
}


void User::rejectRequest(std::string name){
	if(name != ""){
		std::list<std::string>::iterator itr = requests.begin();
		for( ; itr != requests.end() ; itr++){
			if(*itr == name){
				requests.erase(itr);
				writeRequests();
				return;
			}

		}
	}

}

int User::friendSize(){
	return friends.size();
}

int User::requestSize(){
	return requests.size();
}

int User::getPostNumber() {
	return wall -> size();
}

std::list<std::string>::iterator User::requestBegin() {
	return requests.begin();
}

std::list<std::string>::iterator User::requestEnd() {
	return requests.end();
}

std::list<std::string>::iterator User::friendBegin() {
	return friends.begin();
}

std::list<std::string>::iterator User::friendEnd() {
	return friends.end();
}
