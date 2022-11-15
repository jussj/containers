#ifndef	RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>				// allocator
# include <cstddef>				// ptrdiff_t
# include <iomanip>				// debug setw
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
		copy_data(const rb_tree_header& src) {
			if (src.node.parent == 0) {
				reset();
				return ;
			}
			node.color	= src.node.color;
			node.parent = src.node.parent;
			node.left	= src.node.left;
			node.right	= src.node.right;
			node.parent->parent = &node;
			
			node_count	= src.node_count;	
		}
		void
		move_node_data(rb_tree_header& src) {
			node.color	= src.node.color;
			node.parent = src.node.parent;
			node.left	= src.node.left;
			node.right	= src.node.right;
			node.parent->parent = &node;
			
			src.reset();	
		}
		void
		reset() {
			node.parent	= 0;		// will be set to root
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
		node_content() const {
			return this->value;
		}

		value_type&
		operator*() const {
			return *(this->value);
		}

		// declaring a unique ptr to bottom NIL sentinel
		static node_ptr			   nil;

	private:

		// declaring the node "content"
		static rb_tree_node 	   _nil_node;

		// init function for NIL sentinel
		static rb_tree_node
		black_node() {
			rb_tree_node	node;
			
			// only non-null value (leafs must be black)
			node.color	= BLACK;
			node.parent	= 0;
			node.right	= &node;
			node.left	= &node;
			return node;
		}

	};	/* rb_tree_node struct */

	template<class T>
	struct rb_tree_iterator;
	
	template<class T>
	struct rb_tree_const_iterator;

	// static nil node initialization
	template<class Val>
	rb_tree_node<Val> rb_tree_node<Val>::_nil_node =
		rb_tree_node<Val>::black_node();

	template<class Val>
	typename rb_tree_node<Val>::node_ptr rb_tree_node<Val>::nil =
		&rb_tree_node<Val>::_nil_node;

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
			key_compare				_compare;
			node_ptr				_root;
			header					_header;
			//rb_tree_impl&			_t;			// implement second tree layer?

		//// MEMBER FUNCTIONS ////

		public:

			// CTOR / DTOR 

			rb_tree_impl()
				:	_alloc(),
				 	_nodalloc(),
					_compare(),
					_root(nil()),
					_header()	{}

			rb_tree_impl(const key_compare& comp) 
				:	_alloc(),
				 	_nodalloc(),
					_compare(comp),
					_root(nil()),
					_header()	{}

			rb_tree_impl(const key_compare& comp,
						 const pair_allocator_type& pair_alloc, 
						 const node_allocator_type& node_alloc) 
				:	_alloc(pair_alloc),
				 	_nodalloc(node_alloc),
					_compare(comp),
					_root(nil()),
					_header() {}
		
			rb_tree_impl(const rb_tree_impl& src) 
				:	_alloc(),
					 _nodalloc(),
					_compare(),
					_root(),
					_header()	{
				*this = src;		
			}

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

			//// OVERLOADS ////

			rb_tree_impl&
			operator=(const rb_tree_impl& src) {
				_compare	= src._compare;
				_nodalloc	= src._nodalloc;
				_alloc		= src._alloc;
				_root		= src._root;
				_header.copy_data(src._header);
				return *this;
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

				if (y->left != nil())
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nil())
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
			
				if (y->right != nil())
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nil())
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

			// MARKERS MAINTENANCE

			void
			maintain_root(node_ptr n) {
				node_ptr new_root	= n;
			
				while (new_root->parent != &(_header.node)) // find root
					new_root = parent(new_root);
				// TO-DO make root be a ptr on a node
				_set_new_root(new_root);	
			}

			// INSERTIONS

			iterator
			rebalance_after_insert(node_ptr n) {
				node_ptr	y;
			
				while (n->parent->color == RED) {
					if (n->parent == n->parent->parent->left) {
						y = right(n->parent->parent);
						// case 1: red uncle
						if (y->color == RED) {
							//if (n->parent != header)
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
								(base_ptr&)n = parent(n);
								left_rotate((base_ptr&)n); // turn n left
							}	
							// case 3: uncle black, n is left child
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
							if (parent(parent(n)) != _root)
								(base_ptr&)n = n->parent->parent;
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
				maintain_root(n);
				return iterator(n);
			}

			node_ptr
			_find_pos_with_hint(node_ptr n, value_type v) {
			//_find_pos_with_hint(node_ptr n, const value_type& v) {
				node_ptr	y = nil();
				node_ptr	x = _create_node(v);
				
				while (x != nil()) {
					y = x;
					if (_compare(key_of_value(**n), key_of_value(**x)))
						x = left(x);
					else
						x = right(x);
				}
				return y;
			}
			
			node_ptr
			_find_pos(node_ptr n) {
				node_ptr	y = nil();
				node_ptr	x = _root;
				
				while (x != nil()) {
					y = x;
					if (_compare(key_of_value(**n), key_of_value(**x)))
						x = left(x);
					else
						x = right(x);
				}
				return y;
			}

			iterator	
			insert_and_rebalance(const value_type& v, iterator hint = 0) {
				node_ptr	n	= _create_node(v);
				node_ptr	y	= nil();
				node_ptr	x	= _root;

				(void)hint;

				//if (hint == 0)
					//y = _find_pos(n);
				//else {
					//value_type x = (*hint);
					////value_type x = (*hint);
					//y = _find_pos_with_hint(n, x);
				//}

				while (x != nil()) {
					y = x;
					if (_compare(key_of_value(**n), key_of_value(**x)))
						x = left(x);
					else
						x = right(x);
				}
				// set new node's parent
				n->parent = y;
				// first node
				if (y == nil())
					_init_root_and_header(n);
				else if (_compare(key_of_value(**n), key_of_value(**y)))
					y->left = n;
				else
					y->right = n;
				n->left		= nil();
				n->right	= nil();
				
				// maintain leftmost/rightmost
				if (_compare(key_of_value(**n), 
						key_of_value(**left(&_header.node))))
					_header.set_leftmost(n); 
				else if (_compare(key_of_value(**right(&_header.node)),
								key_of_value(**n)))
					_header.set_rightmost(n); 

				// update count	
				_header.node_count++;

				// return rebalanced tree iterator on node
				if (_header.node_count > 2)
					rebalance_after_insert(n);
				_header.node.color = RED;
				return iterator(n);
			}

			// DELETIONS

			void
			rebalance_after_erase(base_ptr x) {
				base_ptr w;

				while (x != _root && x->color == BLACK) {
					if (x == x->parent->left) {
						w = x->parent->right;
						// case 1: sibling is red
						if (w->color == RED) {
							w->color = BLACK;
							if (x->parent != nil())
								x->parent->color = RED;
							left_rotate(x->parent);
							w = x->parent->right;
						}
						// case 2: sibling is black
						// and nephews are blacks
						if (w->left->color == BLACK
								&& w->right->color == BLACK) {
							if (w != nil())
								w->color = RED;
							x = x->parent;
						}
						else {
							// case 3: sibling is black, 
							// left nephew red, right is black
							if (w->right->color == BLACK) {
								if (w->left != nil())
									w->left->color = RED;
								if (w != nil())
									w->color = RED;
								right_rotate(w);
								w = x->parent->right;
							}
							// case 4: the other way
							if (w != nil())
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
							if (x->parent != nil())
								x->parent->color = RED;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						// case 6
						if (w->right->color == BLACK 
								&& w->left->color == BLACK) {
							if (w != nil())
								w->color = RED;
							x = x->parent;
						}
						else {
							// case 7
							if (w->left->color == BLACK) { 
								if (w->right != nil())
									w->right->color = RED;
								if (w != nil())
									w->color = RED;
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
				if (u->parent == nil())
					(base_ptr&)_root = v;
				else if (u->parent->left == u)	// is node p left child
					u->parent->left = v;		// set parent left to
				else							// its child or 0
					u->parent->right = v;
				v->parent = u->parent;
			}

			void
			erase_leaf_and_rebalance(base_ptr n, base_ptr y) {
				// create "doubly black" node to rebalance the tree
				node_ptr x	= _alloc_node();
				y			= n->parent;
			
				// parent is n old parent
				x->parent	= y;
				x->left		= nil();
				x->right	= nil();
				x->color	= BLACK;
				if (y->left == nil())
					y->left = x;
				else
					y->right = x;
				
				// rebalance with doubly black node
				rebalance_after_erase(x);
				
				// delete node
				if (y->left == x)
					y->left = nil();
				else
					y->right = nil();
				_header.node.color = RED;
				_dealloc_node(x);
			}


			void
			erase_and_rebalance(iterator pos) {
				base_ptr n	= pos.node;		// node to be deleted
				base_ptr y	= n;			// successor to n
				base_ptr x;					// successor to y

				// save erased node original color
				t_color original_color	= y->color;

				// maintain leftmost/rightmost
				if (leftmost() == n)
					_header.set_leftmost(n->parent);
				if (rightmost() == n)
					_header.set_rightmost(n->parent);
				
				// has 0 to 1 child
				if (left(n) == nil()) {
					x = n->right;				// save only child
					transplant(n, n->right);	// replace parent child 
				}								// by its own child
				else if (n->right == nil()) {
					x = n->left;	
					transplant(n, n->left);
				}
				
				// has 2 children
				else {	
					y = minimum(n->right);		// n closest successor
					original_color = y->color;
					if (y->right == nil()		// set successor to y
							&& size() == 3)
						x = n->left;
					else 
						x = y->right;
					if (y->parent == n)
						x->parent = y;
					else {
						transplant(y, y->right);
						y->right = n->right;
						y->right->parent = y;
					}
					transplant(n, y);
					y->left			= n->left;
					y->left->parent = y;
					y->color		= n->color;
				}
				_header.node_count--;
				if (original_color == BLACK) {
					// n was with no child
					if (x == nil() && y == n)
						erase_leaf_and_rebalance(n, y);
					else
						rebalance_after_erase(x);
				}
				if (size() == 1)
					y = _root;
				
				// maintain root
				if (n == _root) {
					// only one elem left, becomes root
					if (size() == 1)
						y = x;
					(base_ptr&)_root	= y;
					_header.node.parent = _root;
					if (empty())
						_reset_root_and_header();
				}
				else
					maintain_root(parent(n));
				
				// maintain max/min
				if (size() == 1) {
					_header.set_rightmost(y);
					_header.set_leftmost(y);
				}
				else if (!empty()) {
					_header.set_rightmost(maximum(_header.node.right));
					_header.set_leftmost(minimum(_header.node.left));
				}	
				_header.node.color = RED;
				_destroy_node((node_ptr&)pos.node);
			}

			void
			clear() {
				if (empty())
					return ;
				_clear_from(root());

				_reset_root_and_header();
				//_header.set_leftmost(&_header.node);
				//_header.set_rightmost(&_header.node);
				_header.node_count = 0;
			}

			//// MAP OPERATIONS ////

			iterator
			upper_bound(const key_type& x) {
				node_ptr n = _root;
				base_ptr m = &_header.node;
				
				while (n != nil()) {
					if (_compare(x, key_of_value(**n)))
						m = n, n = left(n);
					else
						n = right(n);
				}
				return iterator(m);
			}

			const_iterator
			upper_bound(const key_type& x) const {
				node_ptr n = _root;
				base_ptr m = nil();
				
				while (n != nil()) {
					if (_compare(x, key_of_value(**n)))
						m = n, n = left(n);
					else
						n = right(n);
				}
				if (m == nil())
					return end();
				return const_iterator(m);
			}

			iterator
			lower_bound(const key_type& x) {
				node_ptr n = _root;
				base_ptr m = &_header.node;
				
				while (n != nil()) {
					if (!(_compare(key_of_value(**n), x))) // same than above
						m = n, n = left(n);
					else
						n = right(n);
				}
				return iterator(m);
			}
			
			const_iterator
			lower_bound(const key_type& x) const {
				node_ptr n = _root;
				base_ptr m = nil();
			   
				while (n != nil()) {
					if (!(_compare(key_of_value(**n), x))) // same than above 
						m = n, n = left(n);
					else
						n = right(n);
				}
				if (m == nil())
					return end();
				return const_iterator(m);
			}

			iterator
			find(const key_type& x) {
				iterator y = lower_bound(x);
				if (y != nil() && y != end()
						&& key_of_value(*y) == x)
					return y;
				return end();
			}

			const_iterator
			find(const key_type& x) const {
				const_iterator y = lower_bound(x);
				if (y != nil() && y != end()
						&& (*y).first == x)
					return y;
				return end();
			}

			key_compare
			compare() const {
				return _compare;
			}

			size_type
			max_size() const {
				return _nodalloc.max_size();
			}

			// DEBUG
			
			void
			print_header() {
				std::cout	<< "   root:  " << key_of_value(**root())
							<< "\t(" << root() << ")" << std::endl
							<< "   lmost: " << key_of_value(**leftmost()) 
							<< "\t(" << leftmost() << ")" << std::endl
							<< "   rmost: " << key_of_value(**rightmost()) 
							<< "\t(" << rightmost() << ")" << std::endl
							<< "   nil:   " << 0 << "\t(" 
							<< nil() << ")" << std::endl
							<< "   head:  " << "\t(" << &(_header.node) << ")"
							<< std::endl
							<< "  (color)\t";
							if (_header.node.color == RED)
								std::cout << "RED" << std::endl;
							else if (_header.node.color == BLACK)
								std::cout << "BLACK" << std::endl;
				std::cout	<< "   bh:    " << black_height() << std::endl;
			}

			void
			print_node(char role, node_ptr x, int depth) {
				std::cout << " ";
				while (depth > 0) {
					if (depth == 1)
						std::cout << "|----";
					else
						std::cout << "\t";
					depth--;
				}   
				(void)role;
				std::cout << role << "[";
				if (x->color == RED)
					 std::cout << "\033[31m";
				std::cout << std::setw(10);
				if (x == nil())
					std::cout << "NIL";
				else
					std::cout << std::left <<  key_of_value(**x);
				std::cout << "\033[0m";
			}

			void
			graphic_visualizer(node_ptr x, int depth) {
				if (x != nil()) {   
					graphic_visualizer(right(x), depth + 1); 
					if (x == _root)
						print_node('R', x, depth);
					else if (x == leftmost())
						print_node('l', x, depth);
					else if (x == rightmost())
						print_node('r', x, depth);
					else
						print_node('-', x, depth);
					std::cout << std::endl;
					graphic_visualizer(left(x), depth + 1); 
				}   
			}
			
		protected:
     
			//// ACCESS ////

			// ATTRIBUTES

			pair_allocator_type
			pair_allocator() const {
				return _alloc;
			}
			
			node_allocator_type
			node_allocator() const {
				return _nodalloc;
			}

			const key_type
			key_of_value(value_type& v) const {
				return v.first;
			}
			
			const key_type
			key(node_ptr n) const {
				return key_of_value(static_cast<node_ptr>(n->value));
			}

			node_ptr
			nil() const {
				return rb_tree_node<Val>::nil;	
			}
			
			size_type
			count() const {
				return _header.node_count;
			}

			// MIN/MAX ACCESS
			
			static base_ptr
			minimum(base_ptr x)	{ 
				while (x->left != rb_tree_node<Val>::nil)
					x = x->left;
				return x;	
			}
			
			static const_base_ptr
			minimum(const_base_ptr x)	{ 
				while (x->left != rb_tree_node<Val>::nil)
					x = x->left;
				return x;	
			}
			
			static base_ptr
			maximum(base_ptr x)	{ 
				while (x->right != rb_tree_node<Val>::nil)
					x = x->right;
				return x;	
			}
			
			static const_base_ptr
			maximum(const_base_ptr x)	{ 
				while (x->right != rb_tree_node<Val>::nil)
					x = x->right;
				return x;	
			}

			// POINTERS ACCESS
			
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

			// HEADER DATA ACCESS
	
			// for debug purposes
		public:			
			node_ptr
			root() {
				return static_cast<node_ptr>(_header.node.parent);
			}

			// TO-DO db check for unjustified non priv members
		protected:	
			node_ptr
			leftmost() {
				return static_cast<node_ptr>(_header.node.left);
			}

			node_ptr
			rightmost() {
				return static_cast<node_ptr>(_header.node.right);
			}
			
			//// BLACK HEIGHT ////

			size_type
			black_node_count(base_ptr pos) {
				base_ptr	x		= pos;
				size_type	count	= 0;
				size_type	lcount	= 0;

				while (x != rb_tree_node<Val>::nil) {
					if (x->color == BLACK)
						count += 1;
					x = x->right;
				}
				// control tree balance
				x = pos;
				while (x != rb_tree_node<Val>::nil) {
					if (x->color == BLACK)
						lcount += 1;
					x = x->left;
				}
				// if ret = 0, tree empty or unbalanced
				if (count != lcount)
					return 0;
				
				return count;
			}

			size_type
			black_height() {
				return black_node_count(root());
			}
			
			size_type
			black_height(base_ptr pos) {
				return black_node_count(pos);
			}

		private:

			//// MODIFIERS ////

			void
			_clear_from(node_ptr n) {
				// erase without rebalancing
				while (n != nil()) {	
					_clear_from(right(n));
					node_ptr m = left(n);
					_destroy_node(n);
					n = m;
				}
			}

			node_ptr
			_copy_from(node_ptr x, node_ptr p = 0) {
				// save for ret value
				node_ptr start = x;

				if (p == 0)
					(base_ptr&)p = &_header.node;
				// copy tree structure, no rebalance needed
				while (x != nil()) {
					node_ptr y = _alloc_node();
					if (start == x)
						start = y;

					y->value	= _construct_pair(value(x));
					p->left		= y;	
					y->parent	= p;	
					y->color	= x->color;	
					y->right	= _copy_from(right(x), y);
					
					p = y;
					(base_ptr&)x = x->left;
				}
				p->left = nil();
				return start;
			}
			
			void
			_init_root_and_header(node_ptr n) {
				_set_new_root(n);
				_root->parent = &_header.node;
				
				// set leftmost/rightmost and parent
				_header.set_leftmost(n);
				_header.set_rightmost(n);
			}
			
			void
			_reset_root_and_header() {
				_root = nil();
				_header.reset();
			}
			void
			_set_new_root(node_ptr n) {
				_root				= n;
				_root->color		= BLACK;
				_header.node.parent	= _root;
			}

			//// NODES AND VALUES MEMORY ////

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
				n->left = rb_tree_node<Val>::nil;
				n->right = rb_tree_node<Val>::nil;
				n->color = RED;
				return n;
			}

			// RECYCLING NODES POOL

			// struct reuse or realloc
			// reuse or alloc >> recycle a pool of nodes,
			// using alloc only once pool empty
				 // operator() to destroy/construct a node
				 // extract() from the pool, return a node
				 // attributes: root, nodes and tree
			
			// struct alloc without reusing
			      // operator()
			      // attribute tree	
		
			node_ptr
			_allocate();
			node_ptr
			_recycle();

			// PAIRS

			// TO-DO try catch STL like to implement, see construct_node
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
		
			//template<class V>			// if const?
			node_ptr
			_create_node(value_type val, node_ptr pos = 0) {
				node_ptr	n;

				// TO-DO replace w allocator dispatch
				n			= _alloc_node();
				n->value	= _construct_pair(val);
				
				_init_node_ptr(n, pos);
				return n;
			}

			void
			_destroy_node(node_ptr& n) {
				_destroy_pair(n);
				_dealloc_node(n);	
			}

	};	/* rb_tree class */
	
	// COMPARISON OVERLOADS
	
	template<class T, class Key, class Val, class Compare, class Alloc>
	bool
	operator==(const rb_tree_impl<T, Key, Val, Compare, Alloc>& x,
			const rb_tree_impl<T, Key, Val, Compare, Alloc>& y) {
		return x.size() == y.size() 
			&& ft::lexicographical_compare(x.begin(), x.end(),
					y.begin(), y.end());
	}

	template<class T, class Key, class Val,
		class Compare, class Alloc>
	bool
	operator<(const rb_tree_impl<T, Key, Val, Compare, Alloc>& x,
			const rb_tree_impl<T, Key, Val, Compare, Alloc>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), 
				y.begin(), y.end());
	}

	// TO-DO find a solution to keep the base iterator
	// without loosing the const qualifier 
	template<class T>
	struct rb_tree_iterator {

		// TYPES ////

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
		rb_tree_iterator(const self& src)
			: node() {
			*this = src;
		}
		// cpy ctor

		//// OVERLOADS ////

		// ACCESS

		self&
		operator=(const self& src) {
			node = src.node;
			return *this;
		}

		reference
		operator*() const {
			return *static_cast<node_ptr>(node)->node_content();
		}

		pointer
		operator->() const {
			return static_cast<node_ptr>(node)->node_content();
		}

		// DECREM/INCREMENTATION OPERATIONS

		self&
		operator++() {
			if (node->right != rb_tree_node<T>::nil) {
				node = node->right;
				while (node->left != rb_tree_node<T>::nil)
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
			self tmp(*this);

			++(*this);
			return tmp;
		}

		self&
		operator--() {
			if (node->parent->parent == node
					&& node->color == RED) {	// look for header
				node = node->right;				// return rightmost
			}
			else if (node->left != rb_tree_node<T>::nil) {
				base_ptr x = node->left;
				while (x->right != rb_tree_node<T>::nil)
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
			self tmp(*this);

			--(*this);
			return tmp;
		}

		// COMPARISON
	
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

		typedef rb_tree_iterator<T>			iterator;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;
		
		typedef rb_tree_const_iterator<T>		self;
		typedef rb_tree_node_base::const_ptr	base_ptr;
		typedef const rb_tree_node<T>*			node_ptr;
		
		// ATTRIBUTES

		base_ptr	node;

		// CTORS
		
		rb_tree_const_iterator()			: node()	{}
		rb_tree_const_iterator(base_ptr x)	: node(x)	{}
		rb_tree_const_iterator(const iterator& it)
			: node(it.node)	{}

		// OVERLOADS

		reference
		operator*() const {
			return *static_cast<node_ptr>(node)->node_content();
		}

		pointer
		operator->() const {
			return static_cast<node_ptr>(node)->node_content();
		}

		// DECREM/INCREMENTATION OPERATIONS

		self&
		operator++() {
			if (node->right != rb_tree_node<T>::nil) {
				node = node->right;
				while (node->left != rb_tree_node<T>::nil)
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
			self tmp(*this);

			++(*this);
			return tmp;
		}

		self&
		operator--() {
			if (node->parent->parent == node
					&& node->color == RED) {	// look for header
				node = node->right;				// return rightmost
			}
			else if (node->left != rb_tree_node<T>::nil) {
				base_ptr x = node->left;
				while (x->right != rb_tree_node<T>::nil)
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
			self tmp(*this);

			--(*this);
			return tmp;
		}

		// COMPARISON
	
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

	};	/* rb_tree_const_iterator */
		
}	/* namespace ft */

#endif
