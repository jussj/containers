#ifndef MAP_HPP
# define MAP_HPP

# include "iterator/reverse_iterator.hpp"
# include <map>

namespace ft {

	template <	class Key,
				class T,
				class Compare = less<Key>,
				class Alloc = allocator<pair<const Key, T> > >
	class map {

		public:

		// TYPES

			typedef Key					key_type;
			typedef T					mapped_type;
			typedef pair<const Key, T>	value_type;
			typedef Compare				key_compare;
			typedef Alloc				allocator_type;
			typedef size_t				size_type;			// impl defined
			typedef ptrdiff_t			difference_type;	// impl defined

			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;

			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;
		
			// STD ITERATORS	
			typedef /* ... */ std::map::iterator			iterator;
			typedef /* ... */ std::map::const_iterator		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// ???????

			class value_compare
			: public binary_function<value_type, value_type, bool> {
				friend class map;
				
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}

				public:
					bool operator()(	const value_type& x,
										const value_type& y	) const {
						return comp(x.first, y.first);
					}
			};

		// CTOR, DTOR AND COPY

			explicit map(	const key_compare& comp = Compare(),
							const allocator_type& = Allocator()	);

			template <class InputIterator>
			map(	InputIterator first,
					InputIterator last,
					const key_compare& comp = Compare(),
					const allocator_type& = Allocator()	);

			map(const map<key_type, T, key_compare, allocator_type>& x);
			~map();
			map<key_type, T, key_compare, allocator_type>&
			operator=(const map<key_type, T, key_compare, allocator_type>& x);

		// ITERATORS

			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;
		
		// CAPACITY

			bool		empty() const;
			size_type	size() const;
			size_type	max_size() const;

		// ACCESS

			T& operator[](const key_type& x);

		// MODIFIERS

			pair<iterator, bool>	insert(const value_type& x);
			iterator	insert(iterator position, const value_type& x);
			template <class InputIterator>
			void		insert(InputIterator first, InputIterator last);
			
			void		erase(iterator position);
			size_type	erase(const key_type& x);
			void		erase(iterator first, iterator last);
			void		swap(map<Key,T,Compare,Allocator>&);
			void		clear();
			
		// OBSERVERS

		I	key_compare		key_comp() const;
			value_compare	value_comp() const;
I
		// MAP OPERATIONS

		I	const_iterator		find(const key_type& x) const;
			size_type			count(const key_type& x) const;
			iterator			lower_bound(const key_type& x);
			const_iterator I	lower_bound(const key_type& x) const;
			iterator			upper_bound(const key_type& x);
			const_iterator		upper_bound(const key_type& x) const;
			
			pair<iterator,iterator>
			equal_range(const key_type& x);
			pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const;
	
};	/* class map */

template <class Key, class T, class Compare, class Allocator>
bool	operator==(	const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y	);
template <class Key, class T, class Compare, class Allocator>
bool	operator<(	const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y	);
template <class Key, class T, class Compare, class Allocator>
bool	operator!=(	const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y	);
template <class Key, class T, class Compare, class Allocator>
bool	operator>(	const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y	);
template <class Key, class T, class Compare, class Allocator>
bool	operator>=(	const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y);
template <class Key, class T, class Compare, class Allocator>
bool	operator<=(	const map<Key,T,Compare,Allocator>& x,
					const map<Key,T,Compare,Allocator>& y	);

// SPECIALIZED ALGOS

template <class Key, class T, class Compare, class Allocator>
void	swap(	map<Key,T,Compare,Allocator>& x,
				map<Key,T,Compare,Allocator>& y		);

}	/* namespace ft */

#endif	/* MAP_HPP */
