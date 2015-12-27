/* Author : Hemanth Aditya
 * Date   : 14 - 5 - 2015
 * File   : Interface.h 
 * 
 * Has all the method definitions and class members along with
 * their definition.
 *
 * Fuction: Defines the stuct called Screens and all the members
 * and member functions. 
 */


#ifndef Interface_H
#define Interface_H

#include "UserNetwork.h"
#include "Wall.h"
#include "User.h"
#include <list>

enum Screen { 
	GREETING,
	WELCOME,
	SIGNUP_USERNAME,
	SIGNUP_PASSWORD,
	SIGNUP_DETAILS,
	USER,
	POST,
	VIEW_POST,
	VIEW_POST_HANDLER,
	POST_REPLY_TO_WALL,
	DELETE_REPLY_FROM_WALL,
	WALL,
	WALL_HANDLER,
	DELETE_FROM_WALL,
	POST_TO_WALL,
	LOGIN_USERNAME,
	LOGIN_PASSWORD,
	POST_PAGE,
	DELETE_POST,
	SETTINGS,
	DELETE_ACCOUNT,
	CHANGE_PASSWORD,
	EDIT_INFO,
	AUTHORIZE,
	SEARCH_PAGE,
	SEARCH,
	CONNECTION,
	FRIENDS_OF_FRIENDS,
	SEND_REQUEST,
	VIEW_REQUESTS,
	ACCEPT_REQUEST,
	DELETE_REQUEST,
	VIEW_FRIENDS,
	DELETE_FRIEND_HANDLER,
	DELETE_FRIEND,
	CONFIRM_SENDREQUEST,
	EXIT
};

 class Interface{
 
 public:
 	Interface();
 	void greeting();
 	void welcome();
 	void signup_username();
 	void signup_password();
 	void signup_details();
 	void user();
 	void wall();
 	void wall_handler();
 	void post_to_wall();
 	void delete_from_wall();
 	void post();
 	void login_username();
 	void login_password();
 	void delete_account();
 	void post_page();
 	void post_reply_to_wall();
 	void view_post();
 	void view_post_handler();
 	void delete_reply_from_wall();
 	void delete_post();
 	void settings();
 	void friends_of_friends();
 	void search();
 	void search_page();
 	void connection();
 	void delete_friend();
 	void delete_friend_handler();
 	void send_request();
 	void confirm_sendrequest();
 	void view_requests();
 	void accept_request();
 	void delete_request();
 	void view_friends();
 	void authorize();
 	void edit_info();
 	void change_password();
 	Screen nextScreen;

 private:
 	UserNetwork network;
 	User currentUser;
 	long  postIndex;
 	int   id;
 	std::string username;
 	std::list<User> results;
  };

#endif