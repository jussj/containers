/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:12 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/06 13:33:24 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

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
			typedef ptrdiff_t				difference_type;
			typedef T*						pointer;
			typedef T&						reference;
			typedef typename TAG_NS::random_access_iterator_tag	iterator_category;

		// CTOR, CPY, DTOR

			VectorIterator() 			: _ptr(NULL) 	{}
			VectorIterator(pointer it) 	: _ptr(it) 		{}
			template<class I>
			VectorIterator(VectorIterator<I> it)		: _ptr(it.current()) {}
			//VectorIterator(const VectorIterator<I> it) 	: _ptr(it.current()) {}
			~VectorIterator() {}

		// ACCESS
		
			pointer		current() const {
				return this->_ptr;
			}

		// OPERATORS

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
			//pointer		operator+(difference_type n) const {
				return current() + n;
			}
			VectorIterator	operator-(difference_type n) const {
			//pointer		operator-(difference_type n) const {
				return current() - n;
			}
			VectorIterator&	operator+=(int n) {
			//VectorIterator&	operator+=(difference_type n) {
				this->_ptr += n;
				return *this;
			}
			VectorIterator&	operator-=(int n) {
			//VectorIterator&	operator-=(difference_type n) {
				this->_ptr -= n;
				return *this;
			}
			reference	operator[](difference_type n) {
				return this->_ptr[n];
			}

			// COMPARISON
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
		
		private:

			pointer		_ptr;
		
	};
}

#endif 	/* VECTORITERATOR_HPP */
