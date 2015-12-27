/* Author : Hemanth Aditya
 * Date   : 12 - 5 - 2015
 * File   : User.h 
 * 
 * Has all the method definitions and class members along with
 * their definition.
 *
 */

#ifndef User_H
#define User_H

#include <string>
#include <list>
#include "Wall.h"

class User{

public:

	explicit User(std::string uname, std::string pword);
			 User(std::string &line);
			 User( const User & rhs );
			 User();
			~User();

		    int getPostNumber();
		    int friendSize();
		    int requestSize();
	std::string getUserName() const;
	std::string getUserID()   const;
	std::string getPassword() const;
	std::string getRealName() const;
	std::string getCity() 	 const;
	std::string getUserForStore() const;

	void posttoWall(std::string post, std::string user);
	void replytoWall(std::string post, std::string user, int pos);
	void deletePostfromWall(int pos, std::string user);
	void setupRequests();
	void setupFriends();
	void showWall();
	void showPost(int pos);
	void savePosts();
	void setupPosts();
	void ListRequests();
	void ListFriends();
	void postReply(std::string username, std::string post, long parent);
	void setUserName(std::string username);
	void setPassword(std::string password);
	void setRealName(std::string realName);
	void setCity(std::string city);
	void post(std::string post);
	void deletePost(int pos);
	void deleteReply(int pos, long parent);
	void setRequest(std::string username);
	void acceptRequest(std::string username);
	void rejectRequest(std::string username);
	void addFriend(std::string username);
	void deleteFriend(std::string name);
	void setDistance(int dist) {distance = dist;};
	void setParent(std::string prt) {parent = prt;};
	void setVisited(bool flag) { visited = flag;};
	bool isFriend(std::string username);
	bool getVisited() {return visited;};
	int  getDistance() {return distance;};
	std::string getParent() {return parent;};
	std::list<std::string>::iterator requestBegin();
	std::list<std::string>::iterator requestEnd();
	std::list<std::string>::iterator friendBegin();
	std::list<std::string>::iterator friendEnd();

	
private:

//	graph  parameters
	bool        visited;
	int         distance;
	std::string parent;
// 

	Wall        *wall;
	std::string userName;
	std::string password;
	std::string realName;
	std::string userID;
	std::string city;
	std::list<std::string> requests;
	std::list<std::string> friends;
	void writeFriends();
	void writeRequests();

	

};


#endif