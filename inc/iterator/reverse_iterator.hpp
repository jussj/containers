/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:40:45 by jusaint-          #+#    #+#             */
/*   Updated: 2022/09/11 19:40:59 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
		template <class It>
		class reverse_iterator {
				
				public:

				// TYPES

					typedef It												iterator_type;
					typedef typename iterator_traits<It>::difference_type	difference_type;
					typedef typename iterator_traits<It>::reference			reference;
					typedef typename iterator_traits<It>::pointer			pointer;
				
				// CTOR/DTOR

					reverse_iterator() {}
					explicit reverse_iterator(It it) : _current(it) {}
					template<class I>
					reverse_iterator(const reverse_iterator<I>& rit) {
						this->_current = rit.base();
					}
			
				// ACCESS

					It	base() const {	// explicit
						return this->_current;
					}

				// OPERATORS

					reference 			operator*() const {
						It	tmp = this->_current;
						--tmp;

						return *tmp;
					}
					pointer 			operator->() const {
						return &(operator*());
					}
					reverse_iterator& 	operator++() {
						--this->_current;
						return *this;
					}
					reverse_iterator 	operator++(int) {
						reverse_iterator	tmp = *this;
						
						--this->_current;
						return tmp;
					}
					reverse_iterator& 	operator--() {
						++this->_current;
						return *this;
					}
					reverse_iterator 	operator--(int) {
						reverse_iterator	tmp = *this;
						
						++this->_current;
						return tmp;
					}
					reverse_iterator 	operator+(difference_type n) const {
						return reverse_iterator(base() - n);
					}
					reverse_iterator& 	operator+=(difference_type n) {
						this->_current -= n;
						return *this;
					}
					reverse_iterator 	operator-(difference_type n) const {
						return reverse_iterator(base() + n);
					}
					reverse_iterator& 	operator-=(difference_type n) {
						this->_current += n;
						return *this;
					}
					reference 			operator[](difference_type n) const {
						return *(this->_current - n - 1);
					}
					template< class U >
					reverse_iterator&	operator=(const reverse_iterator<U>& src) {
						this->_current = src.base();
						return *this;
					}
			
				// NON-MEMBER OPERATORS FRIEND DECLARATION
			
					template <class I, class J>
					friend bool	operator==(const reverse_iterator<I>& x, const reverse_iterator<J>& y);
					template <class I, class J>
					friend bool	operator<(const reverse_iterator<I>& x, const reverse_iterator<J>& y);
					template <class I, class J>
					friend bool	operator!=(const reverse_iterator<I>& x, const reverse_iterator<J>& y);
					template <class I, class J>
					friend bool	operator>(const reverse_iterator<I>& x, const reverse_iterator<J>& y);
					template <class I, class J>
					friend bool	operator>=(const reverse_iterator<I>& x, const reverse_iterator<J>& y);
					template <class I, class J>
					friend bool	operator<=(const reverse_iterator<I>& x, const reverse_iterator<J>& y);

				protected:

					It	_current;							// why is implemented as protected?
		
		};	/* reverse_iterator class */

		template <class ItL, class ItR>
		bool 	operator==(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return x.base() == y.base();
		}
		template <class ItL, class ItR>
		bool 	operator<(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return y.base() < x.base();
		}
		template <class ItL, class ItR>
		bool 	operator!=(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return !(x == y);
		}
		template <class ItL, class ItR>
		bool 	operator>(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return y < x;
		}
		template <class ItL, class ItR>
		bool 	operator>=(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return !(x < y);
		}
		template <class ItL, class ItR>
		bool 	operator<=(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return !(y < x);
		}
		template <class ItL, class ItR>
		typename reverse_iterator<ItL>::difference_type
		operator-(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
			return y.base() - x.base();
		}
		template <class It>
		reverse_iterator<It>
		operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& x) {
			return reverse_iterator<It>(x.base() - n);
		}
}	/* namespace ft */

#endif	/* REVERSE_ITERATOR_HPP */
