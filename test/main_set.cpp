#include <iostream>			// std::cout
#include <set>				// std::set
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
	NAMESPACE::set<std::string>				seth;
	NAMESPACE::set<std::string>::iterator	it;

	seth.insert("hello my name is seth");

	it = seth.begin();
	std::cout<<*(it)<<std::endl;

	seth.erase(it);

	if (seth.empty())
		std::cout<<"seth is empty inside :)"<<std::endl;

	return 0;	
}
