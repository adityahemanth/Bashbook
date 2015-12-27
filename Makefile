all:

	clang++ -std=c++11 WallPost.cpp Wall.cpp User.cpp UserNetwork.cpp Interface.cpp -o Application -Wc++11-extensions
	