/* Author : Hemanth Aditya
 * Date   : 14 - 5 - 2015
 * File   : Interface.cpp 
 * 
 * Has all the implementations of the  method definitions
 * and class members of Interface.h 
 *
 * Fuction: It is a simple text based interface for the user to
 * interact with the program.
 *
 * Used self-documenting code. All the methods and variables have
 * semantic names defining their function.
 */

#include "Interface.h"
#include "UserNetwork.h"
#include "Wall.h"
#include "User.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

// constructor
Interface::Interface() {
	network.setup();
	username = "";
}

// greeting screen
void Interface::greeting() {
	std::cout << "\n\n**************** WELCOME ****************\n\n" << endl;
	nextScreen = Screen::WELCOME;
}

// Welcome screen. It 
void Interface::welcome() {

	string choice;
	std::locale loc;
	std::cout << "Choose from the following:\n";
	std::cout << "'1' - Login\n";
	std::cout << "'2' - Signup\n";
	std::cout << "'3' - QUIT\n";
	getline(cin,choice,'\n');
	std::cout << "\n\n\n";

	if(isdigit(choice[0],loc) && choice.length() == 1){
		switch (stoi(choice)) {
			case 1 : nextScreen = Screen::LOGIN_USERNAME; break;
			case 2 : nextScreen = Screen::SIGNUP_USERNAME; break;
			case 3 : nextScreen = Screen::EXIT; break;
			default: std::cout << "Not a valid input!\n";
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}
}


void Interface::login_username() {
	string temp;
	std::cout << "Enter Username: ";
	getline(cin,temp,'\n'); 

	if(temp == "1") {
		nextScreen = Screen::SIGNUP_USERNAME;
	}

	else if (temp == "2"){
		nextScreen = Screen::EXIT;
	}

	else {
		User *user = network.findUser(temp);

		if(user -> getUserName() == "") {
			std::cout << "No such user!\n\n";
			std::cout << "'1' - Signup\n";
			std::cout << "'2' - QUIT\n";
		}

		else { 
			currentUser = *user;
			nextScreen = Screen::LOGIN_PASSWORD;
		}

	}

}

void Interface::login_password() {
	string temp;

	std::cout << "Enter password: ";
	getline(cin,temp,'\n'); 

	if(temp == "1") nextScreen = Screen::EXIT;
	else if(temp == currentUser.getPassword()){

		std::cout << "Login successful!\n\n";
		currentUser.setupPosts();
		nextScreen = Screen::USER;

	}

	else{

		std::cout << "Wrong Username or Password!\n";
		std::cout << "1 - QUIT\n";
	}
}

void Interface::signup_username() {
	string temp;

	std::cout << "Pick a username: ";
	getline(cin,temp,'\n');

	if(temp == "" ||  temp.length() < 4 ){
		std::cout << "Don't you have a name longer than that. Why not enter it.\n";
	}

	else {
		User *user = network.findUser(temp);

		if(user -> getUserName() != "") {
			std::cout << "Sorry, username is taken!\n";
		}
	    else {
	    	username = temp;
	    	nextScreen = Screen::SIGNUP_PASSWORD;
	    }
	}
}

void Interface::signup_password() {
	string temp1;
	string temp2;

	std::cout << "Pick a password: ";
	getline(cin,temp1,'\n');
	
	if(temp1 == "1") nextScreen = Screen::EXIT;
	else if(temp1 == "" && temp1.length() < 4) {
		std::cout << "Think of something, you need a password\n";
	}

	else {
		std::cout << "Retype the password: ";
		getline(cin,temp2,'\n');

		if(temp1 != temp2){
			std::cout << "Passwords do not match. Try again!\n\n";
		}
		else{
			User user(username,temp1);
			network.addUser(user);
			currentUser = *(network.findUser(username));
			nextScreen = Screen::SIGNUP_DETAILS;
		}
	}
}

void Interface::signup_details() {
	string temp;
	std::cout << "Almost done!\n";
	std::cout << "Enter full name: ";
	getline(cin,temp,'\n');
	if(temp == ""){
		std::cout << "Enter your name, Pretty Please!\n";
	}

	else {
		currentUser.setRealName(temp);
		std::cout << "Where do you live? (City): ";
		getline(cin,temp,'\n');
		currentUser.setCity(temp);
		network.save();
		nextScreen = Screen::USER;
	}
}

void Interface::user() {
	string choice;
	std::locale loc;
	string realname =  currentUser.getRealName();
	std::cout << "\n**************** HOME ******************\n";
	std::cout << "           " << realname << "\n\n";

	std::cout << "Choose from the following: \n";
	std::cout << "'1' - See your Wall\n";
	std::cout << "'2' - Friends List\n";
	std::cout << "'3' - Posts\n";
	std::cout << "'4' - Search\n";
	std::cout << "'5' - Settings\n";
	std::cout << "'6' - View Pending Requests\n";
	std::cout << "'7' - Logout\n";
	std::cout << "'8' - QUIT\n";
	getline(cin,choice,'\n'); 

	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: 
			std::cout << "\n************** WALL **************\n\n";
			currentUser.showWall(); break;
			case 2: nextScreen = Screen::VIEW_FRIENDS; break;
			case 3: nextScreen = Screen::POST_PAGE; break;
			case 4: nextScreen = Screen::SEARCH_PAGE;break;
			case 5: nextScreen = Screen::SETTINGS;break;
			case 6: nextScreen = Screen::VIEW_REQUESTS; break;
			case 7: 
				currentUser.savePosts();
				username = "";
				nextScreen = Screen::WELCOME;
				break;
			case 8: 
				currentUser.savePosts();
				nextScreen = EXIT; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}
}

void Interface::view_requests(){

	currentUser.setupRequests();
	cout << "***************** REQUESTS ******************\n";

	if(currentUser.requestSize() > 0) {

		string choice;
		std::locale loc;
		currentUser.ListRequests();
		cout << "Choose from the following: " << endl;
		cout << "'1'- Accept a Request" << endl;
		cout << "'2'- Delete a Request" << endl;
		getline(cin,choice,'\n'); 

		if(isdigit(choice[0],loc) && choice.length() == 1) {

			switch(stoi(choice)) {
				case 1: nextScreen = Screen::ACCEPT_REQUEST; break;
				case 2: nextScreen = Screen::DELETE_REQUEST; break;
				default :
					std::cout << "Invalid Input!\n";
					break;
			}
		}

		else {
			std::cout << "Invalid Input\n";
		}
	}

	else {
		cout << "You have no pending requests!\n" << endl;
		nextScreen = Screen::USER; 
	}
}

void Interface::accept_request(){
	cout << "Select Request # to accept" << endl;
	string choice;
	std::locale loc;
	getline(cin,choice,'\n');	

	if(isdigit(choice[0],loc) && choice.length() < 3) {
		int i = stoi(choice);
		
		if(i > 0 && i <= currentUser.requestSize()){
			std::list<string>::iterator itr = currentUser.requestBegin();
			int count = 1;
			for( ; itr != currentUser.requestEnd(); itr++){
				if(count == i){

					string myRequest = *itr;
					string Me = currentUser.getUserName();
					cout << "User 1: " << Me << endl;
					currentUser.acceptRequest(myRequest);
					cout << "current user clear" << endl;

					User* user2 = network.findUser(myRequest);
					user2 -> addFriend(Me);

					cout << "You are now friends with " << myRequest << endl;
					nextScreen = Screen::USER;
					break;
				}

				count ++;
			}
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}
}

void Interface::delete_request(){
	cout << "Select request # to delete" << endl;
	string choice;
	std::locale loc;
	getline(cin,choice,'\n');	

	if(isdigit(choice[0],loc) && choice.length() < 3) {
		int i = stoi(choice);

		
		if(i > 0 && i <= currentUser.requestSize()){
			std::list<string>::iterator itr = currentUser.requestBegin();
			int count = 1;
			for( ; itr != currentUser.requestEnd() ; ){
				if(count == i){
					string name = *itr;
					currentUser.rejectRequest(name);
					nextScreen = Screen::USER;
					break;
				}

				count ++;
			}
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}

}

void Interface::post() {

	std::cout << "\n\n***************** POSTS ******************\n"; 
	string post;
	std::locale loc;
	std::cout << "What's on your mind: ";
	getline(cin,post,'\n');

	if(post == ""){
		std::cout << "You can't have nothing on your mind.\n";
	}
	else {
		currentUser.post(post);
		std::cout << "\n\n";
		nextScreen = Screen::POST_PAGE;
	}
}

void Interface::post_page(){

	std::cout << "\n" << std::endl;
	string choice;
	std::locale loc;
	std::cout << "Choose from the following: " << std::endl;
	std::cout << "'1'-Post" << std::endl;
	std::cout << "'2'-Delete Post" << std::endl;
	std::cout << "'3'-Back to profile" << std::endl;

	getline(cin,choice,'\n');

	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::POST;break;
			case 2: nextScreen = Screen::DELETE_POST;break;
			case 3: nextScreen = Screen::USER; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else
		 std::cout << "Invalid Input\n";
}

void Interface::delete_post(){

	int number;

	if(number > 0){

		string choice;
		std::locale loc;
		currentUser.showWall();
		std::cout << "Choose post # to delete: ";
		getline(cin,choice,'\n');

		if((choice.length() < 3 && isdigit(choice[0],loc))) {
			number = stoi(choice);
			std::cout << "Are you sure you want to delete the post (y/n): ";
			getline(cin,choice,'\n');

			if(choice == "y" || choice == "Y"){
				currentUser.deletePost(number);
				nextScreen = Screen::POST_PAGE;
			}

			else{
				nextScreen = Screen::POST_PAGE;
			}
		}

		else
			 std::cout << "Invalid Input\n";

	}

	else {
		cout << "You have no posts to delete!\n" << endl;
		nextScreen = Screen::POST_PAGE;
	}
}


void Interface::search_page() {

	string choice;
	std::locale loc;

	cout << "\nSelect from the following: \n";
	cout << "'1' - Search All users \n";
	cout << "'2' - Get connection between you and someone else\n";
	cout << "'3' - Get all friends of friends of friends (length 3)\n";
	cout << "'4' - Back to profile\n";
	getline(cin,choice,'\n');

	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::SEARCH;break;
			case 2: nextScreen = Screen::CONNECTION;break;
			case 3: nextScreen = Screen::FRIENDS_OF_FRIENDS; break;
			case 4: nextScreen = Screen::USER; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else
		 std::cout << "Invalid Input\n";
}


void Interface::friends_of_friends(){

	std::string str = network.distance3(currentUser.getUserName());

	if(str != "")
		cout << "\n" << str << "\n" << endl;

	else
		cout << "\nCould not find anyone\n";

	nextScreen = Screen::SEARCH_PAGE;

}

void Interface::connection() {

	string choice;
	cout << "\nEnter username: ";
	getline(cin,choice,'\n');

	if((network.findUser(choice)) -> getUserName() != ""){
		cout << "\n\n" << network.separation(currentUser.getUserName(), choice) << "\n" << endl;
		nextScreen = Screen::SEARCH_PAGE;
	}

	else
		cout << "Did not find anything, try again!";
}

void Interface::search(){

	string choice;
	cout << "\nEnter name or part of it: ";
	getline(cin,choice,'\n');
	results = network.search(choice);

	cout << "\nResults returned: " << results.size() << endl;
	std::list<User>::iterator itr = results.begin();
	int i = 1;
	for( ; itr != results.end() ; itr++){
		cout << i << ") " << (*itr).getRealName() << endl;
		i++;
	}

	if(results.size() > 0)
		nextScreen = Screen::SEND_REQUEST;

	else
		cout << "Did not find anything, try again!";
}

void Interface::send_request(){

	string choice;
	std::locale loc;
	cout << "\nChoose from the following: " << endl;
	cout << "'1'- Send friend request to one of them in the list" << endl;
	cout << "'2'- Didn't find who you are looking for? Search again." << endl;
	cout << "'3'- Back to profile" << endl;
	getline(cin,choice,'\n');


	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::CONFIRM_SENDREQUEST;break;
			case 2: nextScreen = Screen::SEARCH; break;
			case 3: nextScreen = Screen::USER;break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else
		 std::cout << "Invalid Input\n";
}


void Interface::confirm_sendrequest(){

	string choice;
	std::locale loc;
	cout << "Select the index of the user you wanna send a request to" << endl;
	cout << "'0' - Go to Profile" << endl;
	getline(cin,choice,'\n');
	if(isdigit(choice[0],loc) && choice.length() < 3) {
		int i = stoi(choice);

		if(i == 0) { 
			nextScreen = Screen::USER;
			return;
		}

		if(i > 0 && i <= results.size()) {

			int count = 1;
			std::list<User>::iterator itr = results.begin();
			for ( ; itr != results.end() ; itr++){
				if(count == i){
					string receiver = (*itr).getUserName();
					string sender = currentUser.getUserName();
					network.sendRequest(sender, receiver);
					cout << "You successfully sent a friend request to " << receiver << endl;
					nextScreen = Screen::USER;
					break;
				}

				count++;
			}
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}

}


void Interface::settings(){

	cout << "\n******************** SETTINGS ****************" << endl;
	string choice;
	std::locale loc;
	cout << "\nChoose from the following" << endl;
	cout << "'1'- Change personal info" << endl;
	cout << "'2'- Change Password" << endl;
	cout << "'3'- Delete Profile" << endl;

	getline(cin,choice,'\n');
	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::EDIT_INFO; break;
			case 2: nextScreen = Screen::CHANGE_PASSWORD; break;
			case 3: nextScreen = Screen::AUTHORIZE; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}

	}

	else {
		std::cout << "Invalid Input\n";
	}
}


void Interface::edit_info(){

	string temp;
	std::cout << "Edit Real Name\n";
	std::cout << "Enter full name: ";
	getline(cin,temp,'\n');
	if(temp == ""){
		std::cout << "Enter your name, Pretty Please!\n";
	}

	else {
		currentUser.setRealName(temp);
		std::cout << "Where do you live now? (New city): ";
		getline(cin,temp,'\n');
		currentUser.setCity(temp);
		network.save();
		nextScreen = Screen::USER;
	}

}


void Interface::authorize(){
	string temp;

	std::cout << "Enter password: ";
	getline(cin,temp,'\n'); 

	if(temp == "1") nextScreen = Screen::EXIT;
	else if(temp == currentUser.getPassword()){

		std::cout << "Login successful!\n\n";
		currentUser.setupPosts();
		nextScreen = Screen::DELETE_ACCOUNT;

	}
	else{
		std::cout << "Wrong Username or Password!\n";
		std::cout << "1 - QUIT\n";
	}
}

void Interface::delete_account(){

	cout << "Account deleted!" << endl;
	network.deleteUser(currentUser.getUserName());
	network.save();
	nextScreen = Screen::WELCOME;
}

void Interface::change_password(){

	string temp1;
	string temp2;

	std::cout << "Pick a password: ";
	getline(cin,temp1,'\n');
	
	if(temp1 == "1") nextScreen = Screen::EXIT;
	else if(temp1 == "" && temp1.length() < 4) {
		std::cout << "Think of something, you need a password\n";
	}

	else {
		std::cout << "Retype the password: ";
		getline(cin,temp2,'\n');

		if(temp1 != temp2){
			std::cout << "Passwords do not match. Try again!\n\n";
		}
		else{
			cout << "Password updated!" << endl;
			currentUser.setPassword(temp1);
			nextScreen = Screen::USER;
		}
	}
}

void Interface::view_friends(){

	cout << "\n************* Your Friends List! *************\n";
	currentUser.ListFriends();

	if(currentUser.friendSize() > 0)
		nextScreen = Screen::DELETE_FRIEND_HANDLER;

	else {
		cout << "You have no friends, go ahead a make some!" << endl;
		nextScreen = Screen::SEARCH;
	}
}

void Interface::delete_friend_handler(){

	string choice;
	std::locale loc;
	cout << "\nChoose from the following:" << endl;
	cout << "'1'- Go to friend's wall" << endl;
	cout << "'2'- Go back to profile" << endl;
	cout << "'3'- Delete a friend " << endl;

	getline(cin,choice,'\n');
	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::WALL; break;
			case 2: nextScreen = Screen::USER; break;
			case 3: nextScreen = Screen::DELETE_FRIEND; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}
}

void Interface::wall(){

	string choice;
	std::locale loc;
	cout << "Select the index of the friend whose wall you want to visit" << endl;
	cout << "'0' - Go to Profile" << endl;
	getline(cin,choice,'\n');


	if(isdigit(choice[0],loc) && choice.length() < 3) {
		int i = stoi(choice);

		if(i == 0) { 
			nextScreen = Screen::USER;
			return;
		}

		int count = 1;

		if(i > 0 && i <= currentUser.friendSize()){
			std::list<string>::iterator itr = currentUser.friendBegin();

			for ( ; itr != currentUser.friendEnd() ; itr++ ){

				if(count == i) {
					username = *itr;
					nextScreen = Screen::WALL_HANDLER;
					break;
				}

				count++;
			}
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}
}

void Interface::wall_handler() {

	Wall wallObj(username);
	wallObj.createPosts();
	cout << "\n\n*************  ";
	cout << network.findUser(username) -> getRealName() << "'s Wall";
	cout << "  **************\n\n";
	wallObj.displayWall();

	string choice;
	std::locale loc;
	cout << "'1' - View Post" << endl;
	cout << "'2' - Post something on " << username << "'s Wall" << endl;
	cout << "'3' - Delete your post from " << username << "s' Wall" << endl;
	cout << "'4' - Go to Profile" << endl;
	
	getline(cin,choice,'\n');
	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::VIEW_POST_HANDLER; break;
			case 2: nextScreen = Screen::POST_TO_WALL; break;
			case 3: nextScreen = Screen::DELETE_FROM_WALL; break;
			case 4: nextScreen = Screen::USER; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}

}

void Interface::delete_reply_from_wall(){

}

void Interface::view_post_handler() {

	string choice;
	std::locale loc;
	cout << "Select the index of the post: " << endl;
	cout << "'0' - Go to friend's Profile" << endl;
	getline(cin,choice,'\n');


	if(isdigit(choice[0],loc) && choice.length() < 3) {
		int i = stoi(choice);
		id = i;

		if(i == 0) { 
			nextScreen = Screen::WALL_HANDLER;
			return;
		}

		int count = 1;

			Wall wallObj(username);
			wallObj.createPosts();

		if(i > 0 && i <= wallObj.size()){

			int count = 1;
			std::map<long, WallPost>::iterator itr = wallObj.begin();
			for( ; itr != wallObj.end() ; itr++) {
				if(count == id) {
					postIndex = (itr -> second).getIndex();
					wallObj.displayPost(postIndex);
					nextScreen = Screen::VIEW_POST;
					break;
				}

				count++;
			}

		}
	}

	else {
		std::cout << "Invalid Input\n";
	}

}

void Interface::view_post() {

	string choice;
	std::locale loc;
	cout << "\nChoose from the following:" << endl;
	cout << "'1'- Post a reply" << endl;
	cout << "'2'- Delete your reply" << endl;
	cout << "'3'- Go back to friend's profile " << endl;

	getline(cin,choice,'\n');
	if(isdigit(choice[0],loc) && choice.length() == 1) {

		switch(stoi(choice)) {
			case 1: nextScreen = Screen::POST_REPLY_TO_WALL; break;
			case 2: nextScreen = Screen::DELETE_REPLY_FROM_WALL; break;
			case 3: nextScreen = Screen::WALL_HANDLER; break;
			default :
				std::cout << "Invalid Input!\n";
				break;
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}

}

void Interface::post_reply_to_wall() {

		std::string choice;
		Wall wallObj(username);
		wallObj.createPosts();
				
		cout << "What's on your mind?: ";
		getline(cin,choice,'\n');
		currentUser.replytoWall(choice, username, id);
		cout << "You successfully posted a reply" << endl;
		nextScreen = Screen::WALL_HANDLER;

}

void Interface::delete_from_wall(){

}

void Interface::post_to_wall(){

	std::string choice;
	std::cout << "What's on your mind? :";
	getline(cin,choice,'\n');
	currentUser.posttoWall(choice, username);
	std::cout << "You posted: " << choice 
			  << " on " << username << "'s Wall\n\n";

	nextScreen = Screen::WALL_HANDLER;
}


void Interface::delete_friend(){
	string choice;
	std::locale loc;
	cout << "Select the index of the friend you wanna delete!" << endl;
	cout << "'0' - Go to Profile" << endl;
	getline(cin,choice,'\n');
	if(isdigit(choice[0],loc) && choice.length() < 3) {
		int i = stoi(choice);

		if(i == 0) { 
			nextScreen = Screen::USER;
			return;
		}

		int count = 1;

		if(i > 0 && i <= currentUser.friendSize()){
			std::list<string>::iterator itr = currentUser.friendBegin();

			for ( ; itr != currentUser.friendEnd() ; itr++ ){

				if(count == i){
					string user1 = *itr;
					cout << "User 1: " << user1 << endl;
					string user2 = currentUser.getUserName();
					cout << "User 1: " << user2 << endl;

					network.unfriend(user1, user2);
					cout << "You successfully unfriended " << user1 << endl;
					nextScreen = Screen::USER;
					break;

				}

				count++;
			}
		}
	}

	else {
		std::cout << "Invalid Input\n";
	}
}

// main method. Takes care of switching screens according to the
// user input.
int main(){

	Interface interface;
	// runs until the user exits
	interface.nextScreen = Screen::GREETING;

	while (true) {
		switch(interface.nextScreen) {

			case GREETING: interface.greeting();
				break;

			case WELCOME: interface.welcome();
				break;

			case SIGNUP_USERNAME: interface.signup_username();
				break;

			case SIGNUP_PASSWORD: interface.signup_password();
				break;

			case SIGNUP_DETAILS: interface.signup_details();
				break;

			case USER:	interface.user();
				break;

			case POST:	interface.post();
				break;

			case LOGIN_USERNAME: interface.login_username();
				break;

			case LOGIN_PASSWORD: interface.login_password();
				break;

			case POST_PAGE: interface.post_page();
				break;

			case DELETE_POST: interface.delete_post();
				break;

			case SETTINGS: interface.settings();
				break;

			case SEARCH: interface.search();
				break;

			case SEARCH_PAGE: interface.search_page();
				break;

			case CONNECTION: interface.connection();
				break;

			case FRIENDS_OF_FRIENDS: interface.friends_of_friends();
				break;

			case SEND_REQUEST: interface.send_request();
				break;

			case VIEW_REQUESTS: interface.view_requests();
				break;

			case ACCEPT_REQUEST: interface.accept_request();
				break;

			case DELETE_REQUEST: interface.delete_request();
				break;

			case VIEW_FRIENDS: interface.view_friends();
				break;

			case DELETE_FRIEND_HANDLER: interface.delete_friend_handler();
				break;

			case DELETE_FRIEND: interface.delete_friend();
				break;

			case AUTHORIZE: interface.authorize();
				break;

			case CHANGE_PASSWORD: interface.change_password();
				break;

			case DELETE_ACCOUNT: interface.delete_account();
				break;

			case WALL: interface.wall();
				break;

			case WALL_HANDLER: interface.wall_handler();
				break;

			case POST_REPLY_TO_WALL: interface.post_reply_to_wall();
				break;

			case VIEW_POST: interface.view_post();
				break;

			case VIEW_POST_HANDLER: interface.view_post_handler();
				break;

			case DELETE_REPLY_FROM_WALL: interface.delete_reply_from_wall();
				break;

			case POST_TO_WALL: interface.post_to_wall();
				break;

			case DELETE_FROM_WALL: interface.delete_from_wall();
				break;

			case EDIT_INFO: interface.edit_info();
				break;

			case CONFIRM_SENDREQUEST: interface.confirm_sendrequest();
				break;

			case EXIT: return 0;
				break;
		}
	}
}