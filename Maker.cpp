#include "User.h"
#include "UserNetwork.h"
#include "Generator.h"

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {

	srand(clock());
	Generator gen;
	UserNetwork network;
	network.setup();

	for(int i = 0; i < 500; i++ ) {

		string uname = gen.getUserName();
		User user(uname,"password");
		string real = gen.getRealName();
		user.setRealName(real);
		user.setCity("Goleta");
		network.addUser(user);
	}

	std::map<std::string, User>::iterator itr = network.begin();
	std::map<std::string, User>::iterator itr2;

	for( ; itr != network.end() ; itr++){
		int i = rand() % 10;
		for( itr2 = network.begin() ; itr2 != network.end() ; itr2++){
			if(i == 1){
				(itr2 -> second).addFriend((itr -> second).getUserName());
				(itr -> second).addFriend((itr2 -> second).getUserName());
			}
		}
	}


	network.save();

	return 0;
}
