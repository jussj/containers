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
		BLACK
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

	struct rb_tree_header {

		// ATTRIBUTES

		rb_tree_node_base	node;
		size_t				node_count;

		// CTOR

		rb_tree_header() {
			node.color = RED;
			reset();
		}

		// SET
		
		void
		set_leftmost(rb_tree_node_base* n) {
			node.left = n;
		}
		
		void
		set_rightmost(rb_tree_node_base* n) {
			node.right = n;
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
			node.parent	= 0;		// root
			node.left	= &node;
			node.right	= &node;
			node_count	= 0;
		}

	};	/* rb_tree_header struct */

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

	// find a solution to keep the base iterator
	// without loosing the const qualifier 
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

		self&
		operator++() {
			if (node->right != 0) {
				node = node->right;
				while (node->left != 0)
					node = node->left;
			}
			else {
				base_ptr x = node->parent;
				while (node == x->right) {
					node = x;
					x = x->parent;
				}
				if (node->right != x) // rightmost
					node = x;
			}
			return *this;
		}

		self
		operator++(int) {
			self tmp = *this;

			++node;
			return tmp;
		}
		self&
		operator--() {
			if (node->parent->parent == node
					&& node->color == RED) {	// look for header
				node = node->right;				// return rightmost
			}
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
			return *this;
		}

		self
		operator--(int) {
			self tmp = *this;

			--node;
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

		// DEBUG

		void
		print_node_ptr() {
			std::cout	<< "   color  ";
			if (node->color == BLACK)
				std::cout << "BLACK";
			else
				std::cout << "RED";	
			std::cout	<< std::endl
						<< "   addr   " << &(*node)
						<< std::endl
						<< "   left   " << node->left
						<< std::endl
						<< "   right  " << node->right
						<< std::endl
						<< "   parent " << &(*(node->parent))
						<< std::endl << std::endl;
		}

	};	/* rb_tree_iterator */

	template<class T>
	struct rb_tree_const_iterator {

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
					&& node->parent->parent == node) {
				node = node->right;
			}
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
		 
			typedef rb_tree_node_base*			base_ptr;
			typedef const rb_tree_node_base*	const_base_ptr;
			typedef	rb_tree_node<Val>*			node_ptr;
			typedef	const rb_tree_node<Val>*	const_node_ptr;
			typedef rb_tree_header				header;
		
			typedef typename Alloc::template	rebind<rb_tree_node<Val> >::other 
												node_allocator_type;
			typedef Alloc						pair_allocator_type;
			typedef Compare						key_compare;	
		
			typedef rb_tree_iterator<value_type>			iterator;
			typedef rb_tree_const_iterator<value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		//// ATTRIBUTES /////

		private:

			pair_allocator_type		_alloc;
			node_allocator_type		_nodalloc;
			key_compare				_comp;
			node_ptr				_root;
			header					_header;
			//rb_tree_impl&	_t;			// implement second tree layer?

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
		
			// not destroying anything	
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

			// ROTATIONS

			void
			left_rotate(base_ptr x) {
				base_ptr y	= x->right;
				x->right	= y->left;
				
				// maintain leftmost and rightmost
				base_ptr	lmost = _header.node.left;
				base_ptr	rmost = _header.node.right;

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

				_header.set_leftmost(lmost);
				_header.set_rightmost(rmost);
			}

			void
			right_rotate(base_ptr x) {
				base_ptr y	= x->left;
				x->left		= y->right;
				
				// maintain leftmost and rightmost
				base_ptr	lmost = _header.node.left;
				base_ptr	rmost = _header.node.right;
			
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
				
				_header.set_leftmost(lmost);
				_header.set_rightmost(rmost);
			}

			// INSERTIONS

			void
			maintain_root(node_ptr n) {
				node_ptr new_root	= n;
				
				while (new_root->parent != &(_header.node)) // find root
					new_root = parent(new_root);
				
				this->_root			= new_root;
				this->_root->color	= BLACK;
				
				_header.node.parent	= _root;				// make root be a ptr on a node
			}

			iterator
			insert_rebalance(node_ptr n) {
				node_ptr	y;
			
				while (n->parent->color == RED) {
					std::cout<<"---NODE "<<key_of_value(**n)<<std::endl;	
					if (n->parent == n->parent->parent->left) {
						y = right(n->parent->parent);
						// case 1: red uncle
						if (y && y->color == RED) {
							std::cout<<"---1"<<std::endl;
							n->parent->color = BLACK;
							y->color = BLACK;
							n->parent->parent->color = RED;
							// repeat with n being gp, do not if root
							if (parent(parent(n)) != _root)
								(base_ptr&)n = n->parent->parent;
						}
						else {
							// case 2: uncle black, n is right child
							if (n == n->parent->right) {
								std::cout<<"---2"<<std::endl;
								(base_ptr&)n = parent(n);
								left_rotate((base_ptr&)n); // turn n left
							}	
							// case 3: uncle black, n is left child
							std::cout<<"---3"<<std::endl;
							n->parent->color = BLACK;
							n->parent->parent->color = RED;
							right_rotate(n->parent->parent);
						}
					}
					else {
						y = left(n->parent->parent);
						// case 4
						if (y && y->color == RED) {
							std::cout<<"---4"<<std::endl;
							n->parent->color = BLACK;
							y->color = BLACK;
							n->parent->parent->color = RED;
							if (parent(parent(n)) != _root)
								(base_ptr&)n = n->parent->parent;
						}
						else {
							// case 5
							if (n == n->parent->left) {
								std::cout<<"---5"<<std::endl;
								n = parent(n);
								right_rotate(n);
							}	
							// case 6
							std::cout<<"---6"<<std::endl;
							n->parent->color = BLACK;
							n->parent->parent->color = RED;
							left_rotate(n->parent->parent);
						}
					}
				}
				maintain_root(n);
				return iterator(n);
			}

			iterator	
			insert_unique(const value_type& v) {
				node_ptr	n	= _create_node(v);
				node_ptr	y	= 0;
				node_ptr	x	= _root;

				while (x != 0) {
					y = x;
				if (key_of_value(**n) < key_of_value(**x))
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
					// set leftmost/rightmost and parent
					_header.node.left	= n;
					_header.node.right	= n;
					_header.node.parent	= _root;
				}
			// insert first node left?
			else if (key_of_value(**n) < key_of_value(**y))
				y->left = n;
			else
				y->right = n;
			n->left		= 0;
			n->right	= 0;
			
			// maintain leftmost/rightmost
			if (key_of_value(**n) < key_of_value(**left(&_header.node)))
				_header.node.left = (base_ptr&)n; 
			else if (key_of_value(**n) > key_of_value(**right(&_header.node)))
				_header.node.right = (base_ptr&)n; 

			// updt count	
			_header.node_count++;

			// return rebalanced tree iterator on node
			if (_header.node_count > 2)
				return iterator(insert_rebalance(n));
			else
				return iterator(n);
			}

			// DELETIONS

			void
			erase_rebalance(base_ptr x) {
				base_ptr w;

				while (x != _root && x->color == BLACK) {
					if (x == x->parent->left) {
						w = x->parent->right;
						// case 1
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent);
							w = x->parent->right;
						}
						// case 2
						if (w->left->color == BLACK 
								&& w->right->color == BLACK) {
							w->color = RED;
							x = x->parent;
						}
						else {
							// case 3
							if (w->left->color == BLACK 
									&& w->right->color == BLACK) {
								w->color = RED;
								x = x->parent;
								right_rotate(w);
								w = x->parent->right;
							}
							// case 4
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else {
						w = x->parent->left;
						// case 5
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						// case 6
						if (w->right->color == BLACK 
								&& w->left->color == BLACK) {
							w->color = RED;
							x = x->parent;
						}
						else {
							// case 7
							if (w->right->color == BLACK 
									&& w->left->color == BLACK) {
								w->color = RED;
								x = x->parent;
								left_rotate(w);
								w = x->parent->left;
							}
							// case 8
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							right_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
			}

			void
			transplant(base_ptr u, base_ptr v) {
				if (u->parent == 0)
					(base_ptr&)_root = v;
				else if (u->parent->left == u)	// is node p left child
					u->parent->left = v;		// set parent left to
				else							// its child or 0
					u->parent->right = v;
				if (v != 0)
					v->parent = u->parent;		// unconditional in algo bible
			}

			void
			erase(iterator pos) {
				base_ptr n	= pos.node;
				base_ptr y	= n;			// successor	
				base_ptr x;

				// save erased node original color
				t_color original_color	= y->color;

				// maintain leftmost/rightmost
				if (_header.node.left == n)
					_header.node.left = n->parent;
				if (_header.node.right == n)
					_header.node.right = n->parent;
				// has 0 to 1 child
				if (left(n) == 0) {					
					x = n->right;				// save only child
					transplant(n, n->right);	// replace parent child 
				}								// by its own child
				else if (n->right == 0) {
					x = n->left;	
					transplant(n, n->left);
				}
				// has 2 children
				else {		
					y = minimum(n->right);
					//std::cout<<"---MIN "<<y<<std::endl;
					original_color = y->color;
					x = y->right;
					if (y->parent == n)
						x->parent = y;
					else {
						transplant(y, y->right);
						y->right = n->right;
						y->right->parent = y;
					}
					transplant(n, y);
					y->left = n->left;
					y->left->parent = y;
					y->color = n->color;
				}
				_header.node_count--;
				if (original_color == BLACK)
					std::cout<<"---NEEDS FIXUP MATE"<<std::endl;
					//erase_rebalance(x);
				//_destroy_node((node_ptr&)pos.node);
			}

			//// MAP OPERATIONS ////

			const_iterator
			lower_bound(const key_type& x) const {
				node_ptr n = _root;
				node_ptr m = n;
				// init m to header node? last node not less than x
				
				while (n != 0) {
					if (!(_comp(key_of_value(**n), x)))
						m = n, n = left(n);
					else
						n = right(n);
				}
				return const_iterator(m);
			}

			iterator
			lower_bound(const key_type& x) {
				node_ptr n = _root;
				node_ptr m = n;
				// init m to header node? last node not less than x
				
				while (n != 0) {
					if (!(_comp(key_of_value(**n), x)))
						m = n, n = left(n);
					else
						n = right(n);
				}
				return iterator(m);
			}

			const_iterator
			find(const key_type& x) const {
				const_iterator y = lower_bound(x);
				if (y != 0 && key_of_value(*y) == x)
					return y;
				return end();
			}

			iterator
			find(const key_type& x) {
				iterator y = lower_bound(x);
				if (y != 0 && key_of_value(*y) == x)
					return y;
				return end();
			}
			
			// DEBUG
			
			void
			print_header() {
				std::cout	<< "   root:  " << key_of_value(**root())
							<< "\t(" << root() << ")" << std::endl
							<< "   lmost: " << key_of_value(**leftmost()) 
							<< "\t(" << leftmost() << ")" << std::endl
							<< "   rmost: " << key_of_value(**rightmost()) 
							<< "\t(" << rightmost() << ")" << std::endl;
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
			key_of_value(value_type& v) const {
				return v.first;
			}
			
			const key_type
			key(node_ptr n) const {
				return key_of_value(static_cast<node_ptr>(n->value));
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

			// HEADER
		
			node_ptr
			root() {
				return static_cast<node_ptr>(_header.node.parent);
			}
			
			node_ptr
			leftmost() {
				return static_cast<node_ptr>(_header.node.left);
			}
			
			node_ptr
			rightmost() {
				return static_cast<node_ptr>(_header.node.right);
			}

		private:

			//// NODES AND VALUE MEMORY ////

			// NODES

			node_ptr
			_alloc_node() {
				return _nodalloc.allocate(1);
			}
			
			void
			_dealloc_node(node_ptr& n) {
				_nodalloc.deallocate(n, 1);
			}

			//void
			//_construct_node(node_ptr& n, value_type v) {
				//try {
					//_alloc.construct(n, v);
				//}
				//catch (...) {
					//_dealloc_node(n);
					//// throw exception in case construction didn't work
				//}
			//}
			
			node_ptr
			_init_node_ptr(node_ptr n, node_ptr pos = 0) {
				n->parent = pos;
				n->left = 0;
				n->right = 0;
				n->color = RED;
				return n;
			}

			node_ptr
			_clone_node(node_ptr src); // copy ctor?

			// UPCYCLING	

			node_ptr
			_allocate();
			node_ptr
			_recycle();

			// PAIRS

			// try catch STL like to implement, see construct_node
			value_type*
			_construct_pair(value_type v) {
				value_type*	pair = _alloc.allocate(1);
				_alloc.construct(pair, v);
				return pair;
			}
			
			void
			_destroy_pair(node_ptr n) {
				_alloc.destroy(n->value);
				_alloc.deallocate(n->value, 1);
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

			void
			_destroy_node(node_ptr& n) {
				_destroy_pair(n);
				_dealloc_node(n);	
			}
			

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
