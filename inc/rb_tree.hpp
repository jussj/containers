#ifndef	RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>				// allocator
# include <cstddef>				// ptrdiff_t
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
# include "utils.hpp"

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

		rb_tree_node_base	node;
		size_t				node_count;

		// CTOR

		rb_tree_header() {
			node.color = RED;
			//node.color = BLACK;
			reset();
		}

		// MEMBER FUNCTIONS

		void
		move_data(rb_tree_header& src) {
			node.color = src.node.color;
			node.parent = src.node.parent;
			node.left = src.node.left;
			node.right = src.node.right;
			node.parent->parent = &node;
			
			src.reset();	
		}
		void
		reset() {
			node.parent	= 0;			// root
			node.left	= &node;
			node.right	= &node;
			node_count	= 0;
		}

	};	/* rb_tree_header struct */
		/* holds node_count and ends */

	template<class V>
	struct rb_tree_node : public rb_tree_node_base {

		typedef rb_tree_node<V>*	node_ptr;
		typedef V					value_type;
		typedef V*					value_ptr;

		value_ptr					value;

		value_ptr
		node_content() {
			return this->value;
		}

		value_type&
		operator*() {
			return *(this->value);
		}
	
	};	/* rb_tree_node struct */
		/* inherites base_node and holds value ptr */

	// find a solution to keep the base iterator without loosing the const qualifier 
	template<class T>
	struct rb_tree_iterator {

		//// TYPES ////

		typedef T			value_type;
		typedef T&			reference;
		typedef T*			pointer;

		typedef bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;

		typedef rb_tree_iterator<T>			self;
		typedef rb_tree_node_base::ptr		base_ptr;
		typedef rb_tree_node<T>*			node_ptr;

		//// ATTRIBUTES	////

		base_ptr	node;

		//// CTORS ////
		
		rb_tree_iterator()				: node()	{}
		rb_tree_iterator(base_ptr x)	: node(x)	{}

		//// OVERLOADS ////

		reference
		operator*() const {
			return *static_cast<node_ptr>(node)->node_content();
		}

		pointer
		operator->() const {
			return &(static_cast<node_ptr>(node)->node_content());
		}

		self
		operator++() {
			increment();
			return *this;
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
			return *this;
		}

		self
		operator--(int) {
			self tmp = *this;

			decrement();
			return tmp;
		}
	
		bool
		operator==(const self& src) {
			return this->node == src.node;
		}

		bool
		operator!=(const self& src) {
			return this->node != src.node;
		}
		
		friend bool
		operator==(const self& x, const self& y) {
			return x->node == y->node;
		}

		friend bool
		operator!=(const self& x, const self& y) {
			return x->node != y->node;
		}
		
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

		void
		print_node_ptr() {
			std::cout	<< "   addr   " << &(*node)
						<< std::endl
						<< "   left   " << node->left 
						<< std::endl
						<< "   right  " << node->right
						<< std::endl
						<< "   parent " << node->parent 
						<< std::endl << std::endl;
		}

	};	/* rb_tree_iterator */

	template<class T>
	struct rb_tree_const_iterator/* : public rb_tree_base_iterator*/ {

		// TYPES

		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;

		typedef bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;
		
		typedef rb_tree_iterator<T>				self;
		typedef rb_tree_node_base::const_ptr	base_ptr;
		typedef const rb_tree_node<T>*			node_ptr;
		
		// ATTRIBUTES

		node_ptr	node;

		// CTORS
		
		rb_tree_const_iterator()			: node()	{}
		rb_tree_const_iterator(base_ptr x)	: node(x)	{}

		// OVERLOADS

		reference
		operator*() const {
			return *static_cast<node_ptr>(node)->node_content();
		}

		pointer
		operator->() const {
			//return static_cast<node_ptr>(node)->node_content();
			return &(static_cast<node_ptr>(node)->node_content());
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
			return this->node == src->node;
		}

		bool
		operator!=(const self& src) {
			return this->node != src->node;
		}
		
		friend bool
		operator==(const self& x, const self& y) {
			return x->node == y->node;
		}

		friend bool
		operator!=(const self& x, const self& y) {
			return x->node != y->node;
		}
		
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

	};	/* rb_tree_const_iterator */

	template<class T, class Key, class Val, class Compare, class Alloc>
	class rb_tree_impl {

		//// TYPES ////

		public:

			typedef Val					value_type;
			typedef Key 				key_type;
			typedef T					mapped_value;

			typedef size_t 				size_type;
			typedef ptrdiff_t 			difference_type;
		 
			typedef rb_tree_node_base*				base_ptr;
			typedef const rb_tree_node_base*		const_base_ptr;
			typedef	rb_tree_node<Val>*				node_ptr;
			typedef	const rb_tree_node<Val>*		const_node_ptr;
			typedef rb_tree_header					header;
		
			typedef typename Alloc::template	rebind<rb_tree_node<Val> >::other 
												node_allocator_type;
			typedef Alloc						pair_allocator_type;
			typedef Compare						key_compare;	
		
			typedef rb_tree_iterator<value_type>			iterator;
			typedef rb_tree_const_iterator<value_type>		const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		//// ATTRIBUTES /////

		private:

			pair_allocator_type		_alloc;
			node_allocator_type		_nodalloc;
			key_compare				_comp;
			node_ptr				_root;
			header					_header;
			//rb_tree_impl&	_t;			// second tree layer?

		//// MEMBER FUNCTIONS ////

		public:

			// CTOR / DTOR 

			rb_tree_impl() {}

			rb_tree_impl(const key_compare& comp) 
				:	_alloc(),
					_comp(comp),
					_root(NULL),
					_header()	{}

			rb_tree_impl(const key_compare& comp,
						 const pair_allocator_type& pair_alloc, 
						 const node_allocator_type& node_alloc) 
				:	_alloc(pair_alloc),
				 	_nodalloc(node_alloc),
					_comp(comp) {}
			
			~rb_tree_impl() {}

			//// ACCESS ////

			// ITERATORS
			iterator
			begin() {
				return iterator(_header.node.left);
			}
			const_iterator
			begin() const {
				return const_iterator(_header.node.left);
			}
			iterator
			end() {
				return iterator(&_header.node);
			}
			const_iterator
			end() const {
				return const_iterator(&_header.node);
			}

			// CAPACITY
			size_type
			size() const {
				return _header.node_count;
			}
			
			bool
			empty() const {
				return _header.node_count == 0;
			}

			//// MODIFIERS ////

			void
			left_rotate(base_ptr x) {
				base_ptr y	= x->right;
				x->right	= y->left;

				if (y->left != 0)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == 0)
					(base_ptr&)_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left		= x;
				x->parent	= y;
			}

			void
			right_rotate(base_ptr x) {
				base_ptr y	= x->left;
				x->left		= y->right;

				if (y->right != 0)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == 0)
					(base_ptr&)_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right	= x;
				x->parent	= y;
			}

			iterator
			insert_rebalance(node_ptr n) {
				node_ptr	y;

				while (n->parent->color == RED) {
					if (n->parent == n->parent->parent->left) {	
						y = right(n->parent->parent);
						// case 1
						if (y && y->color == RED) {
							n->parent->color = BLACK;
							y->color = BLACK;
							n->parent->parent->color = RED;
						}
						else {
							// case 2
							if (n == n->parent->right) {
								(base_ptr&)n = parent(n);
								left_rotate((base_ptr&)n);
							}	
							// case 3
							n->parent->color = BLACK;
							n->parent->parent->color = RED;
							right_rotate(n->parent->parent);
						}
					}
					else {
						y = left(n->parent->parent);
						// case 4
						if (y->color == RED) {
							n->parent->color = BLACK;
							y->color = BLACK;
							n->parent->parent->color = RED;
						}
						else {
							// case 5
							if (n == n->parent->left) {
								n = parent(n);
								right_rotate(n);
							}	
							// case 6
							n->parent->color = BLACK;
							n->parent->parent->color = RED;
							left_rotate(n->parent->parent);
						}
					}
				}
				_root->color = BLACK;
				return iterator(n);
			}

			iterator	
			insert_unique(const value_type& v) {
				node_ptr	n	= _create_node(v);
				node_ptr	y	= 0;
				node_ptr	x	= _root;

				while (x != 0) {
					y = x;
				if (key(**n) < key(**x))
					x = left(x);
				else
					x = right(x);
			}
			// set new node's parent
			n->parent = y;
			if (y == 0) {
					_root				= n;
					_root->parent		= &_header.node;
					_root->color		= BLACK;
					
					// set leftmost/rightmost
					_header.node.left	= _root;
					_header.node.right	= _root;
				}
			else if (key(**n) < key(**y) || _header.node_count == 1)
				y->left = n;
			else
				y->right = n;
			n->left		= _header.node.parent; // T.nil
			n->right	= _header.node.parent;
			
			// maintain leftmost/rightmost
			if (key(**n) < key(**left(&_header.node)))
				_header.node.left = (base_ptr&)n; 
			else if (key(**n) > key(**right(&_header.node)))
				_header.node.right = (base_ptr&)n; 
			
			// updt count	
			_header.node_count++;

			// return rebalanced tree iterator on node
			//if (_header.node_count > 2)
				//return iterator(insert_rebalance(n));
			//else
				return iterator(n);
			}

			//// MAP OPERATIONS ////

			const_iterator
			lower_bound(const key_type& x) const;
			
			iterator
			lower_bound(const key_type& x) {
				node_ptr n = _root;
				
				while (n != 0) {
					if (!(_comp(key(**n), x)))
						n = left(n);
					else
						n = right(n);	
				}
				return iterator(n);
			}

			const_iterator
			find(const key_type& x) const;

			iterator
			find(const key_type& x) {
				iterator y = lower_bound(x);
				if (y != 0 && key(*y) == x)
					return y;
				return end();
			}

		protected:
     
			//// ACCESS ////

			// ATTRIBUTES

			pair_allocator_type
			pair_allocator() {
				return _alloc;
			}
			
			node_allocator_type
			node_allocator() {
				return _alloc;
			}

			const key_type
			key(value_type& v) const {
				return v.first;
			}

			// MIN/MAX
			
			static base_ptr
			minimum(base_ptr x)	{ 
				return rb_tree_node_base::minimum(x);
			}
			
			static const_base_ptr
			minimum(const_base_ptr x)	{ 
				return rb_tree_node_base::minimum(x);
			}
			
			static base_ptr
			maximum(base_ptr x)	{ 
				return rb_tree_node_base::maximum(x);
			}
			
			static const_base_ptr
			maximum(const_base_ptr x)	{ 
				return rb_tree_node_base::maximum(x);
			}

			// PTR
			
			static node_ptr
			left(base_ptr x) {
				return static_cast<node_ptr>(x->left);
			}

			static const_node_ptr
			left(const_base_ptr x) { 
				return static_cast<const_node_ptr>(x->left);
			}

			static node_ptr
			right(base_ptr x) {
				return static_cast<node_ptr>(x->right);
			}

			static const_node_ptr
			right(const_base_ptr x) { 
				return static_cast<const_node_ptr>(x->right);
			}
			
			static node_ptr
			parent(base_ptr x) {
				return static_cast<node_ptr>(x->parent);
			}

			static const_node_ptr
			parent(const_base_ptr x) { 
				return static_cast<const_node_ptr>(x->parent);
			}

			static const key_type&
			key(const_base_ptr x) { 
				return key(static_cast<const_node_ptr>(x));
			}

		private:

			//// NODES ////

			// ALLOCATION

			node_ptr
			_allocate();
			node_ptr
			_recycle();

			void
			_dealloc_node(node_ptr& n) {
				_nodalloc.deallocate(n, 1);
			}

			node_ptr
			_alloc_node() {
				return _nodalloc.allocate(1);
			}

			// CONSTRUCTION

			value_type*
			_construct_pair(value_type v) {
				value_type*	pair = _alloc.allocate(1);
				_alloc.construct(pair, v);
				return pair;
			}
	
			void
			_destroy_node(node_ptr n);

			void
			_construct_node(node_ptr& n, value_type v) {
				try {
					_alloc.construct(n, v);
				}
				catch (...) {
					_dealloc_node(n);
					// throw exception in case construction didn't work
				}
			}

			// CREATION

			node_ptr
			_init_node_ptr(node_ptr n, node_ptr pos = 0) {
				n->parent = pos;
				n->left = 0;
				n->right = 0;
				n->color = RED;
				return n;
			}

			//template<class V>			// if const
			node_ptr
			_create_node(value_type val, node_ptr pos = 0) {
				node_ptr	n;

				n			= _alloc_node();		// replace w allocator dispatch
				n->value	= _construct_pair(val);
				_init_node_ptr(n, pos);
				return n;
			}
			
			node_ptr
			_clone_node(node_ptr src);
			
			// struct reuse or realloc
			// reuse or alloc >> recycle a pool of nodes,
			// using alloc only once pool empty
				 // operator() to destroy/construct a node
				 // extract() from the pool, return a node
				 // attributes: root, nodes and tree
			
			// struct alloc without reusing
			      // operator()
			      // attribute tree	
		
	};	/* rb_tree class */
		
}	/* namespace ft */

#endif
