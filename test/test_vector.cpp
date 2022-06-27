/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:48 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/27 12:01:31 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

#include <vector>
#include <iostream>
#include "../inc/vector.hpp"

int 	main() {
	NAMESPACE::vector<int>		a;		// empty vector
//	NAMESPACE::vector<int>		b(100, 5);	// 100 ints with value 5
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

	std::cout	<< "a.push_back(42)..." << std::endl;
	a.push_back(42);
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

	std::cout << "printing C..." << std::endl;
	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout << std::endl;

	return 0;
}
