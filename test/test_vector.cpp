/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:48 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/04 17:24:57 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMESPACE
# define NAMESPACE ft

#endif

#include <vector>
#include "../inc/vector.hpp"
#include <iostream>
#include "Test.hpp"

int 	main() {
	NAMESPACE::vector<int>		a;
//	NAMESPACE::vector<int>		b(100, 5);	// enable_if and 
							// is_integral, 
							// will use range ctor
	NAMESPACE::vector<std::string>	c(4, "he");
	NAMESPACE::vector<IncrediblyComplex<int> >	d(5);

	print_info<NAMESPACE::vector<int> >(a, "A");
	print_info(c, "C");
	//print_info(d, "D");

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
	a.reserve(7);
	std::cout	<< "size of A is " << a.size()
			<< ", actual capacity is " << a.capacity()
			<< std::endl;

	std::cout	<< "a.push_back() * 3..." << std::endl;
	a.push_back(42);
	a.push_back(789);
	a.push_back(321321);

	print_vector(a, "A");

	//d.push_back(1);
	d.pop_back();
	//print_vector(d, "D");

	std::cout 	<< "c.reserve(4)..." << std::endl;
	c.reserve(4);

	print_info(c, "C");

	std::cout 	<< "c.reserve(9)..." << std::endl;
	c.reserve(9);
	
	print_info(c, "C");

	std::cout	<< "c.pop_back()..." << std::endl;
	c.pop_back();
	
	print_info(c, "C");
	print_vector(c, "C");
	
	std::cout << std::endl;
	std::cout	<< "c.push_back(ha)..." << std::endl;
	c.push_back("ha");
	
	print_info(c, "C");
	print_vector(c, "C");

	std::cout 	<< "c.resize(10, hi).." << std::endl;
	c.resize(10, "hi");
	
	print_info(c, "C");
	print_vector(c, "C");


	std::cout 	<< "c.resize(3).." << std::endl;
	c.resize(3);
	
	print_info(c, "C");
	print_vector(c, "C");

	std::cout	<< "accessing element thru at()..." << std::endl;

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

	std::cout 	<< "c.resize(6, ha).." << std::endl;
	c.resize(6, "ha");

	print_info(c, "C");	
	print_vector(c, "C");

	std::cout 	<< "c.resize(12) with NULL value..." << std::endl;
	c.resize(12);

	print_info(c, "C");

	std::cout	<< "c.assign(6, hi)..." << std::endl;

	c.assign(6, "hi");
	print_info(c, "C");
	print_vector(c, "C");

	std::cout	<< "c.assign(9, ha)..." << std::endl;

	c.assign(9, "ha");
	print_info(c, "C");
	print_vector(c, "C");

	std::cout	<< "c.assign(0, he)..." << std::endl;

	c.assign(0, "he");
	print_info(c, "C");
	print_vector(c, "C");

	std::cout	<< "c.assign(13, ho)..." << std::endl;

	c.assign(13, "ho");
	print_info(c, "C");
	print_vector(c, "C");
//	std::cout 	<< "iterators... " << std::endl 
//			<< "c.begin is " << c.begin() 
//			<< " and c.end is " << c.end() << std::endl;

	test_capacity(c, "C");
	test_capacity(d, "D");

	return 0;
}
