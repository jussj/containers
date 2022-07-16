#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
		template <class Iterator>
		class reverse_iterator : public iterator
				<	typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference	> {
				
				public:

				// TYPES

					typedef Iterator											iterator_type;
					typedef typename iterator_traits<Iterator>::difference_type	difference_type;
					typedef typename iterator_traits<Iterator>::reference		reference;
					typedef typename iterator_traits<Iterator>::pointer			pointer;
				
				// CTOR/DTOR

					reverse_iterator();
					explicit reverse_iterator(Iterator it) : _base(it), current(it) {}
					template <class It>
					reverse_iterator(const reverse_iterator<It>& u);
				
					Iterator 	base() const {	// explicit
						return this->_base;
					}
					
					reference 			operator*() const;
					pointer 			operator->() const;
					reverse_iterator& 	operator++();
					reverse_iterator 	operator++(int);
					reverse_iterator& 	operator--();
					reverse_iterator 	operator--(int);
					reverse_iterator 	operator+ (difference_type n) const;
					reverse_iterator& 	operator+=(difference_type n);
					reverse_iterator 	operator- (difference_type n) const;
					reverse_iterator& 	operator-=(difference_type n);
					reference 			operator[](difference_type n) const;
				
				protected:

					Iterator 	current;

				private:

					Iterator	_base;
				
		};
		
		template <class Iterator>
		bool 	operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
		
		template <class Iterator>
		bool 	operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
		
		template <class Iterator>
		bool 	operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
		
		template <class Iterator>
		bool 	operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		
		template <class Iterator>
		bool 	operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
		
		template <class Iterator>
		bool 	operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
		
		template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
		
		template <class Iterator>
		reverse_iterator<Iterator>
		operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x);
}

#endif
