#include "rb_tree_s.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {
	template <	class Key,
				class Compare = std::less<Key>,
				class Allocator = std::allocator<Key> >
	class set {

		public:

			// TYPES
			
			typedef Key			key_type;
			typedef Key			value_type;
			typedef Compare		key_compare;
			typedef Compare		value_compare;
			typedef Allocator	allocator_type;

			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference const_reference;
			
			typedef ft::rb_tree_iterator<value_type>		iterator;
			typedef ft::rb_tree_const_iterator<value_type>	const_iterator;

			typedef size_t				size_type;
			typedef ptrdiff_t			difference_type;
			
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		private:

			typedef rb_tree_impl <Key, Key, Key, Compare, 
					Allocator, ft::return_value<Key> >		rb_tree;
			
			// ATTRIBUTES
			
			allocator_type		_alloc;
			rb_tree				_tree;

		public:

			// CTOR/DTOR
			
			explicit
			set(const Compare& comp = Compare(),
				const Allocator& alloc = Allocator())
				:	_alloc(alloc), _tree(comp) {}
			
			template <class InputIterator>
			set(InputIterator first,
				InputIterator last,
				const Compare& comp = Compare(),
				const Allocator& alloc = Allocator())
				:	_alloc(alloc), _tree(comp) {
					insert(first, last);	
				}
			
			set(const set<Key,Compare,Allocator>& x);
			
			~set() {
				clear();
			}
			
			set<Key,Compare,Allocator>&
			operator=(const set<Key,Compare,Allocator>& x);
			
			allocator_type
			get_allocator() const;
			
			// ITERATORS
			
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
			
			// CAPACITY
			
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
				return _tree.max_size();
			}
			
			// MODIFIERS
			
			pair<iterator, bool>
			insert(const value_type& x) {
				bool		key		= false;
				iterator	it		= find(x);

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
				while (first != last)
					insert(*first++);	
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
				return 1;
			}
			
			void
			erase(iterator first, iterator last) {
				while (first != last)
					_tree.erase_and_rebalance(first++);
			}

			void
			swap(set<Key,Compare,Allocator>& src) {
				rb_tree	tmp	= this->_tree;

				this->_tree	= src._tree;
				src._tree	= tmp;
			}
		
			void	
			clear() {
				_tree.clear();	
			}

			// OBSERVERS
			
			key_compare
			key_comp() const {
				return key_compare(_tree.compare());
			}
			
			value_compare
			value_comp() const {
				return value_compare(_tree.compare());
			}
			
			// OPERATIONS
			
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
						lower_bound(x), upper_bound(x)
						);
			}

	};	/* set class */

	template <class Key, class Compare, class Allocator>
	bool operator==(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y);
	template <class Key, class Compare, class Allocator>
	bool operator< (const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y);
	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y);
	template <class Key, class Compare, class Allocator>
	bool operator> (const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y);
	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y);
	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y);
	
	// SPECIALIZED ALGORITHMS 
	
	template <class Key, class Compare, class Allocator>
	void swap(set<Key,Compare,Allocator>& x,
	set<Key,Compare,Allocator>& y);

}	/* namespace ft */
