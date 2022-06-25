/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:48 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/25 16:56:58 by jusaint-         ###   ########.fr       */
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
	NAMESPACE::vector<int>		b(100, 5);	// 100 ints with value 5
	NAMESPACE::vector<std::string>	c(4, "he");

	if (a.empty())
		std::cout << "A is empty" << std::endl;
	if (!b.empty())
		std::cout << "B is NOT empty" << std::endl;

	return 0;
}
