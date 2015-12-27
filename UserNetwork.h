/* Author : Hemanth Aditya
 * Date   : 13 - 5 - 2015
 * File   : UserNetwork.h 
 * 
 * Has all the method definitions and class members along with
 * their definition.
 *
 * Fuction: Interface of a UserNetwork class that maintains and 
 * allows us to interface with a list of users.
 */

#ifndef UserNetwork_H
#define UserNetwork_H
#include "User.h"

#include <map>
#include <list>

class UserNetwork{

public:

			 UserNetwork();
			~UserNetwork();
	bool 	 addUser(User& user);
	void     deleteUser(std::string username);
	void     setup();
	void     save();
	void     printWalls();
	void     unfriend(std::string user1, std::string user2);
	void     sendRequest(std::string sender, std::string receiver);
User*    findUser(std::string username);
std::string  separation(std::string user1, std::string user2);
std::string  distance3(std::string user1);
std::list<User> search(std::string key);
std::map<std::string, User>::iterator begin();
std::map<std::string, User>::iterator end();
	
private:
	std::map<std::string,User> userList;                    // LinkedList of users
	void toLower(std::string & input);
	std::string cachedUser;
	
};

#endif