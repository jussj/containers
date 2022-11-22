#include <iostream>			// std::cout
#include <map>				// std::map
#include <list>				// std::list
#include <stdexcept>
#include <algorithm>
#include <cstddef>			// ptrdiff_t
#include <typeinfo>			// typeid
#include <unistd.h>							// 
#include "../inc/map.hpp"
#include "inc/benchmark.hpp"

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
				<< "// MAP "	<< name << std::endl
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

template<class Map, class It>
void
print_reverse(Map& m, const std::string name) {
	std::cout	<< std::endl
				<< "// REVERSE MAP " << name << std::endl
				<< "   size:  "	<< m.size() << std::endl
				<< std::endl;
	if (m.empty())
		std::cout << "   [ EMPTY MAP ]" << std::endl;
	else {
		for (It it = m.rbegin();
				it != m.rend(); it++	) {
			std::cout	<< "   [ "	<< (*it).first 
						<< "\t| "	<< (*it).second 
						<< "\t]"	<< std::endl;
		}
	}
}

void
main_test_map() {
	NAMESPACE::map<int, std::string>			a;
	NAMESPACE::map<int, std::string>::iterator	it;

	NAMESPACE::pair<NAMESPACE::map<int, std::string>::iterator, bool>
		ret;

	std::cout	<< "// MY FIRST MAP <3 AND IT IS EMPTY AF //" << std::endl;

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	std::cout	<< "// INSERT //" << std::endl
				<< std::endl;
	
	std::cout	<< "// INSERT ONE ELEMENT" << std::endl;

	a.insert(NAMESPACE::pair<int, std::string>(4, "four"));
	a.insert(NAMESPACE::pair<int, std::string>(1, "one"));
	a.insert(NAMESPACE::pair<int, std::string>(5, "five"));
	a.insert(NAMESPACE::pair<int, std::string>(0, "zero"));
	a.insert(NAMESPACE::pair<int, std::string>(3, "three"));
	a.insert(NAMESPACE::pair<int, std::string>(10, "ten"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(a, "A");
	
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
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	b.insert(NAMESPACE::pair<int, std::string>(11, "elev"));
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	b.insert(NAMESPACE::pair<int, std::string>(10, "ten"));
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	std::cout	<< "   INSERT RANGE" << std::endl;
	
	NAMESPACE::map<int, std::string>			bb;

	bb.insert(b.find(1), b.find(5));

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(bb, "BB");
	
	std::cout	<< "   INSERT W HINT" << std::endl;
	
	std::cout	<< "   hint 1, new 9 after last elem"
				<< std::endl;
	
	bb.insert(bb.find(1),
		NAMESPACE::pair<int, std::string>(9, "nine"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(bb, "BB");

	std::cout	<< "   hint 1, new 6 before last elem"
				<< std::endl;
	
	bb.insert(bb.find(1),
		NAMESPACE::pair<int, std::string>(6, "six"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(bb, "BB");
	
	std::cout	<< "   hint 4, new 3 before last elem"
				<< std::endl;
	
	bb.insert(bb.find(4),
		NAMESPACE::pair<int, std::string>(3, "three"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(bb, "BB");
	
	{
		NAMESPACE::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert (NAMESPACE::pair<char,int>('a',100));
		mymap.insert (NAMESPACE::pair<char,int>('z',200));

		NAMESPACE::pair<
			NAMESPACE::map<char,int>::iterator,bool> ret;
		ret = mymap.insert (
			NAMESPACE::pair<char,int>('z',500));
		if (ret.second==false) {
		  std::cout << "   element 'z' already exists";
		  std::cout << " with a value of " << ret.first->second << '\n';
		}

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");
		// second insert function version (with hint position):
		NAMESPACE::map<char,int>::iterator it = mymap.begin();
		// max efficiency inserting
		mymap.insert (it, NAMESPACE::pair<char,int>('b',300));
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");
		// no max efficiency inserting
		mymap.insert (it, NAMESPACE::pair<char,int>('c',400));
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");

		// third insert function version (range insertion):
		NAMESPACE::map<char,int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(anothermap, "ANOTHERMAP");
	
	}

	std::cout	<< std::endl
				<< "// ITERATOR ACCESS //" << std::endl;
	
	it = --a.end();
	
	std::cout	<< "   last element pointer: " << std::endl
				<< "   " << it->first << ", " << it->second
				<< std::endl;
	
	std::cout	<< "   last element reference: " << std::endl
				<< "   " << (*it).first << ", " << (*it).second
				<< std::endl;
	
	std::cout	<< std::endl
				<< "// IT PREFIX DECREM //" << std::endl;

	for (size_t i = 0; i != a.size(); ++i) {
		print_pair(it);
		--it;
	}

	std::cout	<< std::endl
				<< "// IT POSTFIX INCREM //" << std::endl;
	
	it = a.begin();

	while (it != a.end()) {
		std::cout	<< "   " << it->first
					<< " " << it->second << '\n';
		it++;
	}

	std::cout	<< std::endl
				<< "// CONSTANT ITERATOR ACCESS //" << std::endl;
	
	NAMESPACE::map<int, std::string>::iterator	cit;
	
	cit = --a.end();

	std::cout	<< "   last element pointer: " << std::endl
				<< "   " << cit->first << ", " << cit->second
				<< std::endl;
	
	std::cout	<< "   last element reference: " << std::endl
				<< "   " << (*cit).first << ", " << (*cit).second
				<< std::endl;

	std::cout	<< std::endl
				<< "// CONSTANT IT DECREM" << std::endl;
	
	for (size_t i = 0; i != a.size(); ++i) {
		print_pair(cit);
		--cit;
	}
	
	std::cout	<< std::endl
				<< "// CONST AND NOT CONST ITERATORS //" << std::endl;
    
	//NAMESPACE::map<T1, T2> const mp;
	//NAMESPACE::map<T1, T2>::iterator i = mp.begin(); // NO COMP

	//std::cout	<< std::endl
				//<< "// REVERSE IT OPERATIONS" << std::endl
				//<< std::endl;

	//NAMESPACE::map<int, std::string>::reverse_iterator	beg_rit;
	//NAMESPACE::map<int, std::string>::reverse_iterator	end_rit;
	
	//end_rit = a.rend() - 1;
	//beg_rit = a.rbegin();
	
	//std::cout << "   rev it end:   " << *end_rit << std::endl;
	//std::cout << "   rev it begin: " << *beg_rit << std::endl;
	
	std::cout	<< std::endl
				<< "// BEGIN //" << std::endl;
	print_pair(a.begin());
	print_pair(++a.begin());
	//print_pair(a.begin() + 2);	// DOESN'T COMPILE (BIDIR)

	std::cout	<< std::endl
				<< "// END //" << std::endl;
	print_pair(--a.end());
	
	std::cout	<< std::endl
				<< "// FIND //" << std::endl;
	print_pair(a.find(10));
	
	std::cout	<< std::endl
				<< "// LOWER_BOUND //" << std::endl;

	//NAMESPACE::map<int, std::string>::iterator end = a.end();

	std::cout	<< std::endl
				<< "   iterators:" << std::endl;

	it = a.lower_bound(3);
	print_pair(it);
	it = a.lower_bound(1);
	print_pair(it);
	it = a.lower_bound(13);
	if (it == a.end())
		std::cout << std::endl << "   IT RETURN END" << std::endl;
	
	std::cout	<< std::endl
				<< "   const iterators:" << std::endl;

	cit = a.lower_bound(3);
	print_pair(cit);
	cit = a.lower_bound(1);
	print_pair(cit);
	cit = a.lower_bound(13);
	if (cit == a.end())
		std::cout << std::endl << "   CIT RETURN END" << std::endl;

	std::cout	<< std::endl
				<< "// UPPER_BOUND //" << std::endl;

	//NAMESPACE::map<int, std::string>::iterator end = a.end();

	std::cout	<< std::endl
				<< "   iterators:" << std::endl;

	it = a.upper_bound(3);
	print_pair(it);
	it = a.upper_bound(1);
	print_pair(it);
	it = a.upper_bound(13);
	if (it == a.end())
		std::cout << std::endl << "   IT RETURN END" << std::endl;
	
	std::cout	<< std::endl
				<< "   const iterators:" << std::endl;

	cit = a.upper_bound(3);
	print_pair(cit);
	cit = a.upper_bound(1);
	print_pair(cit);
	cit = a.upper_bound(13);
	if (cit == a.end())
		std::cout << std::endl << "   CIT RETURN END" << std::endl;
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	std::cout	<< std::endl
				<< "// LOWER_BOUND/UPPER_BOUND //" << std::endl;
	{
		NAMESPACE::map<char,int> mymap;
		NAMESPACE::map<char,int>::iterator itlo,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;

		itlo	= mymap.lower_bound ('b');
		itup	= mymap.upper_bound ('d');

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");
		
		std::cout	<< "   lower : " << itlo->first << '\n';
		std::cout	<< "   upper : " << itup->first << '\n';

		std::cout	<< std::endl
					<< "   DELETING FROM b TO RIGHTMOST, e"
					<< std::endl;

		mymap.erase(itlo, itup);

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");
	}

	std::cout	<< "// ERASE //" << std::endl
				<< std::endl;

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

	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(a, "A");
	
	a.insert(NAMESPACE::pair<int, std::string>(5, "five"));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	std::cout	<< "   NODE W ONE CHILD:" << std::endl
				<< std::endl;
	
	std::cout	<< ">> B size: " << b.size() << std::endl
				<< ">> B end:" << std::endl;
	print_pair(--b.end());
	//b.erase(--b.end());	
	b.erase(b.find(11));	
	
	std::cout	<< ">> B size: " << b.size() << std::endl
				<< ">> B new end:" << std::endl;
	print_pair(--b.end());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(b, "B");
	
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

	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(b, "B");
	
	std::cout	<< "   NODE W 2 CHILDREN:" << std::endl;

	// but is root

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	b.erase(b.find(5));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(b, "B");
	
	// but closest have NIL children
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");

	b.erase(b.find(9));
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(b, "B");
	
	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(b, "B");
	
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
	
	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(c, "C");
	
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
	
	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(c, "C");
	
	std::cout	<< "   to --end()" << std::endl;
	c.erase(c.find(17), --c.end());
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	print_reverse<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::reverse_iterator>(c, "C");
	
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

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");

		it=mymap.find('b');
		std::cout << "   found b\n";
		// erasing by iterator
		mymap.erase (it);
		std::cout << "   erase iterator to b\n";
		// erasing by key
		mymap.erase ('c');
		std::cout << "   erase by key 'c'\n";
		it=mymap.find ('e');
		std::cout << "   erase by range 'e' to end\n";
		// erasing by range
		mymap.erase (it, mymap.end());    

		std::cout << "   display :\n";
		// show content: d should be 40
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout	<< "   "
						<< it->first << " " << it->second << '\n';
		
		mymap.erase (mymap.begin(), mymap.end());    
		
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");
	
		print_reverse<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::reverse_iterator>(mymap, "MYMAP");
	}

	std::cout	<< std::endl
				<< "// MORE ERASE" << std::endl;
	{
		std::list<NAMESPACE::pair<int, std::string> > lst;
		unsigned int lst_size = 10;
		
		for (unsigned int i = 0; i < lst_size; ++i)
			lst.push_back(
					NAMESPACE::pair<int, std::string>(
						i, std::string((lst_size - i), i + 65))
					);
		
		NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP");
		
		mp.erase(++mp.begin());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP +beg");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(mp, "MP +beg");
		
		mp.erase(mp.begin(), ++(++(++mp.begin())));
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					mp, "MP range beg, +++beg");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					mp, "MP range beg, +++beg");
		
		mp.erase(--(--(--mp.end())), --mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					mp, "MP range beg, -end");

		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					mp, "MP range beg, -end");
		
		mp.erase(mp.begin());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP beg");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					mp, "MP beg");
		
		mp.erase(--mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP -end");
		// two elements left

		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					mp, "MP -end");
		
		mp[10] = "Hello";
		mp[11] = "Hi";
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP insert 2");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					mp, "MP insert 2");
		
		print_pair(mp.begin());
		print_pair(--mp.end()); // NOT OK
		
		mp.erase(--(--(--mp.end())), mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					mp, "MP range ---end, end");

		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					mp, "MP range ---end, end");
		
		mp[12] = "ONE";
		mp[13] = "TWO";
		mp[14] = "THREE";
		mp[15] = "FOUR";
	
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(mp, "MP");
		
		print_pair(mp.begin());
		print_pair(--mp.end()); // NOT OK
		mp.erase(mp.begin(), mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP all");

		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(mp, "MP");
		
		NAMESPACE::map<int, std::string> fck(lst.begin(), lst.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(fck, "FCK");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(fck, "FCK");
		
		fck.erase(++fck.begin(), --fck.end());

		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					fck, "FCK erase +beg to -end");

		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					fck, "FCK erase +beg to -end");
		
		fck.erase(++fck.begin(), --fck.end());

		print_pair(fck.begin());

		std::cout << "END:" << std::endl;
		print_pair(--fck.end()); // NOT OK
		
		fck.erase(--(--fck.end()), fck.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					fck, "FCK erase ---end to end");
		
		print_reverse<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::reverse_iterator>(
					fck, "FCK erase ---end to end");
		
	}
	
	std::cout	<< "// CLEAR //" << std::endl;

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	c.clear();

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");
	
	//std::cout	<< "   lower_bound after clearance (UNDEFINED):"
				//<< std::endl;
	//print_pair(c.lower_bound(100));
	
	//std::cout	<< std::endl
				//<< "   find after clearance (UNDEFINED):"
				//<< std::endl;
	//print_pair(c.find(100));

	std::cout	<< std::endl
				<< "// OPERATOR[] //" << std::endl;

	std::cout	<< "   inserting after clearance..." << std::endl;

	c[100]="one hundred";

	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(c, "C");

	std::cout	<< "   lower_bound after insert:" << std::endl;
	print_pair(c.lower_bound(100));
	
	std::cout	<< std::endl
				<< "   find after insert:" << std::endl;
	print_pair(c.find(100));

	std::cout	<< std::endl
				<< "// COMPARISON OPERATORS //" << std::endl;
	{
		NAMESPACE::map<char,int> foo, bar;
		
		foo['a']=100;
		foo['b']=200;
		bar['a']=10;
		bar['z']=1000;

		if (foo == bar) 
			std::cout << "   foo and bar are equal :(\n";
		if (foo != bar) 
			std::cout << "   foo and bar are not equal :)\n";
		if (foo < bar) 
			std::cout << "   foo is less than bar :(\n";
		if (foo > bar) 
			std::cout << "   foo is greater than bar :)\n";
		if (bar < foo) 
			std::cout << "   bar is less than foo :)\n";
		if (bar > foo) 
			std::cout << "   bar is greater than foo :(\n";
		if (foo <= bar) 
			std::cout << "   foo is less than or equal to bar :)\n";
		if (foo >= bar) 
			std::cout << "   foo is greater than or equal to bar :)\n";

		std::cout	<< std::endl
					<< "   B IS SAME KEY BUT DIFFERENT VALUE" << std::endl;
		bar.erase(--bar.end());
		bar.insert(NAMESPACE::pair<char, int>('z', 500));

		if (foo == bar) 
			std::cout << "   foo and bar are equal :(\n";
		if (foo != bar) 
			std::cout << "   foo and bar are not equal :)\n";
		if (foo < bar) 
			std::cout << "   foo is less than bar :(\n";
		if (foo > bar) 
			std::cout << "   foo is greater than bar :)\n";
		if (foo <= bar) 
			std::cout << "   foo is less than or equal to bar :)\n";
		if (foo >= bar) 
			std::cout << "   foo is greater than or equal to bar :)\n";
		
		std::cout	<< std::endl
					<< "   SAME MAP" << std::endl;
		NAMESPACE::map<char, int> palo, map;

		palo['a'] = 2;
		palo['b'] = 3;
		palo['c'] = 4;
		palo['d'] = 5;

		map['a'] = 2;
		map['b'] = 3;
		map['c'] = 4;
		map['d'] = 5;

		if (palo == palo)
			std::cout << "   palo is the same :)" << std::endl;
		if (palo != palo)
			std::cout << "   palo is different :(" << std::endl;	
		if (palo == map)
			std::cout << "   palomap :)" << std::endl;
		if (palo != map)
			std::cout << "   palo and map are different :(" << std::endl;	
		if (palo < map) 
			std::cout << "   palo is less than map :(\n";
		if (palo > map) 
			std::cout << "   palo is greater than map :)\n";
		if (palo <= map) 
			std::cout << "   palo is less than or equal to map :)\n";
		if (palo >= map) 
			std::cout << "   palo is greater than or equal to map :)\n";

		map.erase(--(--map.end()), map.end());
		map['e'] = 6;
		map['f'] = 7;
		
		if (palo == map)
			std::cout << "   palomap :(" << std::endl;
		if (palo != map)
			std::cout << "   palo and map are different :)" << std::endl;	
		if (palo < map) 
			std::cout << "   palo is less than map :)\n";
		if (palo > map) 
			std::cout << "   palo is greater than map :(\n";
		if (palo <= map) 
			std::cout << "   palo is less than or equal to map :)\n";
		if (palo >= map) 
			std::cout << "   palo is greater than or equal to map :)\n";

	}
	std::cout	<< std::endl
				<< "// SWUAP" << std::endl;

	{
		NAMESPACE::map<int, char> hehe, haha;
		NAMESPACE::map<char, int> hihi;

		hehe[1]='a';
		hehe[2]='b';
		hehe[3]='c';
		hehe[4]='d';
		
		haha[5]='e';
		haha[6]='f';
		haha[7]='g';
		haha[8]='h';
		haha[9]='i';
		
		print_map<NAMESPACE::map<int, char>, 
			NAMESPACE::map<int, char>::iterator>(hehe, "HEHE");
		
		print_map<NAMESPACE::map<int, char>, 
			NAMESPACE::map<int, char>::iterator>(haha, "HAHA");

		std::cout << "   performing swap:" << std::endl;	
		hehe.swap(haha);		

		print_map<NAMESPACE::map<int, char>, 
			NAMESPACE::map<int, char>::iterator>(hehe, "HEHE");
		
		print_map<NAMESPACE::map<int, char>, 
			NAMESPACE::map<int, char>::iterator>(haha, "HAHA");

		std::cout << "   is swap DEEP? clearing haha:" << std::endl;	
		haha.clear();
		
		print_map<NAMESPACE::map<int, char>, 
			NAMESPACE::map<int, char>::iterator>(hehe, "HEHE");

		std::cout	<< "   MAZOIZ SWUAP TESTS:" << std::endl;	

		NAMESPACE::map<char,int> foo, bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		NAMESPACE::map<char, int>::const_iterator foo_it = foo.begin();
		NAMESPACE::map<char, int>::const_iterator bar_it = bar.begin(); 
		
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(foo, "FOO");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(bar, "BAR");
		
		foo.swap(bar);

		NAMESPACE::map<char, int>	other;

		other['1'] = 73;
		other['2'] = 173;
		other['3'] = 763;
		other['4'] = 73854;
		other['5'] = 74683;
		other['6'] = 753;

		NAMESPACE::map<char, int>::const_iterator other_it = other.begin();	

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(foo, "FOO");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(bar, "BAR");

		std::cout << "   " <<"foo contains:\n";
		for (NAMESPACE::map<char,int>::iterator it=foo.begin();
				it!=foo.end(); ++it)
			std::cout << "   " <<it->first << ": "
					<< it->second << '\n';

		std::cout << "   " <<"bar contains:\n";
		for (NAMESPACE::map<char,int>::iterator it=bar.begin();
				it!=bar.end(); ++it)
			std::cout << "   " <<it->first << ": "
				<< it->second << '\n';

		while(foo_it != bar.end()) {
			std::cout << "   " <<foo_it->first << ": "
				<< foo_it->second << '\n';
			foo_it++;
		}
		foo_it--;

		while(bar_it != foo.end()) {
			std::cout << "   " <<bar_it->first << ": "
				<< bar_it->second << '\n';
			bar_it++;
		}
		bar_it--;

		other.swap(foo);
		
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(other, "OTHER");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(foo, "FOO");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(bar, "BAR");
		
		while(foo_it != bar.begin()) {
			std::cout << "   " <<foo_it->first << ": "
				<< foo_it->second << '\n';
			foo_it--;
		}
		std::cout << "   " <<foo_it->first << ": "
			<< foo_it->second << '\n';

		while(bar_it != other.begin()) {
			std::cout << "   " <<bar_it->first << ": "
			   	<< bar_it->second << '\n';
			bar_it--;
		}
		std::cout << "   " <<bar_it->first << ": "
			<< bar_it->second << '\n';

		while(other_it != foo.end()) {
			std::cout << "   " <<other_it->first << ": "
				<< other_it->second << '\n';
			other_it++;
		}
		other_it--;

		bar.swap(foo);

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(other, "OTHER");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(foo, "FOO");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(bar, "BAR");

		while(foo_it != foo.end()) {
			std::cout << "   " <<foo_it->first << ": "
				<< foo_it->second << '\n';
			foo_it++;
		}

		while(bar_it != other.end()) {
			std::cout << "   " <<bar_it->first << ": "
				<< bar_it->second << '\n';
			bar_it++;
		}

		while(other_it != bar.begin()) {
			std::cout << "   " <<other_it->first << ": "
				<< other_it->second << '\n';
			other_it--;
		}
		std::cout << "   " <<other_it->first << ": "
			<< other_it->second << '\n';

		std::cout	<< std::endl
					<< "   SWAP WITH EMPTY CONTAINERS (BAREFOOT)" << std::endl;

		NAMESPACE::map<char, int>					barefoot;
		NAMESPACE::map<char, int>					barecopy(barefoot);
		NAMESPACE::map<char, int>					empty;

		NAMESPACE::map<char, int>::const_iterator	cit_foo = foo.begin();
		NAMESPACE::map<char, int>::const_iterator	cit_bare = barefoot.begin();

		NAMESPACE::swap(foo, barefoot);

		std::cout << "   foo size after swap:      " << foo.size() << std::endl;
		std::cout << "   barefoot size after swap: " << barefoot.size() << std::endl;

		if (cit_bare == foo.end())
			std::cout << "   barefoot it begin == foo end()" << std::endl;
		
		if (cit_bare == barefoot.end())
			std::cout << "   barefoot it begin == barefoot end()" << std::endl;
		
		if (cit_foo == foo.end())
			std::cout << "   foo it begin == foo end()" << std::endl;
		
		if (cit_foo == barefoot.end())
			std::cout << "   foo it begin == barefoot end()" << std::endl;
		
		if (foo.begin() == foo.end())
			std::cout << "   foo begin() == foo end()" << std::endl;

		while (cit_foo != barefoot.end()) {
			std::cout << "   " <<cit_foo->first << ": "
				<< cit_foo->second << '\n';
			cit_foo++;
		}
		
		NAMESPACE::swap(foo, empty);
		
	}

	std::cout	<< std::endl
				<< "// COPY CTOR //" << std::endl;

	d[3]="make";
	d[5]="stop";
	d[4]="dis";
	d[1]="pls";
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(d, "D");

	NAMESPACE::map<int, std::string>			e(d);
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(e, "E");
	
	//std::cout	<< std::endl
				//<< "// 1 MILLION INSERT AND DELETE :))) //" << std::endl;

	//NAMESPACE::map<int, std::string>			f;

	//for (int i = 0; i < 1000000; ++i) {
		//f.insert(NAMESPACE::pair<int, std::string>(i, "POUET"));	
	//}

	//while (!f.empty()) {
		//f.erase(f.begin());	
	//}
	{
		std::cout	<< "// BEGINNING TO END" << std::endl
					<< std::endl;
		
		NAMESPACE::map<int, std::string> mymap;

		mymap.insert(mymap.begin(), NAMESPACE::pair<int, std::string>(1, "one"));
		mymap.insert(NAMESPACE::pair<int, std::string>(9, "nine"));

  // show content:
		std::cout	<< "   after insert:" << std::endl;
		for (NAMESPACE::map<int, std::string>::iterator it = mymap.begin(); 
			it != mymap.end(); ++it)
		std::cout << "   " << it->first << " => " << it->second << '\n';
		
		mymap.erase(mymap.begin());
		mymap.erase(--mymap.end());
		
		std::cout	<< "   after erase:" << std::endl;
		for (NAMESPACE::map<int, std::string>::iterator it = mymap.begin(); 
				it != mymap.end(); ++it)
			std::cout << "   " << it->first << " => " << it->second << '\n';
	}
}

int
main() {
	//measure_performance(main_test_map, "MAIN");
	main_test_map();
	return 0;
}
