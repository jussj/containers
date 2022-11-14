#include "type_traits.hpp"

// METHOD #1
// add a param to discriminate integral type and accept only iterators

template <class InputIt>
void
assign(
	InputIt first,
	InputIt last,
	typename ft::enable_if<!ft::is_integral<InputIt>::value >::type* = NULL
	);

// METHOD #2
// c++11: same but default template

template <
	class InputIt,
	class = typename ft::enable_if<!ft::is_integral<InputIt>::value >::type>
void
assign(
	InputIt first,
	InputIt last,
	);

// METHOD #3
// do a dispatch

template <class InputIt>
void
assign(InputIt first, InputIt last) {
	_dispatch_assign(first, last, typename ft::is_integral<InputIt>::type());	// false type	
}

void
assign(size_type n, const value_type& value) {
	_dispatch_assign(n, value, typename ft::is_integral<size_type>::type());	// true type	
}

template <class InputIt>
void
_dispatch_assign(InputIt first, InputIt last, ft::false_type);

void
_dispatch_assign(size_type n, const value_type& value, ft::true_type);

// METHOD #4
// use a static???
