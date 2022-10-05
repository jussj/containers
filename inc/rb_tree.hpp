#ifndef	RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>				// allocator
# include <cstddef>				// ptrdiff_t
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "utility.hpp"

namespace ft {

	typedef enum	e_color {
		RED,
		BLACK,
		D_BLACK
	}				t_color;

	struct rb_tree_node_base {

		typedef	rb_tree_node_base*			ptr;
		typedef const rb_tree_node_base*	const_ptr;

		// ATTRIBUTES

		t_color		color;
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

	};	/* rb_tree_node_base struct	*/
		/* holds node base pointers, color and max/min func */

	struct rb_tree_header {

		// ATTRIBUTES

		rb_tree_node_base	header;
		size_t				node_count;

		// CTOR

		rb_tree_header() {
			header.color = RED;
			reset();
		}

		// MEMBER FUNCTIONS

		void
		move_data(rb_tree_header& src) {
			header.color = src.header.color;
			header.parent = src.header.parent;
			header.left = src.header.left;
			header.right = src.header.right;
			header.parent->parent = &header;
			
			src.reset();	
		}
		void
		reset() {
			header.parent	= 0;
			header.left		= &header;
			header.right	= &header;
			node_count		= 0;
		}

	};	/* rb_tree_header struct */
		/* holds node_count and ends */

	template<class V>
	struct rb_tree_node : public rb_tree_node_base {

		typedef rb_tree_node<V>*	ptr;
		typedef V					value_type;

		V							_value;

		ptr
		value() const {
			return this->_value;
		}

	};	/* rb_tree_node struct */
		/* inherites base_node and holds value ptr */

/*	template<typename Compare>
	struct rb_tree_key_compare {

		// ATTRIBUTES

		Compare			key_compare;

		// CTOR

		rb_tree_key_compare()
			: key_compare() {}

		rb_tree_key_compare(const key_compare* comp)
			: key_compare(comp) {}
			
	};	 rb_tree_key_compare struct */


	struct rb_tree_base_iterator {

		typedef rb_tree_node_base::ptr		base_ptr;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;

		base_ptr	node;

		void
		increment() {
			if (node->right != 0) {
				node = node->right;
				while (node->left != 0)
					node = node->left;
			}
			else {
				base_ptr x = node->parent;
				while (node == x->parent) {
					node = x;
					x = x->parent;
				}
				if (node->right != x)
					node = x;
			}
		}

		void
		decrement() {
			if (node->color == RED
					&& node->parent->parent == node)
				node = node->right;
			else if (node->left != 0) {
				base_ptr x = node->left;
				while (x->right != 0)
					x = x->right;
				node = x;
			}
			else {
				base_ptr x = node->parent;
				while (node == x->left) {
					node = x;
					x = x->parent;
				}
				node = x;
			}

		}

	};	/* rb_tree_base_iterator */
		/* base_ptr node and decrem/increm func */

	template<class T>
	struct rb_tree_iterator : public rb_tree_base_iterator {

		// TYPES

		typedef T			value_type;
		typedef T&			reference;
		typedef T*			pointer;

		typedef bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;

		typedef rb_tree_iterator<T>			self;
		typedef rb_tree_node_base::ptr		base_ptr;
		typedef rb_tree_node<T>*			node_ptr;

		// ATTRIBUTES

		node_ptr	node;

		// CTORS
		
		rb_tree_iterator()				: node() {}
		rb_tree_iterator(base_ptr x)	: node(x) {}

		// OVERLOADS

		reference
		operator*() const {
			return *node->_value;
		}

		self&
		operator->() const {
			return *node->_value;
		}

		self
		operator++() {
			increment();
		}

		self
		operator++(int) {
			self tmp = *this;

			increment();
			return tmp;
		}
		self
		operator--() {
			decrement();
		}

		self
		operator--(int) {
			self tmp = *this;

			decrement();
			return tmp;
		}
	
		bool
		operator==(const self& src) {
			return this.node == src.node;
		}

		bool
		operator!=(const self& src) {
			return this.node != src.node;
		}
		
		//bool
		//operator==(const self& x, const self& y) {
			//return x.node == y.node;
		//}

		//bool
		//operator!=(const self& x, const self& y) {
			//return x.node != y.node;
		//}

	};	/* rb_tree_iterator */

	template<class T>
	struct const_rb_tree_iterator : public rb_tree_base_iterator {

		// TYPES

		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;

		typedef bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;
		
		typedef rb_tree_iterator<T>			self;
		typedef rb_tree_node_base::ptr		base_ptr;
		typedef rb_tree_node<T>*			node_ptr;
		
		// ...

	};	/* rb_tree_const_iterator */

	template<class T, class Key, class Val, class ValueKey, 
			 class Compare, class Alloc = std::allocator<T> >
	class rb_tree {

		// TYPES

		public:

			typedef Key 				key_type;
			typedef Val 				value_type;
			typedef value_type* 		pointer;
			typedef const value_type* 	const_pointer;
			typedef value_type& 		reference;
			typedef const value_type& 	const_reference;
			typedef size_t 				size_type;
			typedef ptrdiff_t 			difference_type;
			typedef Alloc 				allocator_type;	
			
		protected:

			typedef rb_tree_node_base::ptr			base_ptr;
			typedef rb_tree_node_base::const_ptr	const_base_ptr;
			typedef	rb_tree_node<Val>*				node_ptr;
			typedef	const rb_tree_node<Val>*		const_node_ptr;
		
		public:

		// MEMBER FUNCTIONS

		// ACCESS

			base_ptr
			begin() {
				return this->_header->parent;
			}
			const_base_ptr
			begin() const {
				return this->_header->parent;
			}
			base_ptr
			end() {
				return this->_header;
			}
			const_base_ptr
			end() const {
				return this->_header;
			}

		// MANIPULATE NODES

		allocator_type
		get_allocator() {
			return this->_alloc;
		}
		node_ptr
		alloc_node() {
			return this->_alloc.allocate(1);
		}
		void
		dealloc_node(node_ptr n) {
			this->_alloc.deallocate(n);
		}
		//void
		//construct_node(node_ptr n) {
			//this->_alloc.construct
		//}


		

		// get_node_allocator() const & non-const
		// constructs_node() >> will throw exception and erase node if doesn't work
		// create_node() >> get and construct and return node
		// destroy_node() >> destroy
		// clone_node() >> generate a node from a src, copy and return it

		protected:

		// ACCESS
		
		//	struct tree_impl >> inherites allocator, key_compare, header

		private:

		// ATTRIBUTES

			allocator_type	_alloc;
			base_ptr		_root;
			base_ptr		_header;
			base_ptr		_nodes;
			rb_tree&		_t;

		// MEMBER FUNCTIONS

			template<class V>
			node_ptr
			create_node();
				// allocate and append or reuse >> return addr and construct
				// check for balance

		// ALLOCATION

			//_allocate();
			//_recycle();

		// struct reuse or realloc
		// reuse or alloc >> recycle a pool of nodes, using alloc only once pool empty
		//		operator() to destroy/construct a node
		//		extract() from the pool, return a node
		//		attributes: root, nodes and tree
		
		// struct alloc without reusing
		//		operator()
		//		attribute tree	
		
	};	/* rb_tree class */

}	/* namespace ft */

#endif
