#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include <iterator>
# include "iterator.hpp"

namespace ft {

	template<class T>
	class vector_iterator {
	
		public:
			
		// TYPES
			
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef T*						pointer;
			typedef T&						reference;

			typedef typename ft::random_access_iterator_tag
											iterator_category;

		// CTOR, CPY, DTOR

			vector_iterator()						: _ptr(NULL) {}
			vector_iterator(pointer it)				: _ptr(it) {}
			template<class U>
			vector_iterator(const vector_iterator<U> it)
				: _ptr(&(*it)) {}
			~vector_iterator() {}

		// OPERATORS

			//operator=

			// FORWARD
			reference
			operator*() const {
				return *(current());
			}
			vector_iterator&
			operator++() {
				++_ptr;
				return *this;
			}
			vector_iterator
			operator++(int) {
				vector_iterator tmp = *this;
				
				++_ptr;
				return tmp;
			}
			pointer
			operator->() const {
				return current();
			}

			// BIDIRECTIONAL
			vector_iterator&
			operator--(void) {
				--_ptr;
				return *this;
			}
			vector_iterator
			operator--(int) {
				vector_iterator	tmp = *this;

				--_ptr;
				return tmp;
			}

			// RANDOM ACCESS
			vector_iterator
			operator+(difference_type n) const {
				return current() + n;
			}
			vector_iterator
			operator-(difference_type n) const {
				return current() - n;
			}
			template<class U>
			difference_type
			operator-(const vector_iterator<U>& x) {
				return current() - &(*x);
			}
			vector_iterator&
			operator+=(int n) {
				_ptr += n;
				return *this;
			}
			vector_iterator&
			operator-=(int n) {
				_ptr -= n;
				return *this;
			}
			reference
			operator[](difference_type n) {
				return _ptr[n];
			}

		// NON-MEMBER OPERATORS FRIENDSHIP DECLARATIONS

			template<class L, class R>
			friend bool
			operator==(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator!=(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator<(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator>(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator>=(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator<=(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs);
	
		private:

		// ATTRIBUTE

			pointer		_ptr;
	
		// ACCESS

			pointer		current() const {
				return _ptr;
			}
			
	};	/* class vector_iterator */

	// NON-MEMBER OPERATORS

	template<class T>
	vector_iterator<T>	operator+(	typename vector_iterator<T>::difference_type n,
									vector_iterator<T> it) {
		return it.operator+(n);
	}
	template<class T>
	vector_iterator<T>	operator-(	typename vector_iterator<T>::difference_type n,
									vector_iterator<T> it) {
		return it.operator-(n);
	}
	template<class T>
	typename vector_iterator<T>::difference_type
	operator-(const vector_iterator<T>& x, const vector_iterator<T>& y) {
		return &(*x) - &(*y);
	}

	template<class L, class R>
	bool	operator==(	const vector_iterator<L> & lhs, 
						const vector_iterator<R> & rhs) {
		return lhs._ptr == rhs._ptr;
	}

	template<class L, class R>
	bool	operator!=(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs) {
		return lhs._ptr != rhs._ptr;
	}

	template<class L, class R>
	bool	operator<(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs) {
		return lhs._ptr < rhs._ptr;
	}

	template<class L, class R>
	bool	operator>(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs) {
		return lhs._ptr > rhs._ptr;
	}

	template<class L, class R>
	bool	operator>=(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs) {
		return lhs._ptr >= rhs._ptr;
	}

	template<class L, class R>
	bool	operator<=(	const vector_iterator<L> & lhs,
						const vector_iterator<R> & rhs) {
		return lhs._ptr <= rhs._ptr;
	}
		
}	/* namespace ft */

#endif 	/* vector_iterator_HPP */
