/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:12 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/11 19:32:12 by jusaint-         ###   ########.fr       */
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
			template<class U>
			VectorIterator(VectorIterator<U> it)		: _ptr(it.current()) {}
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
			template<class U>
			difference_type operator-(const VectorIterator<U>& x) {
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

			template<class L, class R>
			friend bool	operator==(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs);
			template<class L, class R>
			friend bool	operator!=(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs);
			template<class L, class R>
			friend bool	operator<(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs);
			template<class L, class R>
			friend bool	operator>(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs);
			template<class L, class R>
			friend bool	operator>=(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs);
			template<class L, class R>
			friend bool	operator<=(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs);
	
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

	template<class L, class R>
	bool	operator==(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs) {
		return lhs._ptr == rhs._ptr;
	}

	template<class L, class R>
	bool	operator!=(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs) {
		return lhs._ptr != rhs._ptr;
	}

	template<class L, class R>
	bool	operator<(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs) {
		return lhs._ptr < rhs._ptr;
	}

	template<class L, class R>
	bool	operator>(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs) {
		return lhs._ptr > rhs._ptr;
	}

	template<class L, class R>
	bool	operator>=(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs) {
		return lhs._ptr >= rhs._ptr;
	}

	template<class L, class R>
	bool	operator<=(const VectorIterator<L> & lhs, const VectorIterator<R> & rhs) {
		return lhs._ptr <= rhs._ptr;
	}
		
}	/* namespace ft */

#endif 	/* VECTORITERATOR_HPP */
