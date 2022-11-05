#include <iostream>			// std::cout
#include <map>				// std::stack
#include <stdexcept>
#include <cstddef>			// ptrdiff_t
#include <typeinfo>			// typeid
#include "../inc/map.hpp"

# define T1 int
# define T2 int

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

template<class It>
void
print_pair(It it) {
		std::cout	<< "   [ "	<< (*it).first 
					<< "\t| "	<< (*it).second 
					<< "\t]"	<< std::endl;
#ifdef DEBUG
		it.print_node_ptr();
#endif
}


template<class Map, class It>
void
print_map(Map& m, const std::string name) {
	std::cout	<< std::endl
				<< "// MAP    "	<< name << std::endl
				<< "   size:  "	<< m.size() << std::endl
				<< std::endl;
	if (m.empty())
		std::cout << "   [ EMPTY MAP ]" << std::endl;
	else {

#ifdef DEBUG 
		m.print_header();
		std::cout << std::endl;
		m.print_tree();
#else
		for (It it = m.begin(); it != m.end(); ++it) {
			print_pair<It>(it);
		}	
#endif
	}
	std::cout	<< std::endl;	
}

/*
template<class Map, class It>
void
print_map(Map& m, const std::string name) {
	std::cout	<< std::endl
				<< "// MAP    "	<< name << std::endl
				<< "   size:  "	<< m.size() << std::endl;
	if (!m.empty())
		m.print_header();
	std::cout	<< std::endl;
	if (m.empty())
		std::cout << "   [ EMPTY MAP ]" << std::endl;
	else
		m.print_tree();
	std::cout	<< std::endl;
}
*/

int
main() {
	NAMESPACE::map<int, std::string>			a;
	NAMESPACE::map<int, std::string>::iterator	it;

	NAMESPACE::pair<NAMESPACE::map<int, std::string>::iterator, bool>
		ret;

	std::cout	<< "// EMPTY MAP" << std::endl;

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	std::cout	<< "// INSERT ONE ELEMENT" << std::endl;

	a.insert(NAMESPACE::pair<int, std::string>(4, "four"));
	a.insert(NAMESPACE::pair<int, std::string>(1, "one"));
	a.insert(NAMESPACE::pair<int, std::string>(5, "five"));
	a.insert(NAMESPACE::pair<int, std::string>(0, "zero"));
	a.insert(NAMESPACE::pair<int, std::string>(3, "three"));
	a.insert(NAMESPACE::pair<int, std::string>(10, "ten"));
	
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

	{
		std::cout << "   INSERT W HINT" << std::endl;
		
		NAMESPACE::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( NAMESPACE::pair<char,int>('a',100) );
		mymap.insert ( NAMESPACE::pair<char,int>('z',200) );

		NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( NAMESPACE::pair<char,int>('z',500) );
		if (ret.second==false) {
		  std::cout << "element 'z' already exists";
		  std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		NAMESPACE::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, NAMESPACE::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, NAMESPACE::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		NAMESPACE::map<char,int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	
	}

	std::cout	<< std::endl
				<< "// ITERATOR ACCESS" << std::endl;
	
	it = --a.end();
	
	std::cout	<< "last element pointer: " << std::endl
				<< it->first << ", " << it->second
				<< std::endl;
	
	std::cout	<< "last element reference: " << std::endl
				<< (*it).first << ", " << (*it).second
				<< std::endl;
	
	std::cout	<< "// IT DECREM" << std::endl;

	for (size_t i = 0; i != a.size(); ++i) {
		print_pair(it);
		--it;
	}

	std::cout	<< "// IT POSTFIX INCREM" << std::endl;
	
	it = a.begin();

	while (it != a.end()) {
		std::cout << it->first << ", " << it->second << '\n';
		it++;
	}

	std::cout	<< std::endl
				<< "// CONSTANT ITERATOR ACCESS" << std::endl;
	
	NAMESPACE::map<int, std::string>::iterator	cit;
	
	cit = --a.end();

	std::cout	<< "last element pointer: " << std::endl
				<< cit->first << ", " << cit->second
				<< std::endl;
	
	std::cout	<< "last element reference: " << std::endl
				<< (*cit).first << ", " << (*cit).second
				<< std::endl;

	std::cout	<< std::endl
				<< "// CONSTANT IT DECREM" << std::endl;
	
	for (size_t i = 0; i != a.size(); ++i) {
		print_pair(cit);
		--cit;
	}
	
	std::cout	<< std::endl
				<< "// CONST AND NOT CONST ITERATORS" << std::endl;
    
	//NAMESPACE::map<T1, T2> const mp;
	//NAMESPACE::map<T1, T2>::iterator i = mp.begin(); // NO COMP

	
/*	std::cout	<< std::endl
				<< "// REVERSE IT OPERATIONS" << std::endl
				<< std::endl;

	NAMESPACE::map<int, std::string>::reverse_iterator	beg_rit;
	NAMESPACE::map<int, std::string>::reverse_iterator	end_rit;
	
	end_rit = a.rend() - 1;
	beg_rit = a.rbegin();
	
	std::cout << "   rev it end:   " << *end_rit << std::endl;
	std::cout << "   rev it begin: " << *beg_rit << std::endl;
*/	
	std::cout	<< std::endl
				<< "// BEGIN" << std::endl;
	print_pair(a.begin());
	print_pair(++a.begin());
	//print_pair(a.begin() + 2);	// DOESN'T COMPILE (BIDIR)

	std::cout	<< std::endl
				<< "// END" << std::endl;
	print_pair(--a.end());
	
	std::cout	<< std::endl
				<< "// FIND" << std::endl;
	print_pair(a.find(10));
	
	std::cout	<< std::endl
				<< "// LOWER_BOUND" << std::endl;
	it = a.lower_bound(3);
	print_pair(it);
	it = a.lower_bound(1);
	print_pair(it);
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	std::cout	<< "// ERASE ONE ELEMENT" << std::endl;

	std::cout	<< "   NODE W ZERO CHILD:" << std::endl
				<< std::endl;

	std::cout	<< "   RIGHTMOST:" << std::endl;
	std::cout	<< ">> A size: " << a.size() << std::endl
				<< ">> A end:" << std::endl;
	print_pair(--a.end());
	a.erase(a.find(10));	
	
	std::cout	<< ">> A size: " << a.size() << std::endl
				<< ">> A new end:" << std::endl;
	print_pair(--a.end());
	
	a.erase(a.find(5));
	
	std::cout	<< ">> A size: " << a.size() << std::endl
				<< ">> A new new end:" << std::endl;
	print_pair(--a.end());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	a.insert(NAMESPACE::pair<int, std::string>(5, "five"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	std::cout	<< "   NODE W ONE CHILD:" << std::endl
				<< std::endl;
	
	std::cout	<< ">> B size: " << b.size() << std::endl
				<< ">> B end:" << std::endl;
	print_pair(--b.end());
	b.erase(--b.end());	
	
	std::cout	<< ">> B size: " << b.size() << std::endl
				<< ">> B new end:" << std::endl;
	print_pair(--b.end());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	std::cout	<< "   LEFTMOST:" << std::endl;
	std::cout	<< ">> A size: " << a.size() << std::endl
				<< ">> A begin:" << std::endl;
	print_pair(a.begin());
	a.erase(a.find(0));	
	
	std::cout	<< ">> A size: " << a.size() << std::endl
				<< ">> A new begin:" << std::endl;
	print_pair(a.begin());

	std::cout	<< ">> B size: " << b.size() << std::endl
				<< ">> B begin:" << std::endl;
	print_pair(b.begin());
	b.erase(b.begin());	
	
	std::cout	<< ">> B size: " << b.size() << std::endl
				<< ">> B new begin:" << std::endl;
	print_pair(b.begin());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	std::cout	<< "   NODE W 2 CHILDREN:" << std::endl;

	// but is root

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	b.erase(b.find(5));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	// but closest have NIL children
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	b.erase(b.find(9));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	// huge tree

	NAMESPACE::map<int, std::string>			c;
	
	for (size_t size = 0; size < 20; ++size) {
		c.insert(NAMESPACE::pair<int, std::string>(size, "hehe"));
	}

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");

	c.erase(c.find(3));

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	std::cout	<< "   reinserting deleted elements..." << std::endl;
	
	a.insert(NAMESPACE::pair<int, std::string>(0, "zero"));
	a.insert(NAMESPACE::pair<int, std::string>(10, "ten"));

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	std::cout	<< "   erasing last element..." << std::endl;

	NAMESPACE::map<int, std::string>			d;

	d.insert(NAMESPACE::pair<int, std::string>(0, "zero"));

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(d, "D");

	d.erase(d.find(0));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(d, "D");

	std::cout	<< "   emptying A tree from begin..." << std::endl;

	std::cout	<< std::endl;

	while (!a.empty())
		a.erase(a.begin());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");
	
	std::cout	<< "   emptying B tree from end..." << std::endl;
	
	while (!b.empty())
		b.erase(--b.end());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	
	std::cout	<< "// ERASE RANGE" << std::endl;
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");

	std::cout	<< "   from begin()" << std::endl;
	c.erase(c.begin(), c.find(7));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	std::cout	<< "   to --end()" << std::endl;
	c.erase(c.find(17), --c.end());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	std::cout	<< "   to end()" << std::endl;
	c.erase(c.find(15), c.end());
	
	{
		NAMESPACE::map<char,int> mymap;
		NAMESPACE::map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;

		it=mymap.find('b');
		std::cout << "found b\n";
		mymap.erase (it);                   // erasing by iterator
		std::cout << "erase iterator to b\n";
		mymap.erase ('c');                  // erasing by key
		std::cout << "erase by key 'c'\n";
		it=mymap.find ('e');
		std::cout << "erase by range 'e' to end\n";
		mymap.erase ( it, mymap.end() );    // erasing by range

		std::cout << " display :\n";
		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	
	}
	
	std::cout	<< "// COPY CTOR" << std::endl;

	//NAMESPACE::map<int, std::string>			e(c);

	std::cout	<< "// CLEAR" << std::endl;

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	c.clear();

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	// SHOULD RET NULL	
	//std::cout	<< "   lower_bound after clearance:" << std::endl;
	//print_pair(c.lower_bound(100));
	
	//std::cout	<< std::endl
				//<< "   find after clearance:" << std::endl;
	//print_pair(c.find(100));

	std::cout	<< "// REVERSE ITERATORS" << std::endl;
	
	std::cout	<< "// OPERATOR[]" << std::endl;

	std::cout	<< "   inserting after clearance..." << std::endl;

	c[100]="one hundred";

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");

	std::cout	<< "   lower_bound after insert:" << std::endl;
	print_pair(c.lower_bound(100));
	
	std::cout	<< std::endl
				<< "   find after insert:" << std::endl;
	print_pair(c.find(100));

	return 0; 
}
