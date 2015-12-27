/* Author : Hemanth Aditya
 * Date   : 10 - 6 - 2015
 * File   : WallPost.cpp 
 * It is the template class of WallPost.cpp
 * Has all the method definitions and class members.
 * Storage Format: parent <d> index <d> username <d> post <d> post date <d> post time 
 */

#include "Wallpost.h"
#include <string>
#include <fstream>
#include <iostream>

 const std::string DELIMITER = "<d>";

 WallPost::WallPost(){

 	parent = 0;
 	numberofReplies = 0;
 	post = "";
 	postTime = "";
 	postDate = "";
 	userName = "";
 }

 WallPost::WallPost(std::string pst, std::string dte, std::string username) 
 {
 	std::swap(post,pst);
 	std::swap(userName,username);
 	numberofReplies = 0;
 	index = 0;
 	parent = 0;

 	// Date format (day-month-year<d>hours:mins)
 	std::string str = dte.substr(0,dte.find(DELIMITER));
 	std::swap(postDate,str);

 	dte.erase( 0, dte.find(DELIMITER) + DELIMITER.length() );
 	std::swap(postTime,dte);

 }

 WallPost::WallPost(std::string &line){

 	size_t pos = 0;
	std::string token;
	int tcount = 0;
	numberofReplies = 0;

	while ((pos = line.find(DELIMITER)) != std::string::npos) {

	    token = line.substr(0, pos);
	    switch(tcount){
	    	case 0: parent = stol(token); break;
	    	case 1: index = stol(token); break;
	    	case 2: userName = token; break;
	    	case 3: post = token; break;
	    	case 4: postDate = token; break;
	    }

	    line.erase(0, pos + DELIMITER.length());
	    tcount ++;
	}
	postTime = line;
 }


 WallPost::WallPost(const WallPost& rhs){

 	parent = rhs.parent;
 	index = rhs.index;
 	numberofReplies = rhs.numberofReplies;
 	post = rhs.post;
 	postDate = rhs.postDate;
 	postTime = rhs.postTime;
 	userName = rhs.userName;
 }

 WallPost::~WallPost(){}

 std::string WallPost::getWallPost() const {

 	std::string str = "Username: " + userName + "\nPost: " + post 
 					+ "\nDate: " + postDate
 					+ "\nTime: " + postTime
 					+ "\nReplies: " + std::to_string(numberofReplies);

 	return str;
 }

 std::string WallPost::getReply() const {

 	std::string str = "     Username: " + userName + "\n     Post: " + post 
 					+ "\n     Date: " + postDate
 					+ "\n     Time: " + postTime;

 	return str;
 }

 std::string WallPost::getPostForStore() const {
 	std::string str = std::to_string(parent) + DELIMITER + 
 					  std::to_string(index) + DELIMITER +
 					  userName + DELIMITER + post +
 					  DELIMITER + postDate + DELIMITER +
 					  postTime;
 	return str;
 }

 void WallPost::incrementReplies() {
 	numberofReplies++;
 }

 void WallPost::decrementReplies() {
 	numberofReplies--;
 }

 void WallPost::setDate(std::string & input){
 		std::swap(input,postDate);
 }

 void WallPost::setPost(std::string & str){
 		std::swap(str,post);
 }

 void WallPost::setTime(std::string & input) {
 		std::swap(input,postTime);
 }

 void WallPost::setUserName(std::string & uName){
 		std::swap(uName,userName);
 }

 void WallPost::setIndex(long item) {
 	index = item;
 }

 void WallPost::setParent(long item) {
 	parent = item;
 }

 void WallPost::setNumberofReplies(int item) {
 	numberofReplies = item;
 }

 long WallPost::getIndex() const {
 	return index;
 }

 long WallPost::getParent() const {
 	return parent;
 }

 std::string WallPost::getPost() const {
 	return post;
 }

 std::string WallPost::getDate() const {
 	return postDate;
 }

 std::string WallPost::getTime() const {
 	return postTime;
 }

 std::string WallPost::getUser() const {
 	return userName;
 }


 int WallPost::getNumberofReplies() const {
 	return numberofReplies;
 }
