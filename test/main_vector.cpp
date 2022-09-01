#ifndef NAMESPACE
# define NAMESPACE ft

#endif

#include <vector>
#include "../inc/Vector.hpp"
#include <iostream>
#include "../test/vector/TestVector.hpp"
#include "../test/vector/ComplexClass.hpp"
//#include "TestVecIterators.hpp"
#include <cstddef>		// ptrdiff_t
#include <typeinfo>		// typeid

int 	main() {
	NAMESPACE::vector<int>						a;
	NAMESPACE::vector<int>						b(50, 5);	
	NAMESPACE::vector<std::string>				c(4, "he");
	NAMESPACE::vector<IncrediblyComplex<int> >	d(5);
	//NAMESPACE::vector<IncrediblyComplex>	d(5);

	print_info(a, "A");
	print_info(c, "C");
	//print_info(d, "D");

	print_info(b, "B");
	print_content(b, "B");
	
	if (a.empty())
		std::cout << "A is empty" << std::endl;
	if (!c.empty())
		std::cout << "C is NOT empty" << std::endl;
	if (!d.empty())
		std::cout << "D is NOT empty" << std::endl;

	std::cout 	<< "a.reserve(0)..." << std::endl;
	a.reserve(0);
	
	std::cout << "a.reserve(max_size + 1)..." << std::endl;
	try {
		a.reserve(a.max_size()+1);
	}
	catch (std::length_error& le) {
		std::cerr << "error thrown: " << le.what() << std::endl;
	}
	
	std::cout 	<< "a.reserve(7)..." << std::endl;
	a.reserve(5);
	std::cout	<< "size of A is " << a.size()
			<< ", actual capacity is " << a.capacity()
			<< std::endl;

	std::cout	<< "a.push_back() * 6 (past capacity)..." << std::endl;
	a.push_back(42);
	a.push_back(789);
	a.push_back(321321);
	a.push_back(12);
	a.push_back(-89);
	a.push_back(021321);

	print_content(a, "A");


	//NAMESPACE::vector<IncrediblyComplex<int> >	e(9);

//	std::cout	<< "d.push_back(9)..." << std::endl;
//	d.push_back(d(9));
	std::cout	<< "d.pop_back()..." << std::endl;
	
	d.pop_back();
//	print_content(d, "D");
	std::cout	<< "//// RESERVE ////" << std::endl;

	std::cout 	<< "c.reserve(4)..." << std::endl;
	c.reserve(4);

	print_info(c, "C");

	std::cout 	<< "c.reserve(9)..." << std::endl;
	c.reserve(9);
	
	print_info(c, "C");

	std::cout	<< "//// PUSH & POP ////" << std::endl;
	
	std::cout	<< "c.pop_back()..." << std::endl;
	c.pop_back();
	
	print_info(c, "C");
	print_content(c, "C");
	
	std::cout << std::endl;
	std::cout	<< "c.push_back(ha)..." << std::endl;
	c.push_back("ha");
	
	print_info(c, "C");
	print_content(c, "C");

	std::cout	<< "//// RESIZE ////" << std::endl;
	
	std::cout 	<< "c.resize(10, hi).." << std::endl;
	c.resize(10, "hi");
	
	print_info(c, "C");
	print_content(c, "C");

	std::cout 	<< "c.resize(3).." << std::endl;
	c.resize(3);
	
	print_info(c, "C");
	print_content(c, "C");

	std::cout 	<< "c.resize(6, ha).." << std::endl;
	c.resize(6, "ha");

	print_info(c, "C");	
	print_content(c, "C");

	std::cout 	<< "c.resize(12) with NULL value..." << std::endl;
	c.resize(12);

	print_info(c, "C");

	std::cout	<< "//// AT ////" << std::endl;

	std::cout	<< "in range: element at(0) is "
			<< c.at(0) << std::endl;
	std::cout	<< "past size(): element at(3) is ";
	try {
		std::cout	<< c.at(3) << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "error thrown: " << e.what() << std::endl;
	}
	std::cout	<< "past capacity(): element at(12) is ";
	try {
	std::cout	<< c.at(12) << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "error thrown: " << e.what() << std::endl;
	}

	std::cout	<< "//// ASSIGN(NB, T) ////" << std::endl;
	
	std::cout	<< "c.assign(6, hi)..." << std::endl;

	c.assign(6, "hi");
	print_info(c, "C");
	print_content(c, "C");

	std::cout	<< "c.assign(9, ha)..." << std::endl;

	c.assign(9, "ha");
	print_info(c, "C");
	print_content(c, "C");

	std::cout	<< "c.assign(0, he)..." << std::endl;

	c.assign(0, "he");
	print_info(c, "C");
	print_content(c, "C");

	std::cout	<< "c.assign(13, ho)..." << std::endl;

	c.assign(13, "ho");
	print_info(c, "C");
	print_content(c, "C");

	//std::cout 	<< "//// ITERATOR TRAITS //// " << std::endl 
	//typedef std::iterator_traits<int*> traits;
	  
	//if (typeid(traits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
		    //std::cout << "int* is a random-access iterator";

	NAMESPACE::vector<std::string>::iterator vbegin	= c.begin();
	NAMESPACE::vector<std::string>::iterator vend	= c.end();
	std::cout 	<< "//// ITERATORS //// " << std::endl 
			<< "c.begin is " << *vbegin << std::endl;
	//std::cout << "c.end is " << *vend << std::endl; // will segf

	std::cout 	<< "iterating through vector... " << std::endl 
			<< "[ ";
	for (	NAMESPACE::vector<std::string>::iterator it = vbegin;
		it != vend;
		it++		) {
		std::cout << *it << " "; 
	}
	std::cout	<< "]" << std::endl << std::endl;
	
	NAMESPACE::vector<std::string>::const_iterator cvbegin	= c.begin();
	NAMESPACE::vector<std::string>::const_iterator cvend	= c.end();
	std::cout 	<< "const iterators... " << std::endl 
			<< "c.begin is " << *cvbegin << std::endl;
	//std::cout << "c.end is " << *vend << std::endl; // will segf

	std::cout 	<< "iterating through vector..." << std::endl 
			<< "[ ";
	for (	NAMESPACE::vector<std::string>::const_iterator it = cvbegin;
		it != cvend;
		it++		) {
		std::cout << *it << " "; 
	}
	std::cout	<< "]" << std::endl << std::endl;

	std::cout	<< "//// ASSIGN(IT, IT) ////" << std::endl;
	
	NAMESPACE::vector<std::string>		e(20, "HE");
//	NAMESPACE::vector<IncrediblyComplex<IncrediblyComplex<float> > >	f(42);
//	NAMESPACE::vector<IncrediblyComplex<std::string> >			g(6);

	print_content(c, "C");
	print_info(c, "C");
	
	c.push_back("he");
	
	print_content(c, "C");
	print_info(c, "C");

	c.push_back("ha");
	
	print_content(e, "E");
	print_info(e, "E");
	print_content(c, "C");
	print_info(c, "C");

	NAMESPACE::vector<std::string>::iterator				ite;
	NAMESPACE::vector<IncrediblyComplex<std::string> >::iterator		itg;

	std::cout	<< "assign to c.end() - 1 =" << *(c.end() - 1) << std::endl;
	e.assign(c.begin() + 10, c.end() - 1);
	print_content(e, "E");
	print_info(e, "E");
	
	//std::cout	<< "assign to c.end() =" << *(c.end()) << std::endl;
	// is undefined? protect against segf?
	std::cout	<< "assign to c.end()" << std::endl;
	e.assign(c.begin() + 10, c.end());
	print_content(e, "E");
	print_info(e, "E");

	std::cout	<< "assign to c.end() + 1" << std::endl;
	e.assign(c.begin() + 10, c.end() + 1);
	print_content(e, "E");
	print_info(e, "E");
	
	std::cout	<< "assign from c.begin() - 1" << std::endl;
	e.assign(c.begin() - 1, c.end() - 10);
	print_content(e, "E");
	print_info(e, "E");

	c.resize(25, "hi");
	print_content(c, "C");
	print_info(c, "C");
	print_content(e, "E");
	print_info(e, "E");
	
	std::cout	<< "//// SWAP ////" << std::endl;

	e.swap(c);
	print_content(c, "C"); // capacity differs 
	print_info(c, "C");
	
	std::cout	<< "clearing src..." << std::endl;
	c.clear();	
	
	print_content(e, "E");
	print_info(e, "E");

	std::cout	<< "swap overload!" << std::endl;

	swap(c, e);

	print_content(c, "C");
	print_info(c, "C");
	print_content(e, "E"); // capacity differs
	print_info(e, "E");
	
	//std::cout	<< "//// CLEAR ////" << std::endl;

	//print_info(a, "A");
	//a.clear();
	//print_info(a, "A");

	std::cout	<< "//// INSERT ////" << std::endl << std::endl;

	NAMESPACE::vector<std::string>::iterator				pos;
	//pos = e.insert(e.begin(), "he");	// empty array, segf
						// it on wrong vector
	//c.reserve(30);
	//pos = c.insert(e.end(), "HE");	// past size, segf
	//pos = c.insert(e.capacity() + 1, "HE"); 
						// past cap, compile not
	pos = c.insert(c.begin() + 6, "HO");

	std::cout	<< "new element is " << *pos << std::endl;

	print_content(c, "C");
	print_info(c, "C");
	
	std::cout	<< "//// ERASE ////" << std::endl << std::endl;
	
	pos = c.erase(c.begin() + 6);

	std::cout	<< "new element is " << *pos << std::endl;

	print_content(c, "C");
	print_info(c, "C");
	
	pos = c.erase(c.begin());

	std::cout	<< "new element is " << *pos << std::endl;

	print_content(c, "C");
	print_info(c, "C");

	pos = c.erase(c.end());

	std::cout	<< "new element is " << *pos << std::endl;

	print_content(c, "C");
	print_info(c, "C");
	
	//std::cout	<< "clearing c" << std::endl;
	//c.clear();

	//pos = c.erase(c.begin());	// will segf

	//std::cout	<< "new element is " << *pos << std::endl;

	std::cout	<< "//// INSERT MULTIPLE VALUES ////" << std::endl;

	c.insert(c.begin() + 4, 6, "HO");

	print_content(c, "C"); // diff capacity
	print_info(c, "C");
	
	c.insert(c.begin() + 4, 6, "HA");

	print_content(c, "C"); // diff capacity
	print_info(c, "C");
	
	c.insert(c.begin() + 4, 10, "HA");

	print_content(c, "C"); // diff capacity
	print_info(c, "C");
	
	e.assign(20, "HE");
	
	print_content(e, "E");
	print_info(e, "E");

	e.insert(e.begin() + 5, c.end() - 10, c.end() - 5);

	print_content(e, "E");
	print_info(e, "E");

	// test with int enable if 
	// test with non broken complex classes

	//std::cout	<< "//// CAPACITY ////" << std::endl;
	
	//test_capacity(a, "A");
	//test_capacity(c, "C");
	//test_capacity(d, "D");
	
	{
		std::cout	<< "//// ACCESS ////" << std::endl;
		 
		NAMESPACE::vector<int> myvector;

		myvector.push_back(10);

		while (myvector.back() != 0)
			myvector.push_back(myvector.back() - 1);

		std::cout	<< std::endl
					<< "myvector contains:";
		for (unsigned i = 0; i < myvector.size() ; i++)
			std::cout << ' ' << myvector[i];
		
		std::cout	<< std::endl << std::endl;;
	}/*
	{
		std::cout	<< "//// ERASE ////" << std::endl;
		
		NAMESPACE::vector<int> myvector;
		
		// set some values (from 1 to 10)
		for (int i = 1; i <= 10; i++)
			myvector.push_back(i);		// invalid read

		// erase the 6th element
		myvector.erase (myvector.begin()+5);

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}*/
	return 0;
}
