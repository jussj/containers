/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:48 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/29 19:58:21 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

#include <vector>
#include <iostream>
#include "../inc/vector.hpp"

//void	print_state();
//void	print_vector();
//void	test_vector();	ft must be a template

int 	main() {
	NAMESPACE::vector<int>		a;
//	NAMESPACE::vector<int>		b(100, 5);	// enable_if and 
							// is_integral, 
							// will use range ctor
	NAMESPACE::vector<std::string>	c(4, "he");

	std::cout	<< "size of A is " << a.size()
			<< ", actual capacity is " << a.capacity()
			<< ", max_size is " << a.max_size() << std::endl
			<< "size of C is " << c.size()
			<< ", actual capacity is " << a.capacity()
			<< ", max_size is " << c.max_size() << std::endl;

	if (a.empty())
		std::cout << "A is empty" << std::endl;
	if (!c.empty())
		std::cout << "C is NOT empty" << std::endl;

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
	std::cout	<< "size of A is " << a.size()
			<< ", actual capacity is " << a.capacity() << std::endl
			<< "A front is " << a.front()
			<< ", back is " << a.back() << std::endl;

	std::cout << "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout << std::endl;
	
	std::cout 	<< "c.reserve(4)..." << std::endl;
	c.reserve(4);
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity()
			<< std::endl;

	std::cout 	<< "c.reserve(9)..." << std::endl;
	c.reserve(9);
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity()
			<< std::endl;

	std::cout	<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	std::cout	<< "c.pop_back()..." << std::endl;
	c.pop_back();
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity() << std::endl
			<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	std::cout << "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	
	std::cout << std::endl;
	std::cout	<< "c.push_back(ha)..." << std::endl;
	c.push_back("ha");
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity() << std::endl
			<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	std::cout 	<< "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout 	<< std::endl;

	std::cout 	<< "c.resize(10, hi).." << std::endl;
	c.resize(10, "hi");
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity() << std::endl
			<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	std::cout 	<< "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout 	<< std::endl;


	std::cout 	<< "c.resize(3).." << std::endl;
	c.resize(3);
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity() << std::endl
			<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	std::cout 	<< "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout 	<< std::endl;

	std::cout	<< "accessing element thru at()..." << std::endl;

	std::cout	<< "in range: element at(0) is "
			<< c.at(0) << std::endl;
	std::cout	<< "past size(): element at(3) is ";
	try {
		std::cout	<< c.at(3) << std::endl;
		//that element exists???? taking off throwing exception
		//no segv
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
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity() << std::endl
			<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	std::cout 	<< "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout 	<< std::endl;

	std::cout 	<< "c.resize(12) with NULL value..." << std::endl;
	c.resize(12);
	std::cout	<< "size of C is " << c.size()
			<< ", actual capacity is " << c.capacity() << std::endl
			<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;
	
	return 0;
}
