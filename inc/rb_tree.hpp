#ifndef	RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>				// allocator
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "utility.hpp"

# define RED		0			// nodes color
# define BLACK		1
# define D_BLACK	2

template<class T>
struct rb_tree_node {

	typedef	rb_tree_node*		ptr;
	typedef const rb_tree_node*	const_ptr;
	typedef T					value_type;

	// ATTRIBUTES

	int			color;
	ptr			parent;
	ptr			left;
	ptr			right;

	// MEMBER FUNCTIONS

	static ptr
	minimum(ptr x) {
		while (x->left != 0)
			x = x->left;
		return x;	
	}		
	static const_ptr
	minimum(const_ptr x) {
		while (x->left != 0)
			x = x->left;
		return x;	
	}		
	static ptr
	maximum(ptr x) {
		while (x->right != 0)
			x = x->right;
		return x;	
	}		
	static const_ptr
	maximum(const_ptr x) {
		while (x->right != 0)
			x = x->right;
		return x;	
	}		
};	/* rb_tree_node struct */

struct rb_tree_header {

	// ATTRIBUTES

	rb_tree_node	header;
	size_t			node_count;

	rb_tree_header();				// color + reset init
	move_data(rb_tree_header& src); // cpy from src and reset src
									// also, _M_header._M_parent->_M_parent = &_M_header;
	reset() {						// reset all but color
		header.parent	= 0;
		header.left		= &header;
		header.right	= &header;
		node_count		= 0;
	}

}	/* rb_tree_header struct */

// helper to init elements to compare with COMPARE?

template<class Key, class Val, class ValueKey, 
		 class Compare, class Alloc = std::allocator<T> >
class rb_tree {
	
	// TYPES
	
	typedef
};

#endif
