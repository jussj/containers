#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

// reverse_iterator not compatible with map iterators?? how to make it compatible

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
					reverse_iterator(const reverse_iterator<It>& rit) {
						this->_current = rit._current;
					}
					// class that accept const and non-const it in ctor?
				
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
						return &(*this->_current);
						// is that clean?
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
						return reverse_iterator(base() + n);
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
				
				private:

					It	_current;							// why is implemented as protected?
		
		};	/* reverse_iterator class */

		template <class It>
		bool 	operator==(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x.base() == y.base();
			// compare base directly instead of entire class?
		}
		template <class It>
		bool 	operator<(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x < y;
		}
		template <class It>
		bool 	operator!=(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x != y;
		}
		template <class It>
		bool 	operator>(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x > y;
		}
		template <class It>
		bool 	operator>=(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x >= y;
		}
		template <class It>
		bool 	operator<=(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x <= y;
		}
		template <class It>
		typename reverse_iterator<It>::difference_type
		operator-(const reverse_iterator<It>& x, const reverse_iterator<It>& y) {
			return x.base() - y.base();
		}
		template <class It>
		reverse_iterator<It>
		operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& x) {
			return x.base() + n;
		}
}	/* namespace ft */

#endif	/* REVERSE_ITERATOR_HPP */
