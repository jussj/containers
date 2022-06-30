/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:12 by jusaint-          #+#    #+#             */
/*   Updated: 2022/06/30 11:46:00 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>
# include "iterator/iterator_traits.hpp"
# include <iterator>

# define TAG_NS	std

namespace ft {

	template<class Iterator, class Container>
	class vectorIterator {
	
		public:
			
		// TYPES
			
			typedef typename T					value_type;
			typedef typename ptrdiff_t				difference_type;
			typedef typename T*					pointer;
			typedef typename T&					reference;
			typedef typename TAG_NS::random_access_iterator_tag	iterator_category;

		// CTOR, CPY, DTOR

			vectorIterator() : _it(NULL) {}
			~vectorIterator() {}

		// OPERATORS
		
			// COMPARAISON
			bool	operator==(const vectorIterator& src) {
				return _it == src._it;
			}
			bool	operator!=(const vectorIterator& src) {
				return _it != src._it;
			}
			bool	operator<(const vectorIterator& src) {
				return _it < src._it;
			}
			bool	operator>(const vectorIterator& src) {
				return _it > src._it;
			}

		private:

			iterator	_it;
	};

}

#endif 	/* VECTOR_ITERATOR_HPP */
