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

template<class It>
void
print_key(It it) {
		std::cout	<< "   [ "	<< (*it) << "\t]"
					<< std::endl;
#ifdef DEBUG
		it.print_node_ptr();
#endif
}


template<class Set, class It>
void
print_set(Set& s, const std::string name) {
	std::cout	<< std::endl
				<< "// SET "	<< name << std::endl
				<< "   size:  "	<< s.size() << std::endl
				<< std::endl;
	if (s.empty())
		std::cout << "   [ EMPTY MAP ]" << std::endl;
	else {

#ifdef DEBUG 
		s.print_header();
		std::cout << std::endl;
		s.print_tree();
#else
		for (It it = s.begin(); it != s.end(); ++it) {
			print_key<It>(it);
		}	
#endif
	}
	std::cout	<< std::endl;	
}

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
