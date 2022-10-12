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

		typedef rb_tree_node<V>*	ptr;
		typedef V					value_type;

		V							value;

		rb_tree_node(value_type v)
			: value(v) {}

		rb_tree_node<V>&
		value_ptr() {
			return *this;
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

		base_ptr	node;

		// CTORS
		
		rb_tree_iterator()				: node()	{}
		rb_tree_iterator(base_ptr x)	: node(x)	{}

		// OVERLOADS

		reference
		operator*() const {
			return *static_cast<node_ptr>(node)->value_ptr();
		}

		pointer
		operator->() const {
			return static_cast<node_ptr>(node)->value_ptr();
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

	};	/* rb_tree_iterator */

	template<class T>
	struct rb_tree_const_iterator : public rb_tree_base_iterator {

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
			return *static_cast<node_ptr>(node)->value;
		}

		pointer
		operator->() const {
			return static_cast<node_ptr>(node)->value;
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


	};	/* rb_tree_const_iterator */

	template<	class T, class Key, class Val, class Compare, 
				class Alloc = std::allocator<rb_tree_node<Val> > >
	class rb_tree_impl {

		// TYPES

		public:

			typedef Key 				key_type;
			typedef T					mapped_value;
			typedef Val					value_type;

			//typedef mapped_value* 		pointer;
			//typedef const mapped_value* const_pointer;
			//typedef mapped_value& 		reference;
			//typedef const mapped_value& const_reference;
		
			typedef size_t 				size_type;
			typedef ptrdiff_t 			difference_type;
		
			typedef Alloc 				allocator_type;
			typedef Compare				key_compare;	
		
			typedef rb_tree_iterator<value_type>			iterator;
			typedef rb_tree_const_iterator<value_type>		const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		protected:

			typedef rb_tree_node_base*				base_ptr;
			typedef const rb_tree_node_base*		const_base_ptr;
			typedef rb_tree_header					header;
			typedef	rb_tree_node<Val>*				node_ptr;
			typedef	const rb_tree_node<Val>*		const_node_ptr;
	
		// ATTRIBUTES

		private:

			allocator_type	_alloc;
			key_compare		_comp;
			node_ptr		_root;
			header			_header;
			base_ptr		_nodes;
			//rb_tree_impl&	_t;			// second tree layer?

		// MEMBER FUNCTIONS

		public:
		
			// CTOR / DTOR 

			rb_tree_impl() {}

			rb_tree_impl(const key_compare& comp) 
				:	_alloc(),
					_comp(comp),
					_root(NULL),
					_header()	{}

			rb_tree_impl(const key_compare& comp,
						 const allocator_type& alloc) 
				:	_alloc(alloc),
					_comp(comp) {}
			
			~rb_tree_impl() {}

			// ACCESS 

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

			// ATTRIBUTES
			allocator_type
			get_allocator() {
				return _alloc;
			}

			const key_type
			key(node_ptr& n) const {
				return n->value.first;
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

			// MODIFIERS

			iterator	
			insert_unique(const value_type& v) {
				node_ptr	n	= _create_node(v);
				node_ptr	y	= 0;
				node_ptr	x	= _root;

				if (x == 0) {
					_root			= n;
					_root->left		= _header.node.parent;
					_root->right	= _header.node.parent;
					_root->parent	= &_header.node;
					_root->color	= BLACK;
					_header.node_count++;
					return iterator(n);
				}
				while (x != 0) {
					y = x;
					if (key(n) < key(x))
						(base_ptr&)x = x->left;
					else
						(base_ptr&)x = x->right;
				}
				n->parent = y;
				if (y == 0) 
					_root = n;
				else if (key(n) < key(y))
					y->left = n;
				return iterator(n);
			}

			// OPERATIONS
			
			const_iterator
			lower_bound(const key_type& x) const;
			
			iterator
			lower_bound(const key_type& x) {
				node_ptr n = _root;
				
				while (n != 0) {
					if (!(_comp(key(n), x)))
						(base_ptr&)n = n->left;
					else
						(base_ptr&)n = n->right;	
				}
				return iterator(n);
			}

			const_iterator
			find(const key_type& x) const;

			iterator
			find(const key_type& x) {
				iterator y = lower_bound(x);
				if (key(*y) == key(*x))
					return y;
				return end();
			}

		private:

			// NODE ALLOCATION
			
			node_ptr
			_alloc_node() {
				return _alloc.allocate(1);
			}
	
			void
			_dealloc_node(node_ptr& n) {
				_alloc.deallocate(n, 1);
			}

			node_ptr
			_allocate();
			node_ptr
			_recycle();

			// NODE CTOR

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

			void
			_destroy_node(node_ptr n);

			node_ptr
			_clone_node(node_ptr src);
			
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

				n = _alloc_node();		// replace w allocator dispatch
				_construct_node(n, val);
				_init_node_ptr(n, pos);
				return n;
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
