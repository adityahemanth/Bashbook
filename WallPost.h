/* Author : Hemanth Aditya
 * Date   : 10 - 6 - 2015
 * File   : WallPost.h 
 * It is the template class of WallPost.cpp
 * Has all the method definitions and class members.
 */

#ifndef WallPost_H
#define WallPost_H

#include <string>
#include <map>

// Class wallpost
 class WallPost{

 	public:
 		 WallPost();
 		 WallPost(std::string pst, std::string dte, std::string username);
 		 WallPost(std::string &line);
 		 WallPost(const WallPost & rhs);
 		~WallPost();

 		std::string getWallPost() const;
 		std::string getPostForStore() const;
 		std::string getReply() const;
 		void   incrementReplies();
 		void   decrementReplies();
 		void   setDate(std::string & input);
 		void   setPost(std::string & str);
 		void   setTime(std::string & time);
 		void   setUserName(std::string & uName);
 		void   setIndex(long item);
 		void   setParent(long item);
 		void   setNumberofReplies(int item);
 		int    getNumberofReplies() const;

 		// get methods
 		std::string getPost() const;
 		std::string getTime() const;
 		std::string getDate() const;
 		std::string getUser() const;
 		long 		getIndex() const;
 		long 		getParent() const;

 		// overriding comparator 
 		bool operator == (const WallPost& wallpost){
    	return
	       post        == wallpost.getPost()
	       && postDate == wallpost.getDate()
	       && postTime == wallpost.getTime()
	       && userName == wallpost.getUser();
		}


	private:

		long index;
		long parent;
		int numberofReplies;
		std::string post;
		std::string postDate;
		std::string postTime;
		std::string userName;


 };

#endif