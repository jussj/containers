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
			
		// TYPES //
			
			typedef T	value_type;
			typedef ptrdiff_t	difference_type;
			typedef T* pointer;
			typedef T& reference;

			typedef typename std::random_access_iterator_tag
				iterator_category;

		// CTOR, CPY, DTOR //

			vector_iterator()
				: _ptr(NULL) {}

			vector_iterator(pointer it)
				: _ptr(it) {}

			template<class U>
			vector_iterator(const vector_iterator<U> it)
				: _ptr(it.current()) {}

			~vector_iterator() {}

		// OPERATORS //

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
			operator-(const vector_iterator<U>& x) const {
				return current() - x.current();
			}
			
			vector_iterator&
			operator+=(difference_type n) {
				_ptr += n;
				return *this;
			}
			
			vector_iterator&
			operator-=(difference_type n) {
				_ptr -= n;
				return *this;
			}

			reference
			operator[](difference_type n) const {
				return _ptr[n];
			}

			// COMPARISON

			template<class R>
			bool
			operator==(const vector_iterator<R> & rhs) {
				return current() == rhs.current();
			}

			template<class R>
			bool
			operator!=(const vector_iterator<R> & rhs) {
				return current() != rhs.current();
			}

			template<class R>
			bool
			operator<(const vector_iterator<R> & rhs) {
				return current() < rhs.current();
			}

			template<class R>
			bool
			operator>(const vector_iterator<R> & rhs) {
				return current() > rhs.current();
			}

			template<class R>
			bool
			operator>=(const vector_iterator<R> & rhs) {
				return current() >= rhs.current();
			}

			template<class R>
			bool
			operator<=(const vector_iterator<R> & rhs) {
				return current() <= rhs.current();
			}


		// ATTRIBUTE //
	
		private: 

			pointer	_ptr;
	
		// ACCESS //

		public:

			pointer
			current() const {
				return _ptr;
			}
			
	};	/* class vector_iterator */

	// NON-MEMBER OPERATORS //

	template<class T>
	vector_iterator<T>
	operator+(
			typename vector_iterator<T>::difference_type n,
			vector_iterator<T> it) {
		return it.operator+(n);
	}
	
	template<class L, class R>
	bool
	operator==(
			const vector_iterator<L> & lhs, 
			const vector_iterator<R> & rhs) {
		return lhs.current() == rhs.current();
	}

	template<class L, class R>
	bool
	operator!=(
			const vector_iterator<L> & lhs,
			const vector_iterator<R> & rhs) {
		return lhs.current() != rhs.current();
	}

	template<class L, class R>
	bool
	operator<(
			const vector_iterator<L> & lhs,
			const vector_iterator<R> & rhs) {
		return lhs.current() < rhs.current();
	}

	template<class L, class R>
	bool
	operator>(
			const vector_iterator<L> & lhs,
			const vector_iterator<R> & rhs) {
		return lhs.current() > rhs.current();
	}

	template<class L, class R>
	bool
	operator>=(
			const vector_iterator<L> & lhs,
			const vector_iterator<R> & rhs) {
		return lhs.current() >= rhs.current();
	}

	template<class L, class R>
	bool
	operator<=(
			const vector_iterator<L> & lhs,
			const vector_iterator<R> & rhs) {
		return lhs.current() <= rhs.current();
	}
		
}	/* namespace ft */

#endif 	/* vector_iterator_HPP */
