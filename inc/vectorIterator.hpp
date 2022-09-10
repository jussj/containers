/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:12 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/10 17:46:15 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include "iterator/iterator_traits.hpp"
# include <iterator>

namespace ft {

	template<class T>
	class VectorIterator {
	
		public:
			
		// TYPES
			
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef T*						pointer;
			typedef T&						reference;
			typedef typename ft::random_access_iterator_tag	iterator_category;

		// CTOR, CPY, DTOR

			VectorIterator() 			: _ptr(NULL) 	{}
			VectorIterator(pointer it) 	: _ptr(it) 		{}
			template<class It>
			VectorIterator(VectorIterator<It> it)		: _ptr(it.current()) {}
			~VectorIterator() {}

		// OPERATORS

			//operator=

			// FORWARD
			reference	operator*() const {
				return *(current());
			}
			VectorIterator&	operator++() {
				++_ptr;
				return *this;
			}
			VectorIterator	operator++(int) {
				VectorIterator tmp = *this;
				
				++_ptr;
				return tmp;
			}
			pointer		operator->() const {
				return current();
			}

			// BIDIRECTIONAL
			VectorIterator&	operator--(void) {
				--_ptr;
				return *this;
			}
			VectorIterator	operator--(int) {
				VectorIterator	tmp = *this;

				--_ptr;
				return tmp;
			}

			// RANDOM ACCESS
			VectorIterator	operator+(difference_type n) const {
				return current() + n;
			}
			VectorIterator	operator-(difference_type n) const {
				return current() - n;
			}
			difference_type operator-(const VectorIterator<T>& x) {
				return this->current() - x.current();
			}
			VectorIterator&	operator+=(int n) {
				this->_ptr += n;
				return *this;
			}
			VectorIterator&	operator-=(int n) {
				this->_ptr -= n;
				return *this;
			}
			reference	operator[](difference_type n) {
				return this->_ptr[n];
			}

		// NON-MEMBER OPERATORS FRIENDSHIP DECLARATIONS

			template<class V, class W>
			friend bool	operator==(const VectorIterator<V> & lhs, const VectorIterator<W> & rhs);
			template<class V, class W>
			friend bool	operator!=(const VectorIterator<V> & lhs, const VectorIterator<W> & rhs);
			template<class V, class W>
			friend bool	operator<(const VectorIterator<V> & lhs, const VectorIterator<W> & rhs);
			template<class V, class W>
			friend bool	operator>(const VectorIterator<V> & lhs, const VectorIterator<W> & rhs);
			template<class V, class W>
			friend bool	operator>=(const VectorIterator<V> & lhs, const VectorIterator<W> & rhs);
			template<class V, class W>
			friend bool	operator<=(const VectorIterator<V> & lhs, const VectorIterator<W> & rhs);
	
		private:

		// ATTRIBUTE

			pointer		_ptr;
	
		public:
		// private must be	
		// ACCESS

			pointer		current() const {
				return this->_ptr;
			}
			
	};	/* class vectorIterator */

	// NON-MEMBER OPERATORS

	template<class T>
	VectorIterator<T>	operator+(	typename VectorIterator<T>::difference_type n,
									VectorIterator<T> it) {
		return it.operator+(n);
	}
	template<class T>
	VectorIterator<T>	operator-(	typename VectorIterator<T>::difference_type n,
									VectorIterator<T> it) {
		return it.operator-(n);
	}
	template<class T>
	typename VectorIterator<T>::difference_type
	operator-(const VectorIterator<T>& x, const VectorIterator<T>& y) {
		return x.current() - y.current();
	}

	template<class T, class U>
	bool	operator==(const VectorIterator<T> & lhs, const VectorIterator<U> & rhs) {
		return lhs._ptr == rhs._ptr;
	}

	template<class T, class U>
	bool	operator!=(const VectorIterator<T> & lhs, const VectorIterator<U> & rhs) {
		return lhs._ptr != rhs._ptr;
	}

	template<class T, class U>
	bool	operator<(const VectorIterator<T> & lhs, const VectorIterator<U> & rhs) {
		return lhs._ptr < rhs._ptr;
	}

	template<class T, class U>
	bool	operator>(const VectorIterator<T> & lhs, const VectorIterator<U> & rhs) {
		return lhs._ptr > rhs._ptr;
	}

	template<class T, class U>
	bool	operator>=(const VectorIterator<T> & lhs, const VectorIterator<U> & rhs) {
		return lhs._ptr >= rhs._ptr;
	}

	template<class T, class U>
	bool	operator<=(const VectorIterator<T> & lhs, const VectorIterator<U> & rhs) {
		return lhs._ptr <= rhs._ptr;
	}
		
}	/* namespace ft */



#endif 	/* VECTORITERATOR_HPP */
