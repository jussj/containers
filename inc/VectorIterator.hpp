/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:12 by jusaint-          #+#    #+#             */
/*   Updated: 2022/07/06 12:11:01 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include "iterator/iterator_traits.hpp"
# include <iterator>

# define TAG_NS	ft

namespace ft {

	template<class T>
	class VectorIterator {
	
		public:
			
		// TYPES
			
			typedef T						value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*						pointer;
			typedef T&						reference;
			typedef typename TAG_NS::random_access_iterator_tag	iterator_category;

		// CTOR, CPY, DTOR

			VectorIterator() : _ptr(NULL) {}
			//VectorIterator(Iterator& it) : _ptr(it) {}
			VectorIterator(T* it) : _ptr(it) {}
			~VectorIterator() {}

		// OPERATORS
	
			//reference	operator*() {
			//	return *(this->_ptr);
			//}
			
			reference	operator*() const {
				return *(this->_ptr);
			}

			// COMPARAISON
			bool	operator==(const VectorIterator& src) const {
				return _ptr == src._ptr;
			}
			bool	operator!=(const VectorIterator& src) const {
				return _ptr != src._ptr;
			}
			bool	operator<(const VectorIterator& src) const {
				return _ptr < src._ptr;
			}
			bool	operator>(const VectorIterator& src) const {
				return _ptr > src._ptr;
			}
			bool	operator>=(const VectorIterator& src) const {
				return _ptr >= src._ptr;
			}
			bool	operator<=(const VectorIterator& src) const {
				return _ptr <= src._ptr;
			}
			
			// ARITHMETIC

			// PREFIX/POSTFIX INCREMENT/DECREMENT
			VectorIterator&	operator++(void) {
				_ptr++;
				return *this;
			}
			VectorIterator&	operator--(void) {
				_ptr--;
				return *this;
			}
			VectorIterator	operator++(int) {
				VectorIterator	tmp = *this;
				
				++_ptr;
				return tmp;
			}
			VectorIterator	operator--(int) {
				VectorIterator	tmp = *this;

				--_ptr;
				return tmp;
			}
		
		private:

			pointer		_ptr;
		
	};

}

#endif 	/* VECTORITERATOR_HPP */
