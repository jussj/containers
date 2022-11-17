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

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(seth, "SETH");
	
	seth.erase(it);

	if (seth.empty())
		std::cout	<< "seth is empty inside :)" << std::endl;

	seth.insert("hehe");
	seth.insert("haha");
	seth.insert("hoho");
	seth.insert("huhu");
	seth.insert("hihi");
	seth.insert("hhhh");
	
	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(seth, "SETH");

	NAMESPACE::set<std::string>				sept(seth);
	NAMESPACE::set<std::string>				certes(seth.begin(), --seth.end());
	
	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(sept, "SEPT");

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(certes, "CERTES");

	sept.erase(++(++sept.begin()), sept.end());

	sept.insert("HAHA");
	sept.insert("HEHE");
	sept.insert("HIHI");

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(sept, "SEPT");
	
	certes.swap(sept);
	
	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(sept, "SEPT");

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(certes, "CERTES");

	NAMESPACE::set<std::string>				tess;

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(tess, "TESS");

	tess.swap(certes);

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(tess, "TESS");

	print_set<NAMESPACE::set<std::string>, 
		NAMESPACE::set<std::string>::iterator>(certes, "CERTES");

	std::cout	<< "// ITERATORS" << std::endl
				<< std::endl;

	it = seth.begin();

	NAMESPACE::set<std::string>::const_iterator			cit(it);
	NAMESPACE::set<std::string>::reverse_iterator		rit(++cit);
	NAMESPACE::set<std::string>::const_reverse_iterator	crit(++it);
	
	std::cout << *it << std::endl;	
	std::cout << *cit << std::endl;	
	std::cout << *rit << std::endl;	
	std::cout << *rit++ << std::endl;	
	std::cout << *(crit--)-- << std::endl;

	std::cout	<< std::endl
				<< "// COMPARISON" << std::endl
				<< std::endl;

	if (seth == certes)
		std::cout << "seth and certes are equal :(" << std::endl;
	if (seth != certes)
		std::cout << "seth and certes are not equal :)" << std::endl;
	if (seth > certes)
		std::cout << "seth is superior to certes :)" << std::endl;
	if (seth < certes)
		std::cout << "seth is inferior to certes :(" << std::endl;
	if (seth >= certes)
		std::cout << "seth is superior or equal to certes :)" << std::endl;
	if (seth <= certes)
		std::cout << "seth is inferior or equal to certes :(" << std::endl;

	return 0;	
}
