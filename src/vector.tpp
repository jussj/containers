/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:07:18 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/24 19:07:28 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/vector.hpp"

// ACCESS

reference 	vector::operator[](size_type n) {
	return _array[n];
}

const_reference vector::operator[](size_type n) const {
	return _array[n];
}

const_reference vector::at(size_type n) const;
reference 	vector::at(size_type n);
reference 	vector::front() {
	return _array[0];
}

const_reference vector::front() const {
	return _array[0];
}

reference 	vector::back() {
	return _array[_n - 1];
}

const_reference vector::back() const {
	return _array[_n - 1];
}
