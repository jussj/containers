/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:01:37 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/28 10:21:15 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

template<class T>
class	IncrediblyComplex {
	public:
		IncrediblyComplex() : nb(42), ptr(new T) {}
		IncrediblyComplex(int n, T type) : nb(n), ptr(new T) {
			*ptr = type;
		}
		IncrediblyComplex(IncrediblyComplex const &src)
			: nb(src.nb), ptr(new T) {
			*ptr = *src.ptr;
		}
		~IncrediblyComplex() {
			delete ptr;
		}
	private:
		int	nb;
		T	*ptr;
}

#endif 	/* TEST_HPP */
