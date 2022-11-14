#include <iostream>			// std::cout
#include <map>				// std::map
#include <list>				// std::list
#include <stdexcept>
#include <cstddef>			// ptrdiff_t
#include <typeinfo>			// typeid
#include "../inc/set.hpp"

# define T1 int
# define T2 int

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif
int
main() {
	NAMESPACE::set<std::string>		seth;

	seth.insert("hello my name is seth");

	return 0;	
}
