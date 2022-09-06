/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:27:14 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/06 10:39:45 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
# define EQUAL_HPP

# include "../utils.hpp"

// returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), 
// and false otherwise.

namespace ft {

	template<class InputIt1, class InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
	
	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal(	InputIt1 first1, 
					InputIt1 last1,	
					InputIt2 first2,
					BinaryPredicate p );
	
	template <class InputIt1, class InputIt2>
	bool lexicographical_compare (	InputIt1 first1, 
									InputIt1 last1,
									InputIt2 first2, 
									InputIt2 last2	) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
	return (first2 != last2);
	}
}	/* namespace ft */

#endif	/* EQUAL_HPP */
