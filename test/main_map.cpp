#include <iostream>			// std::cout
#include <map>				// std::stack
#include <stdexcept>
#include <cstddef>			// ptrdiff_t
#include <typeinfo>			// typeid
#include "../inc/map.hpp"

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template<class Map>
void	print_map(Map m, std::string name) {
	std::cout	<< std::endl
				<< "// MAP " << name << std::endl
				<< "   size: " << m.size() << std::endl;
				//<< "   top:	\"" << s.top() << "\"" << std::endl;
	if (m.empty())
		std::cout << "[ EMPTY MAP ]";
	std::cout << std::endl;
}

int 	main() {
	{
		NAMESPACE::map<int, std::string>	a;

		//print_map(a, "A");
	}
	return 0;
}
