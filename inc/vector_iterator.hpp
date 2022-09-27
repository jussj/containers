#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include <cstddef>		// ptrdiff_t
# include <memory>		// allocator
# include <iterator>
# include "iterator.hpp"

namespace ft {

	template<class T>
	class vectorIterator {
	
		public:
			
		// TYPES
			
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef T*						pointer;
			typedef T&						reference;
			typedef typename ft::random_access_iterator_tag	iterator_category;

		// CTOR, CPY, DTOR

			vectorIterator() 			: _ptr(NULL) 	{}
			vectorIterator(pointer it) 	: _ptr(it) 		{}
			template<class U>
			vectorIterator(vectorIterator<U> it)		: _ptr(it.current()) {}
			~vectorIterator() {}

		// OPERATORS

			//operator=

			// FORWARD
			reference	operator*() const {
				return *(current());
			}
			vectorIterator&	operator++() {
				++_ptr;
				return *this;
			}
			vectorIterator	operator++(int) {
				vectorIterator tmp = *this;
				
				++_ptr;
				return tmp;
			}
			pointer		operator->() const {
				return current();
			}

			// BIDIRECTIONAL
			vectorIterator&	operator--(void) {
				--_ptr;
				return *this;
			}
			vectorIterator	operator--(int) {
				vectorIterator	tmp = *this;

				--_ptr;
				return tmp;
			}

			// RANDOM ACCESS
			vectorIterator	operator+(difference_type n) const {
				return current() + n;
			}
			vectorIterator	operator-(difference_type n) const {
				return current() - n;
			}
			template<class U>
			difference_type operator-(const vectorIterator<U>& x) {
				return this->current() - x.current();
			}
			vectorIterator&	operator+=(int n) {
				this->_ptr += n;
				return *this;
			}
			vectorIterator&	operator-=(int n) {
				this->_ptr -= n;
				return *this;
			}
			reference	operator[](difference_type n) {
				return this->_ptr[n];
			}

		// NON-MEMBER OPERATORS FRIENDSHIP DECLARATIONS

			template<class L, class R>
			friend bool
			operator==(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator!=(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator<(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator>(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator>=(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs);
			template<class L, class R>
			friend bool
			operator<=(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs);
	
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
	vectorIterator<T>	operator+(	typename vectorIterator<T>::difference_type n,
									vectorIterator<T> it) {
		return it.operator+(n);
	}
	template<class T>
	vectorIterator<T>	operator-(	typename vectorIterator<T>::difference_type n,
									vectorIterator<T> it) {
		return it.operator-(n);
	}
	template<class T>
	typename vectorIterator<T>::difference_type
	operator-(const vectorIterator<T>& x, const vectorIterator<T>& y) {
		return x.current() - y.current();
	}

	template<class L, class R>
	bool	operator==(	const vectorIterator<L> & lhs, 
						const vectorIterator<R> & rhs) {
		return lhs._ptr == rhs._ptr;
	}

	template<class L, class R>
	bool	operator!=(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs) {
		return lhs._ptr != rhs._ptr;
	}

	template<class L, class R>
	bool	operator<(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs) {
		return lhs._ptr < rhs._ptr;
	}

	template<class L, class R>
	bool	operator>(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs) {
		return lhs._ptr > rhs._ptr;
	}

	template<class L, class R>
	bool	operator>=(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs) {
		return lhs._ptr >= rhs._ptr;
	}

	template<class L, class R>
	bool	operator<=(	const vectorIterator<L> & lhs,
						const vectorIterator<R> & rhs) {
		return lhs._ptr <= rhs._ptr;
	}
		
}	/* namespace ft */

#endif 	/* VECTORITERATOR_HPP */
