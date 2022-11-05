#ifndef MAP_HPP
# define MAP_HPP

# include "iterator.hpp"
# include "utility.hpp"
# include "rb_tree.hpp"
# include <map>

namespace ft {

	template <	class Key,
				class T,
				class Compare	= std::less<Key>,
				class Alloc		= std::allocator<pair<const Key, T> > >
	class map {

		public:

		//// TYPES ////

			typedef Key					key_type;
			typedef T					mapped_type;
			typedef pair<const Key, T>	value_type;
			typedef Compare				key_compare;
			typedef Alloc				allocator_type;
			typedef size_t				size_type;		
			typedef ptrdiff_t			difference_type;

			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;

			typedef ft::rb_tree_iterator<value_type>		iterator;
			typedef ft::rb_tree_const_iterator<value_type>	const_iterator;

			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:

			typedef rb_tree_impl <T, Key, pair<const Key, T>, Compare, Alloc>	
			rb_tree;

		//// ATTRIBUTES ////
		
			allocator_type	_alloc;
			rb_tree			_tree;

		public:

		//// VALUE COMPARE ////

			class value_compare
				: public std::binary_function<value_type, value_type, bool> {
				
				friend class map;
				
				protected:

					Compare comp;
					value_compare(Compare c) : comp(c) {}

				public:

					bool
					operator()(	const value_type& x,
								const value_type& y	) const {
						return comp(x.first, y.first);
					}
			};

		//// CTOR, DTOR AND COPY ////

			explicit
			map(	const key_compare& comp = Compare(), 
					const allocator_type& alloc = Alloc()
					) 
				:	_alloc(alloc), _tree(comp) {}

			template <class InputIterator>
			map(	InputIterator first,
					InputIterator last,
					const key_compare& comp = Compare(),
					const allocator_type& alloc = Alloc()
					)
				:	_alloc(alloc), _tree(comp) {
					insert_and_rebalance(first, last);	
				}

			map(const map<key_type, T, key_compare, allocator_type>& src) 
				: _tree(src) {}
				
			
			~map() {
				clear();
			}

			map<key_type, T, key_compare, allocator_type>&
			operator=(const map<key_type, T, key_compare, allocator_type>& x);

		//// ITERATORS ////

			iterator
			begin() {
				return _tree.begin();
			}

			const_iterator
			begin() const {
				return _tree.begin();
			}
			
			iterator
			end() {
				return _tree.end();
			}
			
			const_iterator
			end() const {
				return _tree.end();
			}
			
			reverse_iterator
			rbegin() {
				return reverse_iterator(_tree.end());
			}
			
			const_reverse_iterator
			rbegin() const {
				return const_reverse_iterator(_tree.end());
			}
			
			reverse_iterator
			rend() {
				return reverse_iterator(_tree.begin());
			}
			
			const_reverse_iterator
			rend() const {
				return const_reverse_iterator(_tree.begin());
			}
		
		//// CAPACITY ////

			bool
			empty() const {
				return _tree.empty();
			}

			size_type
			size() const {
				return _tree.size();	
			}
			
			size_type
			max_size() const {
				return _alloc.max_size();
			}

		//// ACCESS ////

			T&
			operator[](const key_type& x) {
				return _tree.insert_and_rebalance(ft::make_pair(x, mapped_type()))->second;
			}

		//// MODIFIERS ////

			pair<iterator, bool>
			insert(const value_type& x) {
				bool		key		= false;
				iterator	it		= find(x.first);

				if (it == end()) {
					it	= _tree.insert_and_rebalance(x);
					key = true;
				}
				return pair<iterator, bool>(it, key);
			}
			
			iterator
			insert(iterator position, const value_type& x) {
				iterator	it		= find(x.first);

				if (it == end())
					it	= _tree.insert_and_rebalance(x, position);
				return it;
			}
			
			template <class InputIterator>
			void
			insert(InputIterator first, InputIterator last) {
				for (iterator it = first; it != last; ++it)
					insert(it);	
			}
			
			void
			erase(iterator position) {
				_tree.erase_and_rebalance(position);
			}
			
			size_type
			erase(const key_type& x) {
				iterator ret	= find(x);
			   
				if (ret	== end())
					return 0;
				_tree.erase_and_rebalance(ret);
				// return number of occurences
				return 1;
			}
			
			void
			erase(iterator first, iterator last) {
				// erase range by priority order (red nodes that need no rebalance?)
				for (iterator it = first; first != last; ++it)
					_tree.erase_and_rebalance(first);
			}
			
			void
			swap(map<Key, T, Compare, Alloc>&);
			
			void
			clear() {
				_tree.clear();	
			}
			
		//// OBSERVERS ////

			key_compare
			key_comp() const {
				return key_compare(_tree.compare());
			}
			
			value_compare
			value_comp() const {
				return value_compare(_tree.compare());
			}

		//// MAP OPERATIONS ////

			iterator
			find(const key_type& x) {
				return _tree.find(x);
			}
			
			const_iterator
			find(const key_type& x) const {
				return _tree.find(x);
			}
			
			size_type
			count(const key_type& x) const {
				const_iterator ret = find(x);
				if (ret == end())
					return 0;
				return 1;
			}
			
			iterator
			lower_bound(const key_type& x) {
				return _tree.lower_bound(x);
			}
			
			const_iterator
			lower_bound(const key_type& x) const {
				return _tree.lower_bound(x);
			}
			
			iterator
			upper_bound(const key_type& x) {
				return _tree.upper_bound(x);
			}
			
			const_iterator
			upper_bound(const key_type& x) const {
				return _tree.upper_bound(x);
			}
			
			ft::pair<iterator,iterator>
			equal_range(const key_type& x) {
				return ft::pair<iterator, iterator>(
						lower_bound(x), upper_bound(x)
						);
			}
			
			ft::pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const {
				return ft::pair<const_iterator, const_iterator>(
						lower_bound(x), upper_nound(x)
						);
			}

		// DEBUG

			void
			print_header() {
				_tree.print_header();
			}

			void
			print_tree() {
				_tree.graphic_visualizer(_tree.root(), 0);
			}

		// NON-MEMBERS FRIENDSHIP DECLARATION

		public:

			template <class K, class V, class C, class A>
			friend bool
			operator==(	const map<K, V, C, A>& x,
						const map<K, V, C, A>& y	);
			
			template <class K, class V, class C, class A>
			friend bool
			operator<(	const map<K, V, C, A>& x,
						const map<K, V, C, A>& y	);
	
	};	/* class map */

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator==(	const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y	) {
		return x._tree == y._tree;	
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator<(	const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y	) {
		return x._tree < y._tree;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator!=(	const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y	) {
		return !(x._tree == y._tree);	
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator>(	const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y	) {
		return !(x._tree < y._tree);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator>=(	const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y) {
		return !(x._tree < y._tree);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator<=(	const map<Key,T,Compare,Allocator>& x,
				const map<Key,T,Compare,Allocator>& y	) {
		return !(y._tree < x._tree);
	}

	//// SPECIALIZED ALGOS ////

	template <class Key, class T, class Compare, class Allocator>
	void
	swap(	map<Key,T,Compare,Allocator>& x,
			map<Key,T,Compare,Allocator>& y		);

}	/* namespace ft */

#endif	/* MAP_HPP */
