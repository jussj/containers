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
void	print_map(Map& m, const std::string name) {
	std::cout	<< std::endl
				<< "// MAP " << name << std::endl
				<< "   size: " << m.size() << std::endl;
	if (m.empty())
		std::cout << "[ EMPTY MAP ]";
	std::cout << std::endl;
}

int 	main() {
	{
		NAMESPACE::map<int, std::string>	a;

		a.insert(NAMESPACE::pair<int, std::string>(0, "hehehe"));
		print_map(a, "A");
	}
	return 0;
}
