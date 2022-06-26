/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:48 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/26 14:18:11 by jusaint-         ###   ########.fr       */
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

	std::cout	<< "printing C..." << std::endl;

	for (size_t s = 0; s < c.size(); s++) {
		std::cout << c[s] << " ";
	}
	std::cout	<< std::endl;

	std::cout	<< "C front is " << c.front()
			<< ", back is " << c.back() << std::endl;

	return 0;
}
