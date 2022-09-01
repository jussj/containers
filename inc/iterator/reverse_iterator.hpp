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

					reverse_iterator();
					explicit reverse_iterator(It it) : _current(it) {}
					reverse_iterator(const reverse_iterator<It>& u);
					reverse_iterator(reverse_iterator<It>& u);			// class that accept const
																		// and non-const it
				
					It	base() const {	// explicit
						return this->_current;
					}

				// OPERATORS

					reference 			operator*() const {
						return *(this->_current);
					}
					pointer 			operator->() const {
						return this->_current;
					}
					reverse_iterator& 	operator++() {
						--this->_current;
						return *this->_current;
					}
					reverse_iterator 	operator++(int) {
						It	tmp = *this->current;
						
						--this->_current;
						return tmp;
					}
					reverse_iterator& 	operator--() {
						++this->_current;
						return *this->_current;
					}
					reverse_iterator 	operator--(int) {
						It	tmp = *this->current;
						
						++this->_current;
						return tmp;
					}
					reverse_iterator 	operator+(difference_type n) const {
						return base() + n;
					}
					reverse_iterator& 	operator+=(difference_type n) {
					}
					reverse_iterator 	operator-(difference_type n) const;
					reverse_iterator& 	operator-=(difference_type n);
					reference 			operator[](difference_type n) const;
				
				private:

					It	_current;							// why is implemented as protected?
				
		};
		
		template <class It>
		bool 	operator==(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		bool 	operator<(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		bool 	operator!=(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		bool 	operator>(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		bool 	operator>=(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		bool 	operator<=(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		typename reverse_iterator<It>::difference_type
		operator-(const reverse_iterator<It>& x, const reverse_iterator<It>& y);
		
		template <class It>
		reverse_iterator<It>
		operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& x);
}

#endif
