#include <iostream>			// std::cout
#include <map>				// std::map
#include <list>				// std::list
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
		  std::cout << "   with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		NAMESPACE::map<char,int>::iterator it = mymap.begin();
		// max efficiency inserting
		mymap.insert (it, NAMESPACE::pair<char,int>('b',300));
		// no max efficiency inserting
		mymap.insert (it, NAMESPACE::pair<char,int>('c',400));

		// third insert function version (range insertion):
		NAMESPACE::map<char,int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(mymap, "MYMAP");

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(anothermap, "ANOTHERMAP");
	
	}

	std::cout	<< std::endl
				<< "// ITERATOR ACCESS" << std::endl;
	
	it = --a.end();
	
	std::cout	<< "   last element pointer: " << std::endl
				<< "   " << it->first << ", " << it->second
				<< std::endl;
	
	std::cout	<< "   last element reference: " << std::endl
				<< "   " << (*it).first << ", " << (*it).second
				<< std::endl;
	
	std::cout	<< std::endl
				<< "// IT DECREM" << std::endl;

	for (size_t i = 0; i != a.size(); ++i) {
		print_pair(it);
		--it;
	}

	std::cout	<< std::endl
				<< "// IT POSTFIX INCREM" << std::endl;
	
	it = a.begin();

	while (it != a.end()) {
		std::cout	<< "   " << it->first
					<< " " << it->second << '\n';
		it++;
	}

	std::cout	<< std::endl
				<< "// CONSTANT ITERATOR ACCESS" << std::endl;
	
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
				<< "// CONST AND NOT CONST ITERATORS" << std::endl;
    
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

	//NAMESPACE::map<int, std::string>::iterator end = a.end();

	std::cout	<< std::endl
				<< "   iterators:" << std::endl;

	it = a.lower_bound(3);
	print_pair(it);
	it = a.lower_bound(1);
	print_pair(it);
	it = a.lower_bound(13);
	if (it == a.end())
		std::cout << "   RETURN END" << std::endl;
	
	std::cout	<< std::endl
				<< "   const iterators:" << std::endl;

	cit = a.lower_bound(3);
	print_pair(cit);
	cit = a.lower_bound(1);
	print_pair(cit);
	cit = a.lower_bound(13);
	if (cit == a.end())
		std::cout << "   RETURN END" << std::endl;

	std::cout	<< std::endl
				<< "// UPPER_BOUND" << std::endl;

	//NAMESPACE::map<int, std::string>::iterator end = a.end();

	std::cout	<< std::endl
				<< "   iterators:" << std::endl;

	it = a.upper_bound(3);
	print_pair(it);
	it = a.upper_bound(1);
	print_pair(it);
	it = a.upper_bound(13);
	if (it == a.end())
		std::cout << "   RETURN END" << std::endl;
	
	std::cout	<< std::endl
				<< "   const iterators:" << std::endl;

	cit = a.upper_bound(3);
	print_pair(cit);
	cit = a.upper_bound(1);
	print_pair(cit);
	cit = a.upper_bound(13);
	if (cit == a.end())
		std::cout << "   RETURN END" << std::endl;
	
	print_map<NAMESPACE::map<int, std::string>, 
		NAMESPACE::map<int, std::string>::iterator>(a, "A");

	std::cout	<< std::endl
				<< "// LOWER_BOUND/UPPER_BOUND" << std::endl;
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
	//b.erase(--b.end());	
	b.erase(b.find(11));	
	
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
		
		mp.erase(mp.begin(), ++(++(++mp.begin())));
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					mp, "MP range beg, +++beg");

		mp.erase(--(--(--mp.end())), --mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					mp, "MP range beg, -end");

		mp.erase(mp.begin());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP beg");
		
		mp.erase(--mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP -end");
		// two elements left

		mp[10] = "Hello";
		mp[11] = "Hi";
		
		mp.erase(--(--(--mp.end())), mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(
					mp, "MP range ---end, end");

		mp[12] = "ONE";
		mp[13] = "TWO";
		mp[14] = "THREE";
		mp[15] = "FOUR";
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP");
		
		print_pair(mp.begin());
		print_pair(--mp.end()); // NOT OK
		mp.erase(mp.begin(), mp.end());
		
		print_map<NAMESPACE::map<int, std::string>, 
			NAMESPACE::map<int, std::string>::iterator>(mp, "MP all");
	}
/*	std::cout	<< std::endl
				<< "// COPY CTOR" << std::endl;

	//NAMESPACE::map<int, std::string>			e(c);

	std::cout	<< "// CLEAR" << std::endl;

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
				<< "// OPERATOR[]" << std::endl;

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
				<< "// COMPARISON OPERATORS" << std::endl;
	{
		NAMESPACE::map<char,int> foo,bar;
		
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
		if (foo <= bar) 
			std::cout << "   foo is less than or equal to bar :(\n";
		if (foo >= bar) 
			std::cout << "   foo is greater than or equal to bar :)\n";
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

		std::cout << "   is deep swap? clearing haha:" << std::endl;	
		haha.clear();
		
		print_map<NAMESPACE::map<int, char>, 
			NAMESPACE::map<int, char>::iterator>(hehe, "HEHE");

		std::cout	<< "   MAZOIZ SWUAP TESTS:" << std::endl;	

		NAMESPACE::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		NAMESPACE::map<char, int>::const_iterator tmp = foo.begin();
		//tmp iterates through foo
		NAMESPACE::map<char, int>::const_iterator tmp2 = bar.begin(); 
		//tmp2 iterates through bar
		
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

		NAMESPACE::map<char, int>::const_iterator tmp3 = other.begin();	
		// tmp3 iterates through other

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

		while(tmp != bar.end()) {
			std::cout << "   " <<tmp->first << ": "
				<< tmp->second << '\n';
			tmp++;
		}
		tmp--;

		while(tmp2 != foo.end()) {
			std::cout << "   " <<tmp2->first << ": "
				<< tmp2->second << '\n';
			tmp2++;
		}
		tmp2--;

		other.swap(foo); //tmp2 iterates through other
						//tmp3 iterates throught foo
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(other, "OTHER");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(foo, "FOO");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(bar, "BAR");
		
		while(tmp != bar.begin()) {
			std::cout << "   " <<tmp->first << ": "
				<< tmp->second << '\n';
			tmp--;
		}
		std::cout << "   " <<tmp->first << ": "
			<< tmp->second << '\n';

		while(tmp2 != other.begin()) {
			std::cout << "   " <<tmp2->first << ": "
			   	<< tmp2->second << '\n';
			tmp2--;
		}
		std::cout << "   " <<tmp2->first << ": "
			<< tmp2->second << '\n';

		while(tmp3 != foo.end()) {
			std::cout << "   " <<tmp3->first << ": "
				<< tmp3->second << '\n';
			tmp3++;
		}
		tmp3--;

		bar.swap(foo); //tmp3 iterates through bar
					//tmp iterates through foo

		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(other, "OTHER");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(foo, "FOO");
		print_map<NAMESPACE::map<char, int>, 
			NAMESPACE::map<char, int>::iterator>(bar, "BAR");

		while(tmp != foo.end()) {
			std::cout << "   " <<tmp->first << ": "
				<< tmp->second << '\n';
			tmp++;
		}

		while(tmp2 != other.end()) {
			std::cout << "   " <<tmp2->first << ": "
				<< tmp2->second << '\n';
			tmp2++;
		}

		while(tmp3 != bar.begin()) {
			std::cout << "   " <<tmp3->first << ": "
				<< tmp3->second << '\n';
			tmp3--;
		}
		std::cout << "   " <<tmp3->first << ": "
			<< tmp3->second << '\n';
	}*/
	return 0; 
}
