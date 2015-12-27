/* Author : Hemanth Aditya
 * Date   : 14 - 5 - 2015
 * File   : Wall.h
 * 
 * Has all the method definitions and class members of Wall class
 * along with their definition.
 *
 * Fuction: Maintains a list of Wallposts of a specific user.
 * Detailed description of each function in .cpp file
 */

#ifndef Wall_H
#define Wall_H

#include "WallPost.h"
#include <map>

class Wall{

 public:
 				Wall();
 				Wall(std::string username);
 			   ~Wall();
 	void	    addPost(WallPost &post);
 	void		addReply(WallPost &post);
 	void	    removePost(long Index);
 	void   		deletePostfromWall(int pos, std::string user);
 	void	    setUsername(std::string username);
 	void        displayWall();
 	void        displayPost(long index);
 	void        createPosts();
 	void        savePosts();
 	void 		deletePost(int pos);
	void 		deleteReply(int pos, long parent);
 	void        setCurrPostID(long id);
 	std::map<long, WallPost>::iterator begin();
 	std::map<long, WallPost>::iterator end();

 	int 		size();
 	WallPost &  getPost(long index);
    std::string getUsername();

 private:

 	long				   currPostID;
 	std::string      	   username;
 	std::map<long,WallPost> posts;			// list of posts
 	int postsize;
 };

#endif	