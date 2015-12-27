/* Author : Hemanth Aditya
 * Date   : 10 - 15 - 2015
 * File   : Wall.cpp
 * 
 * Contains the implementation of the methods defined in Wall.h
 *
 * Fuction: Maintains a list of WallPosts and lets us interact with
 * it. 
 */ 

#include "Wall.h"
#include "WallPost.h"

#include <fstream>
#include <stdlib.h>
#include <iostream>

const std::string DELIMITER = "<d>";

// constructor
Wall::Wall(std::string username){
	this -> username = username;
	postsize = 0;
}

// NULL contructor
Wall::Wall(){
	postsize = 0;
	username = "";
}


Wall::~Wall(){}

// takes WallPost object as parameter and adds it to the list

void Wall::addPost(WallPost & post){

	postsize++;
	std::map<long, WallPost>::iterator itr = posts.begin();

	while (posts.find(post.getIndex()) != posts.end()){
		post.setIndex(post.getIndex() + 1);
	}
	
	posts.insert(itr, std::pair<long,WallPost>(post.getIndex(), post));
}

void Wall::addReply(WallPost &post){
	
	
	posts[post.getParent()].incrementReplies();

	while (posts.find(post.getIndex()) != posts.end()){
		post.setIndex(post.getIndex() + 1);
	}

	std::map<long, WallPost>::iterator itr = posts.begin();
	posts.insert(itr, std::pair<long,WallPost>(post.getIndex(), post));

}


// removes post
void Wall::removePost(long index){

		std::map<long, WallPost>::iterator itr = posts.find(index);
		std::map<long, WallPost>::iterator itr2;
		

		if((itr -> second).getParent() == 0) {
			for(itr2 = posts.begin(); itr2 != posts.end(); /* no increment */){
				std::map<long, WallPost>::iterator itr3 = itr2 ++;
				if((itr3 -> second).getParent() == index){
					posts.erase(itr3);
				}
			}
		}

		else {
			for(itr2 = posts.begin(); itr2 != posts.end(); /* no increment */){

				std::map<long, WallPost>::iterator itr3 = itr2 ++;
				if((itr3 -> second).getIndex() == (itr -> second).getParent()){
					(itr3 -> second).decrementReplies();
				}
			}
		}

		posts.erase(itr);
}


 void Wall::deletePostfromWall(int pos, std::string user) {

 	int count = 0;
 	std::map<long,WallPost>::iterator itr = posts.begin();
 	for( ; itr != posts.end(); itr++){

 		if((itr -> second).getUser() == user)
 			count++;

 		if(count == pos){
 			removePost((itr -> second).getIndex());
 		}

 	}
 }

 void Wall::deletePost(int pos) {

	int count = 0;
	std::map<long, WallPost>::iterator itr ;
	for(itr = posts.begin(); itr != posts.end(); itr++){

		if((itr -> second).getParent() == 0)
			count++;

		if(count == pos){
			removePost((itr -> second).getIndex());
			return;
		}
	}		
}

void Wall::deleteReply(int pos, long parent) {

	int count = 0;
	std::map<long, WallPost>::iterator itr ;
	for(itr = posts.begin(); itr != posts.end(); itr++){
		if( (itr -> second).getParent() == parent)
			count++;

		if(count == pos){
			removePost((itr -> second).getIndex());
			return;
		}
	}
}

void Wall::setUsername(std::string user){
	username = user;
}

// displays the entire wall in a properly formatted way
void Wall::displayWall() {

	if( posts.size() == 0) 
		std::cout << username << " did not post anything yet!\n";

	else {

		std::map<long, WallPost>::iterator itr;
		int count = 1;
		for(itr = posts.begin(); itr != posts.end(); itr++){

			if((itr -> second).getParent() == 0) { 
				std::cout << "Post #: " <<  count << std::endl;
				std::cout << (itr -> second).getWallPost();
				std::cout << "\n\n";
				count ++;
			}

		}
	}
}

// displays the the replies to the current post.
void Wall::displayPost(long index) {

	std::map<long, WallPost>::iterator itr = posts.find(index);
	std::cout << (itr -> second).getWallPost() << "\n" << std::endl;
	
	int count = 1;
	for(itr = posts.begin(); itr != posts.end(); itr++) {
		if((itr -> second).getParent() == index) {
			std::cout << "     Reply #: " << count << std::endl;
			std::cout << (itr -> second).getReply() << std::endl;
			std::cout << "\n\n";
			count++;

		}
	}

}


// sets up the list of posts of a specific user by
// reading from a file. 
void Wall::createPosts(){

	if(username != "") {
		std::string filename = "./db/" + username + ".txt";

		std::ifstream database;
		database.open(filename);

		if(!database.is_open()){
		   std::cout << "Cannot open file, "
		   		<< "Check if it exists" << std::endl;
		}

		posts.clear();

		long parent;
		std::string line;
		while( std::getline(database, line) ) {
				parent = stol(line.substr(0,1));
				WallPost post(line);

				if(parent == 0)
			    	addPost(post);

				else
					addReply(post);
		}

		database.close();
	}

	else std::cout << "Set User to the Wall\n";
}


// saves all the posts by a user in a file
void Wall::savePosts() {

	if(username != "") {
		std::string filename = "./db/" + username + ".txt";

		std::ofstream database;
		database.open(filename, std::fstream::out);

		if(!database.is_open()){
			std::cout << "Cannot open file.\n";
		}

		else {

			std::map<long, WallPost>::iterator itr;
			for(itr = posts.begin(); itr != posts.end(); itr++){
				database << (itr -> second).getPostForStore() << std::endl;
			}

			database.close();
		}
	}

	else
		std::cout << "No username set.\n";

}

WallPost & Wall::getPost(long index){
	std::map<long, WallPost>::iterator itr = posts.find(index);
	return itr -> second;

}


void Wall::setCurrPostID(long id) {
	currPostID = id;
}

int Wall::size(){
	return postsize;
}

std::string Wall::getUsername(){
	return username;
}

std::map<long, WallPost>::iterator Wall::begin() {
	return posts.begin();
}

std::map<long, WallPost>::iterator Wall::end() {
	return posts.end();
}