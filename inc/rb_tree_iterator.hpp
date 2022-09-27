#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

# include "rb_tree.hpp"

template<class T>
class rb_tree_iterator {
	
	public:

	// TYPES

		typedef T						value_type;
		typedef ptrdiff_t				difference_type;
		typedef T*						pointer;
		typedef T&						reference;
		typedef typename ft::bidirectional_iterator_tag	iterator_category;

	// CTOR
	
		rb_tree_iterator()	: 
};	

#endif
