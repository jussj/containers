#include <iostream>			// std::cout
#include <map>				// std::stack
#include <stdexcept>
#include <cstddef>			// ptrdiff_t
#include <typeinfo>			// typeid
#include "../inc/map.hpp"

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template<class It>
void	print_pair(It it) {
		std::cout	<< "   [ " << (*it).first 
					<< "\t| " << (*it).second 
					<< "\t]" << std::endl;
}

template<class Map, class It>
void	print_map(Map& m, const std::string name) {
	std::cout	<< std::endl
				<< "// MAP " << name << std::endl
				<< "   size: " << m.size() << std::endl
				<< std::endl;
	if (m.empty())
		std::cout << "   [ EMPTY MAP ]";
	else {
		std::cout << "   MAP: " << std::endl;
		for (It it = m.begin(); it != m.end(); ++it) {
			print_pair<It>(it);
			
		}
	}
	std::cout	<< std::endl;
}

int 	main() {
	{
		NAMESPACE::map<int, std::string>			a;
		NAMESPACE::map<int, std::string>::iterator	it;

		NAMESPACE::pair<NAMESPACE::map<int, std::string>::iterator,
						bool>						ret;

		ret = a.insert(NAMESPACE::pair<int, std::string>(4, "four"));

		print_pair(ret.first);

		a.insert(NAMESPACE::pair<int, std::string>(1, "one"));
		//a.insert(NAMESPACE::pair<int, std::string>(5, "five"));
		a.insert(NAMESPACE::pair<int, std::string>(0, "zero"));
		//a.insert(NAMESPACE::pair<int, std::string>(3, "three"));
		//a.insert(NAMESPACE::pair<int, std::string>(10, "ten"));

		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(a, "A");
	}
	return 0;
}
