#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>		// ptrdiff_t
# include <iterator>	// iterator tags

namespace ft {

	template<class Iter>
	class iterator_traits {
		public:
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	class iterator_traits<T *> {
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T *								pointer;
			typedef T &								reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};

	template<class T>
	class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef const T *						pointer;
			typedef const T &						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	
	};	/* iterator_traits class */

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

				It
				base() const {
					return _current;
				}

			// OPERATORS

				reference 		
				operator*() const {
					It	tmp = _current;
					--tmp;

					return *tmp;
				}
				pointer 		
				operator->() const {
					return &(operator*());
				}
				reverse_iterator&
				operator++() {
					--_current;
					return *this;
				}
				reverse_iterator
				operator++(int) {
					reverse_iterator	tmp = *this;
					
					--_current;
					return tmp;
				}
				reverse_iterator&
				operator--() {
					++this->_current;
					return *this;
				}
				reverse_iterator
				operator--(int) {
					reverse_iterator	tmp = *this;
					
					++_current;
					return tmp;
				}
				reverse_iterator
				operator+(difference_type n) const {
					return reverse_iterator(base() - n);
				}
				reverse_iterator&
				operator+=(difference_type n) {
					_current -= n;
					return *this;
				}
				reverse_iterator
				operator-(difference_type n) const {
					return reverse_iterator(base() + n);
				}
				reverse_iterator&
				operator-=(difference_type n) {
					_current += n;
					return *this;
				}
				reference 		
				operator[](difference_type n) const {
					return *(_current - n - 1);
				}
				template< class U >
				reverse_iterator&
				operator=(const reverse_iterator<U>& src) {
					_current = src.base();
					return *this;
				}
		
			// NON-MEMBER OPERATORS FRIEND DECLARATION
		
				template <class I, class J>
				friend bool
				operator==(const reverse_iterator<I>& x, const reverse_iterator<J>& y);

				template <class I, class J>
				friend bool
				operator<(const reverse_iterator<I>& x, const reverse_iterator<J>& y);

			protected:

				It	_current;
	
	};	/* reverse_iterator class */

	template <class ItL, class ItR>
	bool
	operator==(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
		return x.base() == y.base();
	}

	template <class ItL, class ItR>
	bool
	operator<(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
		return y.base() < x.base();
	}

	template <class ItL, class ItR>
	bool
	operator!=(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
		return !(x == y);
	}

	template <class ItL, class ItR>
	bool
	operator>(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
		return y < x;
	}

	template <class ItL, class ItR>
	bool
	operator>=(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
		return !(x < y);
	}

	template <class ItL, class ItR>
	bool
	operator<=(const reverse_iterator<ItL>& x, const reverse_iterator<ItR>& y) {
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

#endif	/* ITERATOR_HPP */
