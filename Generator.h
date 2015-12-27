#ifndef Generator_H
#define Generator_H

#include <string>
#include <vector>

class Generator {

public:
	Generator();
	std::string getUserName();
	std::string getRealName();
	std::string getCity();

private:
	std::vector<std::string> names;
};

#endif