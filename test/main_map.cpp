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
		std::cout	<< "   [ "	<< (*it).first 
					<< "\t| "	<< (*it).second 
					<< "\t]"	<< std::endl;
		it.print_node_ptr();
}

template<class Map, class It>
void	print_map(Map& m, const std::string name) {
	std::cout	<< std::endl
				<< "// MAP    "	<< name << std::endl
				<< "   size:  "	<< m.size() << std::endl;
	m.print_header();
	std::cout	<< std::endl;
	if (m.empty())
		std::cout << "   [ EMPTY MAP ]";
	else {
	for (It it = m.begin(); it != m.end(); ++it) {
		//It it = m.begin();
		//for (size_t i = 0; i < m.size(); ++i) {
			print_pair<It>(it);
			//++it;
		}
	}
	std::cout	<< std::endl;
}

int 	main() {
	NAMESPACE::map<int, std::string>			a;
	NAMESPACE::map<int, std::string>::iterator	it;

	NAMESPACE::pair<NAMESPACE::map<int, std::string>::iterator,
					bool>						ret;

	std::cout	<< "// INSERT ONE ELEMENT" << std::endl;

	std::cout << "   first element..." << std::endl;	
	ret = a.insert(NAMESPACE::pair<int, std::string>(4, "four"));

	print_pair(ret.first);

	a.insert(NAMESPACE::pair<int, std::string>(1, "one"));
	a.insert(NAMESPACE::pair<int, std::string>(5, "five"));
	a.insert(NAMESPACE::pair<int, std::string>(0, "zero"));
	a.insert(NAMESPACE::pair<int, std::string>(3, "three"));
	ret = a.insert(NAMESPACE::pair<int, std::string>(10, "ten"));
	
	std::cout << "   last element..." << std::endl;	
	print_pair(ret.first);

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	NAMESPACE::map<int, std::string>			b;
	
	b.insert(NAMESPACE::pair<int, std::string>(1, "one"));
	b.insert(NAMESPACE::pair<int, std::string>(2, "two"));

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	b.insert(NAMESPACE::pair<int, std::string>(5, "five"));
	b.insert(NAMESPACE::pair<int, std::string>(4, "four"));
	b.insert(NAMESPACE::pair<int, std::string>(7, "seven"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	b.insert(NAMESPACE::pair<int, std::string>(9, "nine"));
	b.insert(NAMESPACE::pair<int, std::string>(11, "elev"));
	b.insert(NAMESPACE::pair<int, std::string>(10, "ten"));

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	//std::cout	<< std::endl
				//<< "// DECREM" << std::endl;
	//it = ret.first;
	//for (size_t i = 0; i != a.size(); ++i) {
		//print_pair(it);
		//--it;
	//}

	//std::cout	<< std::endl
				//<< "// BEGIN" << std::endl;
	//print_pair(a.begin());
	//print_pair(++a.begin());
	////print_pair(a.begin() + 2);	// DOESN'T COMPILE (BIDIR)
	
	//std::cout	<< std::endl
				//<< "// END" << std::endl;
	//print_pair(--a.end());
	
	//std::cout	<< std::endl
				//<< "// FIND" << std::endl;
	//print_pair(a.find(10));
	
	//std::cout	<< std::endl
				//<< "// LOWER_BOUND" << std::endl;
	//it = a.lower_bound(3);
	//print_pair(it);
	//it = a.lower_bound(1);
	//print_pair(it);
	////it = a.lower_bound(11);		// SHOULD SEGF
	////print_pair(it);

	//print_map<NAMESPACE::map<int, std::string>, 
		//NAMESPACE::map<int, std::string>::iterator>(a, "A");

	//std::cout	<< "// ERASE ONE ELEMENT" << std::endl;
	
	
	//std::cout	<< "   rightmost..." << std::endl;
	//a.erase(a.find(10));	
	
	//std::cout	<< "   >> size: " << a.size() << std::endl
				//<< "   >> new end:" << std::endl;
	//print_pair(--a.end());
	
	//std::cout	<< "   leftmost..." << std::endl;
	//a.erase(a.find(0));	
	
	//std::cout	<< "   >> size: " << a.size() << std::endl
				//<< "   >> new begin:" << std::endl;
	//print_pair(a.begin());

	//std::cout	<< "   reinserting deleted elements..." << std::endl;
	
	//a.insert(NAMESPACE::pair<int, std::string>(0, "zero"));
	//a.insert(NAMESPACE::pair<int, std::string>(10, "ten"));

	//print_map<NAMESPACE::map<int, std::string>, 
		//NAMESPACE::map<int, std::string>::iterator>(a, "A");
	
	//std::cout	<< "   one child..." << std::endl;
	//a.erase(a.find(5));
	
	//print_map<NAMESPACE::map<int, std::string>, 
		//NAMESPACE::map<int, std::string>::iterator>(a, "A");
	
	//std::cout	<< "   two children..." << std::endl;
	//a.erase(a.find(1));
	//std::cout	<< "   >> size: " << a.size() << std::endl;
	
	//print_map<NAMESPACE::map<int, std::string>, 
		//NAMESPACE::map<int, std::string>::iterator>(a, "A");
	
	return 0;
}
