/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:40:46 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/14 16:03:43 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMESPACE
# define NAMESPACE std
#endif 

#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include <iostream>
#include <iterator>     // std::iterator_traits
#include <typeinfo>     // typeid

int	main() {
  	typedef std::iterator_traits<int*> traits;
  	
	if (typeid(traits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
    		std::cout << "int* is a random-access iterator";
  	return 0;
}
